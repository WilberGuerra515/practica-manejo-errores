// Responsable: Jhon
#include "Alumno.hpp"

#include <utility>

Alumno::Alumno(std::string codigo, std::string nombre, int edad, std::string carrera)
    : codigo_(std::move(codigo)),
      nombre_(std::move(nombre)),
      edad_(edad),
      carrera_(std::move(carrera)) {}

std::string Alumno::descripcion() const {
    return "[" + codigo_ + "] " + nombre_ + " | " + std::to_string(edad_) + " años | " +
           carrera_;
}
