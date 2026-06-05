#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Temperature & Humidity Monitor");
  Serial.println("-------------------------------");
}

void loop() {
  delay(2000);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if reading failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  // Alert system
  if (temperature > 35) {
    Serial.println("⚠️ ALERT: High Temperature!");
  }
  if (humidity > 80) {
    Serial.println("⚠️ ALERT: High Humidity!");
  }
  
  Serial.println("-------------------------------");
}