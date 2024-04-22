#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <BH1750.h>

const char* ssid = "UiTiOt-E3.1";
const char* password = "UiTiOtAP";
const char* serverName = "http://172.31.11.202:5000/sensor";

WiFiClient client;
BH1750 lightMeter(0x23);  // Default I2C address of the BH1750

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Wire.begin(D2, D1);  // SDA, SCL
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  pinMode(D3, OUTPUT); // LED 1
  pinMode(D4, OUTPUT); // LED 2
  pinMode(D5, OUTPUT); // LED 3

  digitalWrite(D3, LOW); // Ensure LEDs are off initially
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
}

void loop() {
  float lux = lightMeter.readLightLevel(); // Read light level from BH1750
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    DynamicJsonDocument doc(1024);
    doc["data"]["light"] = lux;  // Send light level in lux
    String requestBody;
    serializeJson(doc, requestBody);
    
    int httpResponseCode = http.POST(requestBody);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
      
      DynamicJsonDocument resDoc(1024);
      deserializeJson(resDoc, response);
      int leds_on = resDoc["data"]["leds_on"];
      // Control LEDs based on the number received
      digitalWrite(D3, leds_on > 0 ? HIGH : LOW);
      digitalWrite(D4, leds_on > 1 ? HIGH : LOW);
      digitalWrite(D5, leds_on > 2 ? HIGH : LOW);
    }
    http.end();
  }
  delay(500); // Send data every 0.5 seconds
}
