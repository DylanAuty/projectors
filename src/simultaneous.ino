/*
  simultaneous.ino
  Dylan Auty, 27/7/15
  -----------
  Generates pulses of the correct length to advance 3
  Kodak Carousel S-AV2060 Projectors forwards by one slide 
  automatically every slideTime seconds.
  -----------
  To work, pulses must be used to control 20V pulse across pins
  2 + 3 of 6 pin DIN socket (originally to take a remote control).
  Additional hardware is needed.
 */

int led = 13;
int cPulseLength = 500;  //Datasheet specifies 0.2-0.75s for forward change at 50Hz mains
int slideTime = 4000; // Display each slide for 4 seconds
// NB: slide transition time is ~1s

void setup() {
  pinMode(led, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(cPulseLength);
  digitalWrite(led, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(slideTime);
}
