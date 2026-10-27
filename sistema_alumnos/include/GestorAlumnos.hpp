// Lógica de negocio: registrar, buscar, eliminar y listar alumnos.
// Responsable: Jhon
#pragma once

#include <cstddef>
#include <utility>
#include <string>
#include <vector>

#include "Alumno.hpp"

class GestorAlumnos {
public:
    /// @throws EdadInvalidaException si la edad no está entre 0 y 120.
    /// @throws AlumnoDuplicadoException si el código ya existe.
    void registrar(const std::string& codigo, const std::string& nombre, int edad,
                   const std::string& carrera);

    /// @throws AlumnoNoEncontradoException si el código no existe.
    const Alumno& buscar(const std::string& codigo) const;

    /// @throws AlumnoNoEncontradoException si el código no existe.
    void eliminar(const std::string& codigo);

    const std::vector<Alumno>& listar() const { return alumnos_; }
    std::size_t cantidad() const { return alumnos_.size(); }

    /// Reemplaza todo el contenido (usado al cargar desde archivo).
    void reemplazarTodos(std::vector<Alumno> alumnos) { alumnos_ = std::move(alumnos); }

private:
    std::vector<Alumno>::const_iterator encontrar(const std::string& codigo) const;

    std::vector<Alumno> alumnos_;
};
