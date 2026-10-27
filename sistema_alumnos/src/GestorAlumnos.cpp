// Responsable: Jhon
#include "GestorAlumnos.hpp"

#include <algorithm>

#include "Validador.hpp"
#include "excepciones/AlumnoDuplicadoException.hpp"
#include "excepciones/AlumnoNoEncontradoException.hpp"

std::vector<Alumno>::const_iterator GestorAlumnos::encontrar(const std::string& codigo) const {
    return std::find_if(alumnos_.begin(), alumnos_.end(),
                        [&](const Alumno& a) { return a.codigo() == codigo; });
}

void GestorAlumnos::registrar(const std::string& codigo, const std::string& nombre, int edad,
                              const std::string& carrera) {
    Validador::validarEdad(edad);  // lanza EdadInvalidaException
    if (encontrar(codigo) != alumnos_.end()) {
        throw AlumnoDuplicadoException(codigo);
    }
    alumnos_.emplace_back(codigo, nombre, edad, carrera);
}

const Alumno& GestorAlumnos::buscar(const std::string& codigo) const {
    auto it = encontrar(codigo);
    if (it == alumnos_.end()) {
        throw AlumnoNoEncontradoException(codigo);
    }
    return *it;
}

void GestorAlumnos::eliminar(const std::string& codigo) {
    auto it = encontrar(codigo);
    if (it == alumnos_.end()) {
        throw AlumnoNoEncontradoException(codigo);
    }
    alumnos_.erase(alumnos_.begin() + (it - alumnos_.cbegin()));
}
