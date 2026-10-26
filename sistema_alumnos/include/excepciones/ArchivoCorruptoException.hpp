#pragma once

#include <string>

#include "SistemaException.hpp"

/// Se lanza cuando el archivo existe pero su contenido es inválido.
class ArchivoCorruptoException : public SistemaException {
public:
    ArchivoCorruptoException(const std::string& ruta, int linea, const std::string& detalle)
        : SistemaException(3002, "Archivo corrupto '" + ruta + "' (línea " +
                                     std::to_string(linea) + "): " + detalle),
          ruta_(ruta),
          linea_(linea) {}

    const std::string& ruta() const noexcept { return ruta_; }
    int linea() const noexcept { return linea_; }

private:
    std::string ruta_;
    int linea_;
};
