#ifndef SALUDUINOWEB_H
#define SALUDUINOWEB_H

#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class SaluduinoWeb {
public:
    SaluduinoWeb();
    void begin();
    void handleRoot();
    void handleRegister();
    void handleLogin();
    void handleLogout();
    void handleSuccess();
    void handleError();
    void handleOpcionesAvanzadas();
    
private:
    ESP8266WebServer server;
    WiFiManager wifiManager;
    String registeredUsername;
    String registeredPassword;
    String loggedInUser;
    void sendResponse(String html);
};

#endif


