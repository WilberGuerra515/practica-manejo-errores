#pragma once

#include <string>

#include "SistemaException.hpp"

/// Se lanza cuando el archivo de datos no existe o no se puede abrir.
class ArchivoNoEncontradoException : public SistemaException {
public:
    explicit ArchivoNoEncontradoException(const std::string& ruta)
        : SistemaException(3001, "No se encontró el archivo '" + ruta + "'."),
          ruta_(ruta) {}

    const std::string& ruta() const noexcept { return ruta_; }

private:
    std::string ruta_;
};