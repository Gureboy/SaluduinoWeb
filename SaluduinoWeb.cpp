#include "SaluduinoWeb.h"

SaluduinoWeb::SaluduinoWeb() : server(80) {}

void SaluduinoWeb::begin() {
    if (!SPIFFS.begin()) {
        Serial.println("Error al montar el sistema de archivos SPIFFS");
        return;
    }

    server.on("/", HTTP_GET, [this]() { handleRoot(); });
    server.on("/iniciar-sesion", HTTP_GET, [this]() { handleLogin(); });
    server.on("/registrarse", HTTP_GET, [this]() { handleRegister(); });
    server.on("/ver-pacientes", HTTP_GET, [this]() { handleVerPacientes(); });
    server.on("/opciones-avanzadas", HTTP_GET, [this]() { handleOpcionesAvanzadas(); });
    server.on("/hub-enfermero", HTTP_GET, [this]() { handleHubEnfermero(); });
    server.on("/agregar-paciente", HTTP_GET, [this]() { handleAgregarPaciente(); });
    server.on("/eliminar-paciente", HTTP_GET, [this]() { handleEliminarPaciente(); });
    server.onNotFound([this]() { handleNotFound(); });

    server.begin();
}

void SaluduinoWeb::handleClient() {
    server.handleClient();
}

void SaluduinoWeb::handleRoot() {
    handleFileRead("/inicio.html");
}

void SaluduinoWeb::handleLogin() {
    handleFileRead("/iniciar-sesion.html");
}

void SaluduinoWeb::handleRegister() {
    handleFileRead("/registrarse.html");
}

void SaluduinoWeb::handleVerPacientes() {
    handleFileRead("/ver-pacientes.html");
}

void SaluduinoWeb::handleOpcionesAvanzadas() {
    handleFileRead("/opciones-avanzadas.html");
}

void SaluduinoWeb::handleHubEnfermero() {
    handleFileRead("/hub-enfermero.html");
}

void SaluduinoWeb::handleAgregarPaciente() {
    handleFileRead("/agregar-paciente.html");
}

void SaluduinoWeb::handleEliminarPaciente() {
    handleFileRead("/eliminar-paciente.html");
}

void SaluduinoWeb::handleNotFound() {
    server.send(404, "text/plain", "404 Not Found");
}

void SaluduinoWeb::handleFileRead(String path) {
    if (path.endsWith("/")) {
        path += "inicio.html";
    }
    
    String contentType = "text/html";
    if (path.endsWith(".css")) {
        contentType = "text/css";
    } else if (path.endsWith(".js")) {
        contentType = "application/javascript";
    } else if (path.endsWith(".png")) {
        contentType = "image/png";
    } else if (path.endsWith(".jpg")) {
        contentType = "image/jpeg";
    }

    File file = SPIFFS.open(path, "r");
    if (file) {
        server.streamFile(file, contentType);
        file.close();
    } else {
        server.send(404, "text/plain", "404 Not Found");
    }
}

