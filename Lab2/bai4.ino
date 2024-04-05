// Include the DHT library for interacting with the DHT sensor
#include <DHT.h>

// Define the pin connected to the DHT22 sensor's data pin
#define DHTPIN 2     // Connect the DHT22 sensor's data pin to digital pin 2 of the Arduino
// Specify the type of DHT sensor being used
#define DHTTYPE DHT22   // Use the DHT22 sensor
// Initialize the DHT sensor with the specified pin and type
DHT dht(DHTPIN, DHTTYPE);

// Declare LED pins
const int ledPins[] = {5, 6, 7}; // Pins connected to the LEDs

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  // Initialize the DHT sensor
  dht.begin();
  
  // Set LED pins as OUTPUT and turn them off initially
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Turn off all LEDs at the beginning
  }
}

void loop() {
  // Read humidity and temperature from the DHT22 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Read temperature in Celsius

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature values to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C ");

  if (humidity > 70 || temperature < 27) { // No LED is activated
    controlLEDs(false, false, false);
  } else if (temperature >= 27 && temperature < 29) { // 1 LED is turn on
    controlLEDs(true, false, false);
  } else if (temperature >= 29 && temperature < 30) { // 2 LEDs is turn on
    controlLEDs(true, true, false);
  } else { // 3 LEDs is turn on
    controlLEDs(true, true, true);
  }
}

void controlLEDs(bool led1, bool led2, bool led3) {
  digitalWrite(ledPins[0], led1 ? HIGH : LOW);
  digitalWrite(ledPins[1], led2 ? HIGH : LOW);
  digitalWrite(ledPins[2], led3 ? HIGH : LOW);
}
