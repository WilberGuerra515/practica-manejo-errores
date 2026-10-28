// Pruebas de la Práctica 5. Responsable: Jaime
#include <string>

#include "EdadInvalidaException.hpp"
#include "test_util.hpp"
#include "validador_edad.hpp"

int main() {
    // Valores válidos (incluye los límites)
    CHECK_NO_THROW(validarEdad(0));
    CHECK_NO_THROW(validarEdad(25));
    CHECK_NO_THROW(validarEdad(120));

    // Valores inválidos
    CHECK_THROWS(validarEdad(-1), EdadInvalidaException);
    CHECK_THROWS(validarEdad(121), EdadInvalidaException);
    CHECK_THROWS(validarEdad(-500), EdadInvalidaException);
    CHECK_THROWS(validarEdad(1000), EdadInvalidaException);

    // La excepción conserva la edad y un mensaje útil
    try {
        validarEdad(150);
        CHECK(false);
    } catch (const EdadInvalidaException& e) {
        CHECK(e.edad() == 150);
        CHECK(std::string(e.what()).find("150") != std::string::npos);
        CHECK(std::string(e.what()).find("fuera de rango") != std::string::npos);
    }

    return resumen("test_practica5");
}
