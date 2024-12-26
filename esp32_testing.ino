#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFiClientSecure.h>

// WiFi credentials
const char* ssid = "Dialog 4G 093";
const char* password = "b786Fdd8";

// Firmware update URL
const char* firmware_url = "https://raw.githubusercontent.com/mmocbm/esp32_test/main/build/esp32.esp32.esp32/esp32_testing.ino.bin";

// ==================== OTA Update Code ====================
void setupOTA() {
  WiFiClientSecure client;
  client.setInsecure(); // Disable SSL certificate verification
  HTTPClient http;

  Serial.println("Checking for firmware update...");
  Serial.println("Firmware URL: ");
  Serial.println(firmware_url);

  http.begin(client, firmware_url);
  http.setTimeout(20000); // Set timeout to 20 seconds
  int httpCode = http.GET();

  if (httpCode == 200) {
    int contentLength = http.getSize();
    bool canBegin = Update.begin(contentLength);

    if (canBegin) {
      Serial.println("Starting update...");
      size_t written = Update.writeStream(http.getStream());

      if (written == contentLength) {
        Serial.println("Update written successfully!");
      } else {
        Serial.printf("Update failed. Written only %d/%d bytes.\n", written, contentLength);
      }

      if (Update.end()) {
        if (Update.isFinished()) {
          Serial.println("Update completed. Restarting...");
          ESP.restart();
        } else {
          Serial.println("Update failed. Not finished.");
        }
      } else {
        Serial.printf("Update error: %s\n", Update.errorString());
      }
    } else {
      Serial.println("Not enough space for the update.");
    }
  } else {
    Serial.printf("HTTP error: %d\n", httpCode);
  }
  http.end();
}

void loopOTA() {
  // OTA-specific loop code (if any)
}

// ==================== Main setup and loop ====================
void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize OTA
  setupOTA();

  // Initialize the main application
  setupApp();
}

void loop() {
  // Run OTA loop (if needed)
  loopOTA();

  // Run the main application loop
  loopApp();
}