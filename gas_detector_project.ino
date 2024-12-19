#include <DHT.h>
#include <DHT_U.h>

const int gasSensorMQ3Pin = A0;    // MQ-3 analog pin connected to A0
const int buzzerPin = D1;          // Buzzer connected to digital pin D1
const int dhtPin = D2;             // DHT11 sensor connected to digital pin D2

#define DHTTYPE DHT11              // Define sensor type (DHT11)

DHT dht(dhtPin, DHTTYPE);          // Initialize DHT sensor

int gasThreshold = 300;            // Set the gas detection threshold (adjust based on testing)

void setup() {
  pinMode(buzzerPin, OUTPUT);      // Set the buzzer pin as an output
  Serial.begin(115200);            // Initialize serial monitor
  dht.begin();                     // Initialize DHT11 sensor
}

void loop() {
  // Read gas sensor value
  int gasLevel = analogRead(gasSensorMQ3Pin);  // Read the analog value from the gas sensor

  // Read DHT11 sensor data
  float humidity = dht.readHumidity();         // Read humidity
  float temperature = dht.readTemperature();   // Read temperature (in Celsius)

  // Print sensor data to serial monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Check if the gas level exceeds the threshold
  if (gasLevel > gasThreshold) {
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer if gas level exceeds threshold
    Serial.println("Gas Detected! Buzzer ON");
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer if gas level is below threshold
  }

  delay(2000);  // Wait 2 seconds before the next reading
}
