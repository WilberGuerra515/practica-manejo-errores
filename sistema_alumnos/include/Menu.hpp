// Menú interactivo del sistema. Captura y traduce las excepciones a mensajes.
// Responsable: Cristhian
#pragma once

#include <iostream>

#include "GestorAlumnos.hpp"
#include "RepositorioAlumnos.hpp"

class Menu {
public:
    Menu(GestorAlumnos& gestor, RepositorioAlumnos& repositorio,
         std::istream& in = std::cin, std::ostream& out = std::cout);

    /// Bucle principal. Termina con la opción 0 o si se cierra la entrada (EOF).
    void ejecutar();

private:
    void mostrarOpciones() const;
    void registrar();
    void buscar();
    void eliminar();
    void listar() const;
    void guardarCambios();

    GestorAlumnos& gestor_;
    RepositorioAlumnos& repositorio_;
    std::istream& in_;
    std::ostream& out_;
};
