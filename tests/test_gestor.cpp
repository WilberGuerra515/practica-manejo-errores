// Pruebas de GestorAlumnos (alumno no encontrado, duplicado, edad). Responsable: Jhon
#include "GestorAlumnos.hpp"
#include "excepciones/AlumnoDuplicadoException.hpp"
#include "excepciones/AlumnoNoEncontradoException.hpp"
#include "excepciones/EdadInvalidaException.hpp"
#include "excepciones/SistemaException.hpp"
#include "test_util.hpp"

int main() {
    GestorAlumnos g;
    CHECK(g.cantidad() == 0);

    // Registrar y buscar
    CHECK_NO_THROW(g.registrar("A001", "Ana Torres", 20, "Sistemas"));
    CHECK_NO_THROW(g.registrar("A002", "Luis Ramírez", 22, "Civil"));
    CHECK(g.cantidad() == 2);
    CHECK(g.buscar("A002").nombre() == "Luis Ramírez");

    // Duplicado
    CHECK_THROWS(g.registrar("A001", "Otra Persona", 30, "Derecho"), AlumnoDuplicadoException);
    CHECK(g.cantidad() == 2);

    // Edad inválida: no se registra
    CHECK_THROWS(g.registrar("A003", "Pedro", -5, "Medicina"), EdadInvalidaException);
    CHECK_THROWS(g.registrar("A003", "Pedro", 121, "Medicina"), EdadInvalidaException);
    CHECK(g.cantidad() == 2);
    CHECK_NO_THROW(g.registrar("A003", "Pedro", 120, "Medicina"));  // límite válido

    // Buscar inexistente
    CHECK_THROWS(g.buscar("ZZZ"), AlumnoNoEncontradoException);

    // Todas las excepciones del sistema son capturables como SistemaException
    CHECK_THROWS(g.buscar("ZZZ"), SistemaException);
    try {
        g.buscar("ZZZ");
    } catch (const SistemaException& e) {
        CHECK(e.codigo() == 2001);
    }

    // Eliminar
    CHECK_NO_THROW(g.eliminar("A001"));
    CHECK(g.cantidad() == 2);
    CHECK_THROWS(g.buscar("A001"), AlumnoNoEncontradoException);
    CHECK_THROWS(g.eliminar("A001"), AlumnoNoEncontradoException);

    // Reemplazar todos
    g.reemplazarTodos({});
    CHECK(g.cantidad() == 0);

    return resumen("test_gestor");
}
