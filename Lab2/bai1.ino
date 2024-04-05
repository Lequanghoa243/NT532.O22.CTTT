#define TRIG_PIN 13
#define ECHO_PIN 12
#define LED_START_PIN 2  // Start from pin 2 to pin 6 (5 LEDs)

void setup() {
  Serial.begin(9600);
  
  // Set LED pins as outputs
  for(int pin = LED_START_PIN; pin <= 6; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Ensure LEDs are off initially
  }

  // Set the TRIG and ECHO pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

long getDistance() {
  // Send ultrasonic signal
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the duration of the signal
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance based on the duration
  long distance = duration * 0.034 / 2;
  
  return distance;
}

void loop() {
  // Get distance from the ultrasonic sensor
  long distance = getDistance();
  
  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Turn off all LEDs
  for(int pin = LED_START_PIN; pin <= 6; pin++) {
    digitalWrite(pin, LOW);
  }

  // Check if the distance is too close or too far
  if(distance <= 5 || distance >= 20) {
    // If too close or too far, turn on all LEDs
    for(int pin = LED_START_PIN; pin <= 6; pin++) {
      digitalWrite(pin, HIGH);
    }
  } else {
    // Map the distance to determine how many LEDs to light up
    int ledsToLight = map(distance, 5, 20, 1, 5);
    for(int pin = LED_START_PIN; pin < LED_START_PIN + ledsToLight; pin++) {
      digitalWrite(pin, HIGH);
    }
  }

  delay(500); // Delay for half a second before the next reading
}
