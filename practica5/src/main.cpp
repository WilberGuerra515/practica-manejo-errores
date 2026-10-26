// Práctica 5 - Excepciones personalizadas.
// Pide una edad, lanza EdadInvalidaException si no está entre 0 y 120
// y la captura mostrando "Edad fuera de rango".
// Responsable: Jaime
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

#include "EdadInvalidaException.hpp"
#include "validador_edad.hpp"

namespace {

/// Convierte el texto a entero; lanza std::invalid_argument si no es un número válido.
int convertirAEntero(const std::string& texto) {
    std::size_t pos = 0;
    int valor = 0;
    try {
        valor = std::stoi(texto, &pos);  // invalid_argument / out_of_range
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("número fuera de límites");
    }
    while (pos < texto.size() && std::isspace(static_cast<unsigned char>(texto[pos]))) {
        ++pos;
    }
    if (pos != texto.size()) {
        throw std::invalid_argument("texto con caracteres no numéricos");
    }
    return valor;
}

}  // namespace

int main() {
    std::cout << "=== Práctica 5: Excepciones personalizadas ===\n"
              << "Escriba 'salir' para terminar.\n\n";

    std::string linea;
    while (true) {
        std::cout << "Ingrese una edad: ";
        if (!std::getline(std::cin, linea) || linea == "salir") {
            break;
        }

        try {
            int edad = convertirAEntero(linea);
            validarEdad(edad);  // puede lanzar EdadInvalidaException
            std::cout << "Edad válida: " << edad << "\n";
        } catch (const EdadInvalidaException& e) {
            std::cout << "Edad fuera de rango\n";
            std::cout << "  (detalle técnico: " << e.what() << ")\n";
        } catch (const std::invalid_argument&) {
            std::cout << "Debe ingresar un número válido.\n";
        }
    }

    std::cout << "Programa finalizado.\n";
    return 0;
}
