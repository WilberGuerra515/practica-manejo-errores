// Entidad Alumno.
// Responsable: Jhon
#pragma once

#include <string>

class Alumno {
public:
    Alumno(std::string codigo, std::string nombre, int edad, std::string carrera);

    const std::string& codigo() const { return codigo_; }
    const std::string& nombre() const { return nombre_; }
    int edad() const { return edad_; }
    const std::string& carrera() const { return carrera_; }

    /// Texto legible: "[A001] Ana Torres | 20 años | Sistemas".
    std::string descripcion() const;

private:
    std::string codigo_;
    std::string nombre_;
    int edad_;
    std::string carrera_;
};
