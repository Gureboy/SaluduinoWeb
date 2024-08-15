#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "SaluduinoWeb.h"

SaluduinoWeb webServer;

void setup() {
    Serial.begin(115200);
    webServer.begin();
}

void loop() {
    webServer.handleClient();
}
