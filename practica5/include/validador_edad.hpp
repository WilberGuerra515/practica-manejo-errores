// Práctica 5 - Validación de edad.
// Responsable: Jaime
#pragma once

constexpr int EDAD_MINIMA = 0;
constexpr int EDAD_MAXIMA = 120;

/// Lanza EdadInvalidaException si edad < 0 o edad > 120.
void validarEdad(int edad);
