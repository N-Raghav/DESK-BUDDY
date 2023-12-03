#include <DHT.h>

#define DHTPIN 4 // DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN 12 // MQ135 data pin
#define LDR_PIN 2 // LDR data pin
#define BUZZER_PIN 13 // Buzzer data pin

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MQ135_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  delay(2000);

  
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int airQuality = analogRead(MQ135_PIN);
  int lightIntensity = analogRead(LDR_PIN);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Air Quality: ");
  Serial.print(airQuality);
  Serial.print(", Light Intensity: ");
  Serial.println(lightIntensity);

  // You can add your logic here to control the buzzer based on sensor readings.
  // For example, if airQuality is above a certain threshold, trigger the buzzer.
  if (airQuality > 500) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000); // Delay between readings
}
