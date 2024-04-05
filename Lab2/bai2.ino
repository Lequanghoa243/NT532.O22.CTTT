#include "DHT.h"

#define DHT_PIN 7
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000);
  
  float humidity = dht.readHumidity();
  float tempCelsius = dht.readTemperature();
  float tempFahrenheit = dht.readTemperature(true);
  
  if (isnan(humidity) || isnan(tempCelsius) || isnan(tempFahrenheit)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float heatIndexFahrenheit = dht.computeHeatIndex(tempFahrenheit, humidity);
  float heatIndexCelsius = dht.computeHeatIndex(tempCelsius, humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature (C): ");
  Serial.print(tempCelsius);
  Serial.print(" °C\t");
  Serial.print("Temperature (F): ");
  Serial.print(tempFahrenheit);
  Serial.print(" °F\t");
  Serial.print("Heat Index (C): ");
  Serial.print(heatIndexCelsius);
  Serial.print(" °C\t");
  Serial.print("Heat Index (F): ");
  Serial.print(heatIndexFahrenheit);
  Serial.println(" °F");
}
