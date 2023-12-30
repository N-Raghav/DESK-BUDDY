#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <Wire.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ135_PIN 12
#define LDR_PIN 2

DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135(MQ135_PIN);
int ldrValue = 0;

#define mqtt_server ""
#define humidity_topic "sensor/DHT11/humidity"
#define temperature_celsius_topic "sensor/DHT11/temperature_celsius"
#define temperature_fahrenheit_topic "sensor/DHT11/temperature_fahrenheit"
#define mq135_topic "sensor/MQ135"
#define ldr_topic "sensor/LDR"

WiFiClient espClient;
PubSubClient client(espClient);

char ssid[] = "";
char pass[] = "";

void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(MQ135_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  while (!Serial) {
    delay(1);
  }
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Wait a few seconds between measurements.
  delay(5000);

  float h = dht.readHumidity();
  float t = dht.readTemperature(true);  // Temperature in Fahrenheit
  ldrValue = analogRead(LDR_PIN);
  float mq135Value = mq135.getPPM();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.println(dht.computeHeatIndex(t, h, false));
  Serial.println(" *F");

  Serial.print("MQ135 Value: ");
  Serial.println(mq135Value);
  client.publish(mq135_topic, String(mq135Value).c_str(), true);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  client.publish(ldr_topic, String(ldrValue).c_str(), true);

  Serial.print("Temperature in Celsius:");
  Serial.println(String(t).c_str());
  client.publish(temperature_celsius_topic, String(t).c_str(), true);

  Serial.print("Temperature in Fahrenheit:");
  Serial.println(String(t).c_str());
  client.publish(temperature_fahrenheit_topic, String(t).c_str(), true);

  Serial.print("Humidity:");
  Serial.println(String(h).c_str());
  client.publish(humidity_topic, String(h).c_str(), true);
}
z
