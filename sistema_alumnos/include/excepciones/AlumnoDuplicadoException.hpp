#pragma once

#include <string>

#include "SistemaException.hpp"

/// Se lanza al registrar un código que ya existe.
class AlumnoDuplicadoException : public SistemaException {
public:
    explicit AlumnoDuplicadoException(const std::string& codigo)
        : SistemaException(2002, "Ya existe un alumno con el código '" + codigo + "'."),
          codigo_(codigo) {}

    const std::string& codigo_duplicado() const noexcept { return codigo_; }

private:
    std::string codigo_;
};
