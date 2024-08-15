#include <ESP8266WiFi.h>
#include <FS.h>
#include "SaluduinoWeb.h"

// Configura tus credenciales WiFi aquí
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Crea una instancia de la librería
SaluduinoWeb saluduinoWeb;

void setup() {
    Serial.begin(115200);

    // Conectar a la red WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Conectado al WiFi");

    // Iniciar la librería
    saluduinoWeb.begin();
}

void loop() {
    saluduinoWeb.handleClient();
}
