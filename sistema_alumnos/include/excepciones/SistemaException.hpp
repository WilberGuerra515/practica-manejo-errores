// Clase base de todas las excepciones del sistema de alumnos.
#pragma once

#include <exception>
#include <string>
#include <utility>

/// Excepción base: lleva un mensaje y un código numérico de error.
///
/// Códigos usados en el sistema:
///   1001 Edad inválida            2001 Alumno no encontrado
///   2002 Alumno duplicado         3001 Archivo no encontrado
///   3002 Archivo corrupto
class SistemaException : public std::exception {
public:
    SistemaException(int codigo, std::string mensaje)
        : codigo_(codigo), mensaje_(std::move(mensaje)) {}

    const char* what() const noexcept override { return mensaje_.c_str(); }
    int codigo() const noexcept { return codigo_; }

private:
    int codigo_;
    std::string mensaje_;
};
