#ifdef ESP8266
  #include <ESP8266WiFi.h>     /* WiFi library for ESP8266 */
#else
  #include <WiFi.h>            /* WiFi library for ESP32 */
#endif
#include <Wire.h>
#include <PubSubClient.h>
#include "DHT.h"             /* DHT11 sensor library */

#define DHTPIN 4
#define DHTTYPE DHT11 // DHT 11

#define MQ135_PIN 39 // MQ135 data pin
#define LDR_PIN 36 // LDR data pin

DHT dht(DHTPIN, DHTTYPE);
//
//#define wifi_ssid ""
//#define wifi_password ""
#define mqtt_server ""    

#define humidity_topic "sensor/humidity"
#define temperature_celsius_topic "sensor/temperature_celsius"
#define temperature_heatIndex_topic "sensor/heat_index"
# define air_Quality_topic "sensor/airQuality"
#define LDR_topic "sensor/LDR"

WiFiClient espClient;
PubSubClient client(espClient);


char ssid[]="kavin";
char pass[]="nghs3333";

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
  while( !Serial) {
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
      
      // Reading temperature or humidity takes about 250 milliseconds!
      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();


        int airQuality = analogRead(MQ135_PIN);
        int lightIntensity = analogRead(LDR_PIN);
        
      // Check if any reads failed and exit early (to try again).
      if (isnan(h) || isnan(t) ) {
      Serial.println("Failed to read from DHT sensor!");
      return;
      }
      
      // Compute heat index in Celsius (isFahreheit = false)
      float hic = dht.computeHeatIndex(t, h, false);
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print("Heat index: ");
      Serial.print(hic);
      Serial.print(" *C ");

      Serial.print("Light Intensity: ");
      Serial.println(lightIntensity);

      Serial.print("Air Quality");
      Serial.println(airQuality);


      Serial.print("Temperature in Celsius:");
      Serial.println(String(t).c_str());
      client.publish(temperature_celsius_topic, String(t).c_str(), true);

      Serial.print("Heat Index in Celsius:");
      Serial.println(String(hic).c_str());
      client.publish(temperature_heatIndex_topic, String(hic).c_str(), true);

      Serial.print("Humidity:");
      Serial.println(String(h).c_str());
      client.publish(humidity_topic, String(h).c_str(), true);

      Serial.print("Air Quality:");
      Serial.println(String(airQuality).c_str());
      client.publish(air_Quality_topic, String(airQuality).c_str(), true);

      Serial.print("Light Intensity:");
      Serial.println(String(lightIntensity).c_str());
      client.publish(LDR_topic, String(lightIntensity).c_str(), true);
      
      
}
