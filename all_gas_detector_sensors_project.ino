#define BLYNK_TEMPLATE_ID "TMPL3Q5Y_a8XT"
#define BLYNK_TEMPLATE_NAME "gas detector"
#define BLYNK_AUTH_TOKEN "-AGbnxss8jZG_Cjn7sb-s6QlZPENxPgB"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials
char ssid[] = "APS";
char pass[] = "APS12345";

// Analog pin for sensor input
#define GAS_SENSOR_PIN A0

// Define a time interval to change sensor (e.g., 1 day or button press)
unsigned long switchInterval = 86400000;  // 1 day in milliseconds (adjust as needed)
unsigned long readInterval = 5000;  // Delay between readings (5 seconds)
unsigned long previousSwitchMillis = 0;
unsigned long previousReadMillis = 0;

int currentSensor = 0;  // Keeps track of the current sensor (0 to 3)
bool sensorWarmup = false;  // Flag to track if the sensor has been warmed up
unsigned long warmupTime = 60000;  // 1 minute warm-up time for sensors

// Blynk virtual pins for sending sensor data
#define VIRTUAL_PIN V0  // You can use different pins for each sensor if needed

// Setup function for initial configurations
void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initial message
  Serial.println("Connecting to Blynk...");
}

// Main loop function
void loop() {
  // Run Blynk process
  Blynk.run();

  unsigned long currentMillis = millis();

  // Change sensor after the defined interval (1 day)
  if (currentMillis - previousSwitchMillis >= switchInterval) {
    previousSwitchMillis = currentMillis;
    currentSensor++;  // Move to the next sensor
    if (currentSensor > 3) {
      currentSensor = 0;  // Reset to the first sensor
    }
    sensorWarmup = true;  // Start warming up the new sensor
    Serial.print("Switched to Sensor ");
    Serial.println(currentSensor);
  }

  // Wait for sensor warm-up time before reading values
  if (sensorWarmup && (currentMillis - previousSwitchMillis >= warmupTime)) {
    sensorWarmup = false;  // Warm-up is complete
    Serial.println("Sensor warm-up complete. Now reading values...");
  }

  // Collect data from the current sensor if it's not in warm-up phase
  if (!sensorWarmup && (currentMillis - previousReadMillis >= readInterval)) {
    previousReadMillis = currentMillis;

    // Read the sensor value
    int sensorValue = analogRead(GAS_SENSOR_PIN);  // Read the raw analog value directly

    // Send or display data (e.g., to serial monitor)
    Serial.print("Sensor ");
    Serial.print(currentSensor);
    Serial.print(": ");
    Serial.println(sensorValue);  // Print the raw analog value

    // Send data to Blynk app
    Blynk.virtualWrite(VIRTUAL_PIN, sensorValue);  // Send raw sensor value to virtual pin V0
  }
}
