/*
  staggered.ino
  Dylan Auty, 22/8/15
  Updated 10/10/15 to include functionality to save current projector to EEPROM, to preserve synchronisation of projectors
  -----------
  Generates pulses of the correct length to advance 3
  Kodak Carousel S-AV2060 Projectors forwards by one slide 
  automatically every slideTime seconds. Projectors are evenly staggered
 */

#include <EEPROM.h>	// Including library for writing to EEPROM
#define CONFIG_VERSION "ps1"	//To prevent overwriting things, and allow appropriate use of defaults if settings don't exist
#define CONFIG_START 32	//Tells the where to store the config data in EEPROM
// NB - Current projector being used is to be stored in the config
// This allows a loss of power without the projectors going out of sync

struct StoreStruct {
	int lastProj;
	char versionNum[4];	//Stores the version number - will be set to CONFIG_VERSION (= 'ps1' + a terminator \0)
}settings = {
	0,
	CONFIG_VERSION
};

int led = 13;
int cPulseLength = 500;		//Datasheet specifies 0.2-0.75s for forward change at 50Hz mains
int slideTime = 4000;		// Display each slide for 4 seconds
int gapTime = slideTime/3;	// For even spacing of transition between projectors
// NB: slide transition time is ~1s

void setup() {
	loadConfig();	//Check for config file
	pinMode(led, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
}

void loadConfig(){
	// Purpose of this function is to check if a config file exists
	// If it doesn't then it will use default settings.
	if(
		//EEPROM.read(CONFIG_START + sizeof(settings) - 1) == settings.versionNum[3] &&
		// Above line commented out because the character is \0, null terminator
		EEPROM.read(CONFIG_START + sizeof(settings) - 2) == settings.versionNum[2] &&
		EEPROM.read(CONFIG_START + sizeof(settings) - 3) == settings.versionNum[1] &&
		EEPROM.read(CONFIG_START + sizeof(settings) - 4) == settings.versionNum[0]
	)
	{
		for (unsigned int t=0; t < sizeof(settings); t++){
			*((char*)&settings + t) = EEPROM.read(CONFIG_START + t);
		}
	}
	else{
		saveConfig();
	}
}

void saveConfig() {
	for (unsigned int t = 0; t < sizeof(settings); t++){
		EEPROM.write(CONFIG_START + t, *((char*)&settings + t));
		if(EEPROM.read(CONFIG_START + t) != *((char*)&settings + t)){
			//If this is the case then there's been a problem writing
			//...maybe retry? Could create infinite loop so... maybe not
		}
	}
}

void loop() {
	// At the start of the loop, check if we've just done the last projector (2)
	// If so then loop back around at the end.
	// Before sending the signal, write the state to the EEPROM
	// START - read the settings in
	loadConfig();

	digitalWrite(led, HIGH);
	digitalWrite(settings.lastProj + 2, HIGH); // Adding 2 as it's configured to use pins 2, 3 and 4 for projectors
	delay(cPulseLength);
	digitalWrite(led, LOW);
	digitalWrite(settings.lastProj + 2, LOW);
	delay(gapTime);
	
	settings.lastProj++;
	if(settings.lastProj == 3){
		settings.lastProj = 0;	// Loop back around
	}
	saveConfig();	//Save the current projector state

	
}
