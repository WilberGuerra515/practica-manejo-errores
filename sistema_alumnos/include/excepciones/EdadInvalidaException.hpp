// Hereda de SistemaException para integrarse a la jerarquía común.

#pragma once

#include <string>

#include "SistemaException.hpp"

class EdadInvalidaException : public SistemaException {
public:
    explicit EdadInvalidaException(int edad)
        : SistemaException(1001, "Edad fuera de rango: " + std::to_string(edad) +
                                     " (valores permitidos: 0 a 120)"),
          edad_(edad) {}

    int edad() const noexcept { return edad_; }

private:
    int edad_;
};