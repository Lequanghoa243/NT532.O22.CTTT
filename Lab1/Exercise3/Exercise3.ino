
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int numOfLeds = 6;
const int buttonPin = 8;

int buttonState = 0;

void setup() {
  for(int i = 0; i < numOfLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
}
// Read the state of the pushbutton value and Simulate rolling the die
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    for(int i = 0; i < numOfLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
      digitalWrite(ledPins[i], LOW);
    }
    
    // Generate a random number between 1 and 6 
    int rolledNumber = random(1, 7);
    
    // Display the result by lighting up LEDs
    for(int i = 0; i < rolledNumber; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    
    delay(1000);

    // Blink all LEDs up to the rolled number 6 times
    for(int j = 0; j < 7; j++) {
      for(int i = 0; i < rolledNumber; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      delay(250);
      for(int i = 0; i < rolledNumber; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      delay(250);
    }

    delay(500);
    
    // Turn off all LEDs after blinking
    for(int i = 0; i < numOfLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(50);
}
