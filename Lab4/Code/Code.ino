#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN D4
#define DHTTYPE DHT22
#define LED_PIN D7

const char* ssid = "UiTiOt-E3.1";
const char* password = "UiTiOtAP";
const char* postServerName = "http://172.31.11.202:3000/sensor";
const char* getServerName = "http://172.31.11.202:3000/device2/light"; // Endpoint to get the light status

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
ESP8266WebServer server(80);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();
  Wire.begin(); // SDA, SCL
  lightMeter.begin();

  server.begin();
}

void loop() {
  server.handleClient();
  if (WiFi.status() == WL_CONNECTED) {
    postDataToServer();
    checkAndControlLED();
  }
  delay(2000); // Delay for 10 seconds before repeating
}

void postDataToServer() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float lightLevel = lightMeter.readLightLevel();
  Serial.println(humidity);
  Serial.println(temperature);
  Serial.println(lightLevel);
  if (!isnan(humidity) && !isnan(temperature) && lightLevel >= 0) {
    HTTPClient http;
    http.begin(client, postServerName);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"deviceId\":\"1\", \"temperature\":\"" + String(temperature) +
                             "\", \"humidity\":\"" + String(humidity) +
                             "\", \"light\":\"" + String(lightLevel) + "\"}";

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println("Data posted successfully: " + response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Failed to read from sensors!");
  }
}

void checkAndControlLED() {
  HTTPClient http;
  http.begin(client, getServerName);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    String payload = http.getString();
    Serial.println("Received payload: " + payload);

    if (payload.indexOf("\"status\":\"on\"") != -1) {
      digitalWrite(LED_PIN, HIGH);  // Turn LED on
      Serial.println("LED turned ON based on server response.");
    } else if (payload.indexOf("\"status\":\"off\"") != -1) {
      digitalWrite(LED_PIN, LOW);  // Turn LED off
      Serial.println("LED turned OFF based on server response.");
    }
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
