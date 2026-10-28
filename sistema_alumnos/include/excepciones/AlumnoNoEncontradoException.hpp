#pragma once

#include <string>

#include "SistemaException.hpp"

/// Se lanza al buscar o eliminar un código que no existe.
class AlumnoNoEncontradoException : public SistemaException {
public:
    explicit AlumnoNoEncontradoException(const std::string& codigo)
        : SistemaException(2001, "No existe un alumno con el código '" + codigo + "'."),
          codigo_(codigo) {}

    const std::string& codigo_buscado() const noexcept { return codigo_; }

private:
    std::string codigo_;
};
