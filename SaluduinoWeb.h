#ifndef SALUDUINOWEB_H
#define SALUDUINOWEB_H

#include <ESP8266WebServer.h>
#include <FS.h>

class SaluduinoWeb {
public:
    SaluduinoWeb();
    void begin();
    void handleClient();
    void handleRoot();
    void handleLogin();
    void handleRegister();
    void handleVerPacientes();
    void handleOpcionesAvanzadas();
    void handleHubEnfermero();
    void handleAgregarPaciente();
    void handleEliminarPaciente();
    void handleNotFound();
    
private:
    ESP8266WebServer server;
    
    void loadFile(String path);
    void handleFileRead(String path);
};

#endif



