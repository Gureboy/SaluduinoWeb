#ifndef SALUDUINOWEB_H
#define SALUDUINOWEB_H

#include <ESP8266WebServer.h>

class SaluduinoWeb {
public:
    void begin();
    void handleClient();
private:
    ESP8266WebServer server;

    void handleInicio();
    void handleAgregarPaciente();
    void handleVerPacientes();
    void handleEliminar();
    void handleOpcionesAvanzadas();
    void handleAgregarIP();
};

#endif // SALUDUINOWEB_H

