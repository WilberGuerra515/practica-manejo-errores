// Práctica 5 - Validación de edad.
// Responsable: Jaime
#include "validador_edad.hpp"

#include "EdadInvalidaException.hpp"

void validarEdad(int edad) {
    if (edad < EDAD_MINIMA || edad > EDAD_MAXIMA) {
        throw EdadInvalidaException(edad);
    }
}
