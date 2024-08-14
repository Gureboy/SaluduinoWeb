#include "SaluduinoWeb.h"
#include <FS.h>

// Constructor
SaluduinoWeb::SaluduinoWeb() : server(80) {}

// Inicializa WiFiManager y el servidor web
void SaluduinoWeb::begin() {
    // Configuración de WiFiManager
    wifiManager.autoConnect("Saluduino_AP");

    // Configuración del servidor web
    server.on("/", HTTP_GET, std::bind(&SaluduinoWeb::handleRoot, this));
    server.on("/agregar", HTTP_GET, std::bind(&SaluduinoWeb::handleAgregar, this));
    server.on("/ver", HTTP_GET, std::bind(&SaluduinoWeb::handleVer, this));
    server.on("/eliminar", HTTP_GET, std::bind(&SaluduinoWeb::handleEliminar, this));
    server.on("/avanzadas", HTTP_GET, std::bind(&SaluduinoWeb::handleOpcionesAvanzadas, this));
    server.on("/hub", HTTP_GET, std::bind(&SaluduinoWeb::handleHub, this));

    // Iniciar el servidor
    server.begin();
}

// Maneja las solicitudes de clientes
void SaluduinoWeb::handleClient() {
    server.handleClient();
}

// Página principal
void SaluduinoWeb::handleRoot() {
    String html = R"rawliteral(
    <!DOCTYPE HTML>
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Inicio</title>
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
      <style>
        .content-wrapper {
          background-color: #f4f6f9;
        }
        .container {
          margin: 20px;
        }
      </style>
    </head>
    <body class="hold-transition sidebar-mini">
      <div class="wrapper">
        <header class="main-header">
          <nav class="navbar navbar-expand navbar-dark">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
              </li>
              <li class="nav-item d-none d-sm-inline-block">
                <a href="/" class="nav-link">Inicio</a>
              </li>
            </ul>
          </nav>
        </header>
        <aside class="main-sidebar elevation-4">
          <a href="/" class="brand-link">
            <span class="brand-text font-weight-light">Saluduino</span>
          </a>
          <div class="sidebar">
            <nav class="mt-2">
              <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
                <li class="nav-item">
                  <a href="/avanzadas" class="nav-link">
                    <i class="nav-icon fas fa-cogs"></i>
                    <p>Opciones Avanzadas</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/hub" class="nav-link">
                    <i class="nav-icon fas fa-clinic-medical"></i>
                    <p>Hub Enfermero</p>
                  </a>
                </li>
              </ul>
            </nav>
          </div>
        </aside>
        <div class="content-wrapper">
          <div class="content-header">
            <div class="container-fluid">
              <h1 class="m-0 text-dark">Inicio</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <div class="row">
                <div class="col-md-4">
                  <a href="/ver" class="btn btn-primary btn-lg btn-block">Ver Pacientes</a>
                </div>
                <div class="col-md-4">
                  <a href="/agregar" class="btn btn-success btn-lg btn-block">Agregar Paciente</a>
                </div>
                <div class="col-md-4">
                  <a href="/eliminar" class="btn btn-danger btn-lg btn-block">Eliminar Paciente</a>
                </div>
              </div>
            </div>
          </div>
        </div>
        <footer class="main-footer">
          <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
        </footer>
      </div>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

// Página para agregar pacientes
void SaluduinoWeb::handleAgregar() {
    String html = R"rawliteral(
    <!DOCTYPE HTML>
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Agregar Paciente</title>
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
      <style>
        .content-wrapper {
          background-color: #f4f6f9;
        }
        .container {
          margin: 20px;
        }
      </style>
    </head>
    <body class="hold-transition sidebar-mini">
      <div class="wrapper">
        <header class="main-header">
          <nav class="navbar navbar-expand navbar-dark">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
              </li>
              <li class="nav-item d-none d-sm-inline-block">
                <a href="/" class="nav-link">Inicio</a>
              </li>
            </ul>
          </nav>
        </header>
        <aside class="main-sidebar elevation-4">
          <a href="/" class="brand-link">
            <span class="brand-text font-weight-light">Saluduino</span>
          </a>
          <div class="sidebar">
            <nav class="mt-2">
              <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
                <li class="nav-item">
                  <a href="/agregar" class="nav-link active">
                    <i class="nav-icon fas fa-plus"></i>
                    <p>Agregar Paciente</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/ver" class="nav-link">
                    <i class="nav-icon fas fa-eye"></i>
                    <p>Ver Pacientes</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/eliminar" class="nav-link">
                    <i class="nav-icon fas fa-trash"></i>
                    <p>Eliminar Paciente</p>
                  </a>
                </li>
              </ul>
            </nav>
          </div>
        </aside>
        <div class="content-wrapper">
          <div class="content-header">
            <div class="container-fluid">
              <h1 class="m-0 text-dark">Agregar Paciente</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <form action="/agregar_paciente" method="post">
                <div class="form-group">
                  <label for="nombre">Nombre:</label>
                  <input type="text" id="nombre" name="nombre" class="form-control" required>
                </div>
                <div class="form-group">
                  <label for="edad">Edad:</label>
                  <input type="number" id="edad" name="edad" class="form-control" required>
                </div>
                <div class="form-group">
                  <label for="bpm">BPM:</label>
                  <input type="number" id="bpm" name="bpm" class="form-control" required>
                </div>
                <div class="form-group">
                  <label for="temperatura">Temperatura:</label>
                  <input type="number" id="temperatura" name="temperatura" class="form-control" step="0.1" required>
                </div>
                <button type="submit" class="btn btn-success">Agregar</button>
              </form>
            </div>
          </div>
        </div>
        <footer class="main-footer">
          <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
        </footer>
      </div>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

// Página para ver pacientes
void SaluduinoWeb::handleVer() {
    String html = R"rawliteral(
    <!DOCTYPE HTML>
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Ver Pacientes</title>
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
      <style>
        .content-wrapper {
          background-color: #f4f6f9;
        }
        .container {
          margin: 20px;
        }
      </style>
    </head>
    <body class="hold-transition sidebar-mini">
      <div class="wrapper">
        <header class="main-header">
          <nav class="navbar navbar-expand navbar-dark">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
              </li>
              <li class="nav-item d-none d-sm-inline-block">
                <a href="/" class="nav-link">Inicio</a>
              </li>
            </ul>
          </nav>
        </header>
        <aside class="main-sidebar elevation-4">
          <a href="/" class="brand-link">
            <span class="brand-text font-weight-light">Saluduino</span>
          </a>
          <div class="sidebar">
            <nav class="mt-2">
              <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
                <li class="nav-item">
                  <a href="/ver" class="nav-link active">
                    <i class="nav-icon fas fa-eye"></i>
                    <p>Ver Pacientes</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/agregar" class="nav-link">
                    <i class="nav-icon fas fa-plus"></i>
                    <p>Agregar Paciente</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/eliminar" class="nav-link">
                    <i class="nav-icon fas fa-trash"></i>
                    <p>Eliminar Paciente</p>
                  </a>
                </li>
              </ul>
            </nav>
          </div>
        </aside>
        <div class="content-wrapper">
          <div class="content-header">
            <div class="container-fluid">
              <h1 class="m-0 text-dark">Ver Pacientes</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <!-- Aquí se debería agregar código para mostrar la lista de pacientes -->
              <p>Aquí se mostrarán los datos de los pacientes.</p>
            </div>
          </div>
        </div>
        <footer class="main-footer">
          <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
        </footer>
      </div>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

// Página para eliminar pacientes
void SaluduinoWeb::handleEliminar() {
    String html = R"rawliteral(
    <!DOCTYPE HTML>
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Eliminar Paciente</title>
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
      <style>
        .content-wrapper {
          background-color: #f4f6f9;
        }
        .container {
          margin: 20px;
        }
      </style>
    </head>
    <body class="hold-transition sidebar-mini">
      <div class="wrapper">
        <header class="main-header">
          <nav class="navbar navbar-expand navbar-dark">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
              </li>
              <li class="nav-item d-none d-sm-inline-block">
                <a href="/" class="nav-link">Inicio</a>
              </li>
            </ul>
          </nav>
        </header>
        <aside class="main-sidebar elevation-4">
          <a href="/" class="brand-link">
            <span class="brand-text font-weight-light">Saluduino</span>
          </a>
          <div class="sidebar">
            <nav class="mt-2">
              <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
                <li class="nav-item">
                  <a href="/eliminar" class="nav-link active">
                    <i class="nav-icon fas fa-trash"></i>
                    <p>Eliminar Paciente</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/ver" class="nav-link">
                    <i class="nav-icon fas fa-eye"></i>
                    <p>Ver Pacientes</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/agregar" class="nav-link">
                    <i class="nav-icon fas fa-plus"></i>
                    <p>Agregar Paciente</p>
                  </a>
                </li>
              </ul>
            </nav>
          </div>
        </aside>
        <div class="content-wrapper">
          <div class="content-header">
            <div class="container-fluid">
              <h1 class="m-0 text-dark">Eliminar Paciente</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <!-- Aquí se debería agregar código para eliminar pacientes -->
              <p>Aquí se eliminarán los pacientes.</p>
            </div>
          </div>
        </div>
        <footer class="main-footer">
          <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
        </footer>
      </div>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

// Página de opciones avanzadas
void SaluduinoWeb::handleOpcionesAvanzadas() {
    String html = R"rawliteral(
    <!DOCTYPE HTML>
    <html lang="es">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Opciones Avanzadas</title>
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/plugins/fontawesome-free/css/all.min.css">
      <link rel="stylesheet" href="https://adminlte.io/themes/v3/dist/css/adminlte.min.css">
      <style>
        .content-wrapper {
          background-color: #f4f6f9;
        }
        .container {
          margin: 20px;
        }
      </style>
    </head>
    <body class="hold-transition sidebar-mini">
      <div class="wrapper">
        <header class="main-header">
          <nav class="navbar navbar-expand navbar-dark">
            <ul class="navbar-nav">
              <li class="nav-item">
                <a class="nav-link" href="#"><i class="fas fa-bars"></i></a>
              </li>
              <li class="nav-item d-none d-sm-inline-block">
                <a href="/" class="nav-link">Inicio</a>
              </li>
            </ul>
          </nav>
        </header>
        <aside class="main-sidebar elevation-4">
          <a href="/" class="brand-link">
            <span class="brand-text font-weight-light">Saluduino</span>
          </a>
          <div class="sidebar">
            <nav class="mt-2">
              <ul class="nav nav-pills nav-sidebar flex-column" data-widget="treeview" role="menu" data-accordion="false">
                <li class="nav-item">
                  <a href="/avanzadas" class="nav-link active">
                    <i class="nav-icon fas fa-cogs"></i>
                    <p>Opciones Avanzadas</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/ver" class="nav-link">
                    <i class="nav-icon fas fa-eye"></i>
                    <p>Ver Pacientes</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/agregar" class="nav-link">
                    <i class="nav-icon fas fa-plus"></i>
                    <p>Agregar Paciente</p>
                  </a>
                </li>
                <li class="nav-item">
                  <a href="/eliminar" class="nav-link">
                    <i class="nav-icon fas fa-trash"></i>
                    <p>Eliminar Paciente</p>
                  </a>
                </li>
              </ul>
            </nav>
          </div>
        </aside>
        <div class="content-wrapper">
          <div class="content-header">
            <div class="container-fluid">
              <h1 class="m-0 text-dark">Opciones Avanzadas</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <!-- Formulario para agregar nuevas IPs -->
              <form action="/agregar_ip" method="post">
                <div class="form-group">
                  <label for="ip">IP del dispositivo:</label>
                  <input type="text" id="ip" name="ip" class="form-control" required>
                </div>
                <button type="submit" class="btn btn-success">Agregar IP</button>
              </form>
              <!-- Aquí se debería agregar código para gestionar las IPs -->
              <p>Aquí se gestionarán las IPs de los dispositivos ESP8266.</p>
            </div>
          </div>
        </div>
        <footer class="main-footer">
          <strong>Saluduino - Sistema de Monitoreo &copy; 2024</strong>
        </footer>
      </div>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("Saluduino_AP");

    server.on("/agregar", HTTP_GET, []() {
        SaluduinoWeb::handleAgregar();
    });

    server.on("/ver", HTTP_GET, []() {
        SaluduinoWeb::handleVer();
    });

    server.on("/eliminar", HTTP_GET, []() {
        SaluduinoWeb::handleEliminar();
    });

    server.on("/avanzadas", HTTP_GET, []() {
        SaluduinoWeb::handleOpcionesAvanzadas();
    });

    server.begin();
}

void loop() {
    server.handleClient();
}
