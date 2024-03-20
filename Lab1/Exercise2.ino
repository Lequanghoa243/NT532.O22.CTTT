const int potPin = A0;
const int ledPins[] = {4, 3, 2};
const int numLeds = 3;

// Start serial communication and Initialize LED pins as outputs
void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
}

// Read the potentiometer and change delay time
void loop() {
  int pValue = analogRead(potPin); 
  int delayTime;

  if (pValue < 341) { 
    delayTime = 500;
    Serial.println("Speed: Slow");
  } else if (pValue < 682) { 
    delayTime = 250;
    Serial.println("Speed: Medium");
  } else { 
    delayTime = 100;
    Serial.println("Speed: Fast");
  }

  //light LEDs from left to right
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
  }

  //light LEDs from right to left
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
  }
}
