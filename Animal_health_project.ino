#include <DHT.h>

// DHT11 setup
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pulse sensor setup
#define PULSE_PIN A0

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Initialize DHT sensor
  dht.begin();

  Serial.println("Animal Health Monitoring System");
  Serial.println("--------------------------------");
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read pulse sensor value
  int pulseValue = analogRead(PULSE_PIN);

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error: Failed to read from DHT sensor!");
    delay(2000); // Wait before retrying
    return;
  }

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pulse Value: ");
  Serial.println(pulseValue);

  Serial.println("--------------------------------");

  // Wait before the next reading
  delay(2000); // 2 seconds
}
