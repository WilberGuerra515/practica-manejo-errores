// Persistencia de alumnos en un archivo CSV.
// Formato: primera línea "codigo,nombre,edad,carrera" y una fila por alumno.
// Responsable: Diego
#pragma once

#include <string>
#include <vector>

#include "Alumno.hpp"

class RepositorioAlumnos {
public:
    explicit RepositorioAlumnos(std::string ruta);

    /// Lee todos los alumnos.
    /// @throws ArchivoNoEncontradoException si el archivo no existe o no se puede abrir.
    /// @throws ArchivoCorruptoException si hay cabecera/filas inválidas (indica la línea).
    std::vector<Alumno> cargar() const;

    /// Sobrescribe el archivo con los alumnos dados (crea carpetas si hace falta).
    /// @throws std::runtime_error si no se puede escribir.
    void guardar(const std::vector<Alumno>& alumnos) const;

    const std::string& ruta() const { return ruta_; }

    static const char* cabecera() { return "codigo,nombre,edad,carrera"; }

private:
    std::string ruta_;
};
