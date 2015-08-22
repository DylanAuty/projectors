/*
  staggered.ino
  Dylan Auty, 22/8/15
  -----------
  Generates pulses of the correct length to advance 3
  Kodak Carousel S-AV2060 Projectors forwards by one slide 
  automatically every slideTime seconds. Projectors are evenly staggered
 */

int led = 13;
int cPulseLength = 500;		//Datasheet specifies 0.2-0.75s for forward change at 50Hz mains
int slideTime = 4000;		// Display each slide for 4 seconds
int gapTime = slideTime/3;	// For even spacing of transition between projectors
// NB: slide transition time is ~1s

void setup() {
	pinMode(led, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
}

void loop() {
	for (int i = 2; i < 5; i++){ // Output pins are 2, 3, and 4
		digitalWrite(led, HIGH);
		digitalWrite(i, HIGH);
		delay(cPulseLength);
		digitalWrite(led, LOW);
		digitalWrite(i, LOW);
		delay(gapTime);
	}
}
