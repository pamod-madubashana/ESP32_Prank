
#include <WiFi.h>
#include <LittleFS.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* AP_SSID = "YOUR_WIFI_SSID";

IPAddress portalIP(192, 168, 4, 1);

DNSServer dnsServer;
WebServer server(80);

void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
    return;
  }

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(
    portalIP,
    portalIP,
    IPAddress(255, 255, 255, 0)
  );

  // Open Wi-Fi, no password
  WiFi.softAP(AP_SSID);

  // Redirect DNS requests to ESP32
  dnsServer.start(53, "*", portalIP);

  // Display JPG directly
  server.on("/", HTTP_GET, []() {
    File image = LittleFS.open("/image.jpg", "r");

    if (!image) {
      server.send(404, "text/plain", "Image not found");
      return;
    }

    server.streamFile(image, "image/jpeg");
    image.close();
  });

  server.onNotFound([]() {
    server.sendHeader("Location", "http://192.168.4.1/", true);
    server.send(302, "text/plain", "");
  });

  server.begin();

  Serial.println("Hotspot started!");
  Serial.printf("SSID: %s\n", AP_SSID);
  Serial.println("URL: http://192.168.4.1");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
