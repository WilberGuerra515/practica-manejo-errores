// Responsable: Cristhian
#include "Menu.hpp"

#include <string>
#include <stdexcept>

#include "Logger.hpp"
#include "Validador.hpp"
#include "excepciones/AlumnoDuplicadoException.hpp"
#include "excepciones/AlumnoNoEncontradoException.hpp"
#include "excepciones/EdadInvalidaException.hpp"
#include "excepciones/SistemaException.hpp"

namespace {

/// Rellena con espacios hasta 'ancho' caracteres visibles (cuenta UTF-8, no bytes).
std::string rellenar(const std::string& texto, std::size_t ancho) {
    std::size_t visibles = 0;
    for (unsigned char c : texto) {
        if ((c & 0xC0) != 0x80) {
            ++visibles;
        }
    }
    return visibles >= ancho ? texto + " " : texto + std::string(ancho - visibles, ' ');
}

}  // namespace

Menu::Menu(GestorAlumnos& gestor, RepositorioAlumnos& repositorio, std::istream& in,
           std::ostream& out)
    : gestor_(gestor), repositorio_(repositorio), in_(in), out_(out) {}

void Menu::mostrarOpciones() const {
    out_ << "\n===== SISTEMA DE REGISTRO DE ALUMNOS =====\n"
         << " 1. Registrar alumno\n"
         << " 2. Buscar alumno por código\n"
         << " 3. Eliminar alumno\n"
         << " 4. Listar alumnos\n"
         << " 0. Salir\n";
}

void Menu::ejecutar() {
    try {
        while (true) {
            mostrarOpciones();
            int opcion = Validador::leerEnteroEnRango("Seleccione una opción: ", 0, 4, in_, out_);
            if (opcion == 0) {
                out_ << "Hasta pronto.\n";
                return;
            }

            try {
                switch (opcion) {
                    case 1: registrar(); break;
                    case 2: buscar(); break;
                    case 3: eliminar(); break;
                    case 4: listar(); break;
                    default: break;
                }
            } catch (const EdadInvalidaException& e) {
                out_ << "Edad fuera de rango. " << e.what() << "\n";
                Logger::advertencia(std::string("EdadInvalidaException: ") + e.what());
            } catch (const AlumnoNoEncontradoException& e) {
                out_ << "Error: " << e.what() << "\n";
                Logger::advertencia(std::string("AlumnoNoEncontradoException: ") + e.what());
            } catch (const AlumnoDuplicadoException& e) {
                out_ << "Error: " << e.what() << " No se registró.\n";
                Logger::advertencia(std::string("AlumnoDuplicadoException: ") + e.what());
            } catch (const std::ios_base::failure&) {
                throw;  // entrada cerrada: se maneja afuera
            } catch (const SistemaException& e) {
                out_ << "Error del sistema [" << e.codigo() << "]: " << e.what() << "\n";
                Logger::error(std::string("SistemaException: ") + e.what());
            } catch (const std::exception& e) {
                out_ << "Error inesperado: " << e.what() << "\n";
                Logger::error(std::string("Error inesperado: ") + e.what());
            }
        }
    } catch (const std::ios_base::failure&) {
        out_ << "\nLa entrada se cerró. Finalizando el programa.\n";
    }
}

void Menu::registrar() {
    out_ << "\n--- Registrar alumno ---\n";
    std::string codigo = Validador::leerTexto("Código: ", in_, out_);
    std::string nombre = Validador::leerTexto("Nombre: ", in_, out_);
    int edad = Validador::leerEntero("Edad: ", in_, out_);
    std::string carrera = Validador::leerTexto("Carrera: ", in_, out_);

    gestor_.registrar(codigo, nombre, edad, carrera);  // puede lanzar excepciones
    out_ << "Alumno registrado correctamente.\n";
    guardarCambios();
}

void Menu::buscar() {
    out_ << "\n--- Buscar alumno ---\n";
    std::string codigo = Validador::leerTexto("Código: ", in_, out_);
    out_ << gestor_.buscar(codigo).descripcion() << "\n";
}

void Menu::eliminar() {
    out_ << "\n--- Eliminar alumno ---\n";
    std::string codigo = Validador::leerTexto("Código: ", in_, out_);
    gestor_.eliminar(codigo);
    out_ << "Alumno eliminado.\n";
    guardarCambios();
}

void Menu::listar() const {
    out_ << "\n--- Lista de alumnos (" << gestor_.cantidad() << ") ---\n";
    if (gestor_.cantidad() == 0) {
        out_ << "No hay alumnos registrados.\n";
        return;
    }
    out_ << rellenar("Código", 10) << rellenar("Nombre", 24) << rellenar("Edad", 6)
         << "Carrera\n";
    for (const Alumno& a : gestor_.listar()) {
        out_ << rellenar(a.codigo(), 10) << rellenar(a.nombre(), 24)
             << rellenar(std::to_string(a.edad()), 6) << a.carrera() << "\n";
    }
}

void Menu::guardarCambios() {
    try {
        repositorio_.guardar(gestor_.listar());
    } catch (const std::exception& e) {
        out_ << "Aviso: los cambios NO se pudieron guardar en el archivo (" << e.what()
             << ").\n";
        Logger::error(std::string("Fallo al guardar: ") + e.what());
    }
}
