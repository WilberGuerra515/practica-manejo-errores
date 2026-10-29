// Validación y lectura segura de datos de entrada.
// Los métodos de lectura reciben los flujos para poder probarlos con stringstream.
// Responsable: Cristhian
#pragma once

#include <iostream>
#include <string>

class Validador {
public:
    /// Quita espacios, tabuladores y saltos de línea al inicio y al final.
    static std::string recortar(const std::string& texto);

    /// Convierte texto a entero. Lanza std::invalid_argument si no es un número válido.
    static int parseEntero(const std::string& texto);

    /// Lanza EdadInvalidaException si edad < 0 o edad > 120.
    static void validarEdad(int edad);

    /// Pide un entero hasta que el usuario escriba uno válido.
    /// Lanza std::ios_base::failure si se cierra la entrada (EOF).
    static int leerEntero(const std::string& mensaje,
                          std::istream& in = std::cin,
                          std::ostream& out = std::cout);

    /// Igual que leerEntero pero exige min <= valor <= max.
    static int leerEnteroEnRango(const std::string& mensaje, int min, int max,
                                 std::istream& in = std::cin,
                                 std::ostream& out = std::cout);

    /// Pide un texto no vacío y sin comas (el CSV usa comas como separador).
    static std::string leerTexto(const std::string& mensaje,
                                 std::istream& in = std::cin,
                                 std::ostream& out = std::cout);
};
