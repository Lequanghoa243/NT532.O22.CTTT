// Pin configuration
const int pirPin = 5;  

// Variables
int pirState = LOW;    
int val = 0;           

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(pirPin, INPUT); // Set PIR sensor pin as input
}

void loop() {
  val = digitalRead(pirPin); // Read PIR sensor value
  
  // Check if motion is detected
  if (val == HIGH) {         
    pirState = HIGH;
    Serial.println("Motion detected!");
  } else {
    pirState = LOW;
    Serial.println("No motion detected");
  }
  
  delay(1000);
}
