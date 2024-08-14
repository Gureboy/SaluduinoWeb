#ifndef SALUDUINO_WEB_H
#define SALUDUINO_WEB_H

#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class SaluduinoWeb {
public:
    SaluduinoWeb();
    void begin();
    void handleClient();
    
private:
    ESP8266WebServer server;
    WiFiManager wifiManager;
    
    void handleRoot();
    void handleAgregar();
    void handleVer();
    void handleEliminar();
    void handleOpcionesAvanzadas();
    void handleHub();
};

#endif
