// Práctica 5 - Excepción personalizada (versión autónoma, sin dependencias).
// Responsable: Jaime
#pragma once

#include <exception>
#include <string>

/// Se lanza cuando la edad ingresada es menor que 0 o mayor que 120.
class EdadInvalidaException : public std::exception {
public:
    explicit EdadInvalidaException(int edad)
        : edad_(edad),
          mensaje_("Edad fuera de rango: " + std::to_string(edad) +
                   " (valores permitidos: 0 a 120)") {}

    const char* what() const noexcept override { return mensaje_.c_str(); }

    /// Edad que provocó el error.
    int edad() const noexcept { return edad_; }

private:
    int edad_;
    std::string mensaje_;
};
