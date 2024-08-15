#include "SaluduinoWeb.h"

void SaluduinoWeb::begin() {
    server.on("/", HTTP_GET, [this]() { handleInicio(); });
    server.on("/agregar", HTTP_GET, [this]() { handleAgregarPaciente(); });
    server.on("/ver", HTTP_GET, [this]() { handleVerPacientes(); });
    server.on("/eliminar", HTTP_GET, [this]() { handleEliminar(); });
    server.on("/avanzadas", HTTP_GET, [this]() { handleOpcionesAvanzadas(); });
    server.on("/agregar_ip", HTTP_POST, [this]() { handleAgregarIP(); });

    server.begin();
}

void SaluduinoWeb::handleClient() {
    server.handleClient();
}

void SaluduinoWeb::handleInicio() {
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
                <a href="/" class="nav-link active">Inicio</a>
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
              <h1 class="m-0 text-dark">Inicio</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <p>Bienvenido al sistema de monitoreo de pacientes.</p>
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

void SaluduinoWeb::handleAgregarPaciente() {
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
                  <input type="text" id="bpm" name="bpm" class="form-control" required>
                </div>
                <div class="form-group">
                  <label for="temperatura">Temperatura:</label>
                  <input type="text" id="temperatura" name="temperatura" class="form-control" required>
                </div>
                <button type="submit" class="btn btn-primary">Agregar Paciente</button>
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

void SaluduinoWeb::handleVerPacientes() {
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
              <h1 class="m-0 text-dark">Lista de Pacientes</h1>
            </div>
          </div>
          <div class="content">
            <div class="container-fluid">
              <p>Aquí se mostrará la lista de pacientes registrados.</p>
              <!-- Aquí deberías agregar el código para mostrar los pacientes -->
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
              <form action="/eliminar_paciente" method="post">
                <div class="form-group">
                  <label for="id">ID del Paciente:</label>
                  <input type="text" id="id" name="id" class="form-control" required>
                </div>
                <button type="submit" class="btn btn-danger">Eliminar Paciente</button>
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
              <form action="/agregar_ip" method="post">
                <div class="form-group">
                  <label for="ip">IP del Dispositivo:</label>
                  <input type="text" id="ip" name="ip" class="form-control" required>
                </div>
                <button type="submit" class="btn btn-primary">Agregar IP</button>
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

void SaluduinoWeb::handleAgregarIP() {
    // Aquí se debería procesar la IP agregada y realizar la conexión con el dispositivo.
    server.send(200, "text/html", "<h1>IP agregada exitosamente</h1>");
}

