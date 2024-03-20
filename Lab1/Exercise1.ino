const int analogPin = A0; // The pin the potentiometer is connected to
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // The pins the LEDs are connected to
const int numLeds = 12; // Number of LEDs

void setup() {
  // Initialize the LED pins as output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int sensorValue = analogRead(analogPin); // Read the potentiometer
  // Map the potentiometer value to the number of LEDs
  int numLitLeds = map(sensorValue, 0, 1023, 0, numLeds);
  
  // Turn on LEDs up to the mapped number
  for (int i = 0; i < numLitLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  // Turn off the rest of the LEDs
  for (int i = numLitLeds; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}