#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "UiTiOt-E3.1";
const char* password = "UiTiOtAP";
const char* mqtt_server = "172.31.11.48";


// Initialize the client library
WiFiClient espClient;
PubSubClient client(espClient);

// GPIO where the LED is connected
const int ledPin = D3;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(ledPin, HIGH);
  } else if (message == "OFF") {
    digitalWrite(ledPin, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("WemosD1")) {
      Serial.println("connected");
      client.subscribe("nt533/o22/group2/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}