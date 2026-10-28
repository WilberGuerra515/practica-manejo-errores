// Registro de eventos y errores en un archivo de log.
// Responsable: Cristhian
#pragma once

#include <string>

class Logger {
public:
    /// Cambia la ruta del archivo de log (por defecto "logs/errores.log").
    static void configurar(const std::string& ruta);

    static void info(const std::string& mensaje);
    static void advertencia(const std::string& mensaje);
    static void error(const std::string& mensaje);

private:
    static void escribir(const char* nivel, const std::string& mensaje);
    static std::string& ruta();
};
