#define BLYNK_TEMPLATE_ID "TMPL3RBvkO4gs"
#define BLYNK_TEMPLATE_NAME "Ph sensor"
#define BLYNK_AUTH_TOKEN "vBJC_w4SeK_kz7WME1c5W3zGAhMr__WK"   // Blynk Authentication Token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials
#define WIFI_SSID "Abc"        
#define WIFI_PSWD "84490962" 

char auth[] = BLYNK_AUTH_TOKEN;  // Blynk Auth Token

// pH sensor connected to A0
const int phPin = A0;

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to Blynk
  Blynk.begin(auth, WIFI_SSID, WIFI_PSWD);
}

void loop() {
  // Read pH sensor value
  int phValue = analogRead(phPin); // Raw analog value
  float voltage = phValue * (3.3 / 1023.0); // Convert to voltage (assuming 3.3V)
  
  // Convert voltage to pH level
  float phLevel = 7 + ((2.5 - voltage) * 3.5); // Example conversion formula, may vary based on sensor

  // Send pH level to Blynk virtual pin V0
  Blynk.virtualWrite(V0, phLevel);

  // Print pH value in Serial Monitor
  Serial.print("pH Level: ");
  Serial.println(phLevel);

  Blynk.run(); // Run Blynk in the loop
}
