// Pruebas de Validador (entrada de datos). Responsable: Cristhian
#include <ios>
#include <sstream>
#include <stdexcept>

#include "Validador.hpp"
#include "excepciones/EdadInvalidaException.hpp"
#include "test_util.hpp"

int main() {
    // recortar
    CHECK(Validador::recortar("  hola \t\n") == "hola");
    CHECK(Validador::recortar("   ") == "");

    // parseEntero
    CHECK(Validador::parseEntero("42") == 42);
    CHECK(Validador::parseEntero("  -7 ") == -7);
    CHECK_THROWS(Validador::parseEntero("abc"), std::invalid_argument);
    CHECK_THROWS(Validador::parseEntero("12abc"), std::invalid_argument);
    CHECK_THROWS(Validador::parseEntero("3.5"), std::invalid_argument);
    CHECK_THROWS(Validador::parseEntero(""), std::invalid_argument);
    CHECK_THROWS(Validador::parseEntero("99999999999999"), std::invalid_argument);

    // validarEdad
    CHECK_NO_THROW(Validador::validarEdad(0));
    CHECK_NO_THROW(Validador::validarEdad(120));
    CHECK_THROWS(Validador::validarEdad(-1), EdadInvalidaException);
    CHECK_THROWS(Validador::validarEdad(121), EdadInvalidaException);

    // leerEntero: reintenta hasta recibir un número válido
    {
        std::istringstream in("hola\n\n3.5\n18\n");
        std::ostringstream out;
        CHECK(Validador::leerEntero("Edad: ", in, out) == 18);
        CHECK(out.str().find("Debe ingresar un número válido.") != std::string::npos);
    }

    // leerEnteroEnRango
    {
        std::istringstream in("9\n-1\n3\n");
        std::ostringstream out;
        CHECK(Validador::leerEnteroEnRango("Opción: ", 0, 4, in, out) == 3);
        CHECK(out.str().find("entre 0 y 4") != std::string::npos);
    }

    // leerTexto: rechaza vacío y comas
    {
        std::istringstream in("\n   \nGarcía, Ana\n  Ana García  \n");
        std::ostringstream out;
        CHECK(Validador::leerTexto("Nombre: ", in, out) == "Ana García");
        CHECK(out.str().find("no puede estar vacío") != std::string::npos);
        CHECK(out.str().find("No se permiten comas") != std::string::npos);
    }

    // EOF: debe lanzar en lugar de quedar en bucle infinito
    {
        std::istringstream in("abc\n");
        std::ostringstream out;
        CHECK_THROWS(Validador::leerEntero("N: ", in, out), std::ios_base::failure);
    }

    return resumen("test_validador");
}
