// Responsable: Cristhian
#include "Validador.hpp"

#include <stdexcept>

#include "excepciones/EdadInvalidaException.hpp"

namespace {

std::string leerLinea(std::istream& in) {
    std::string linea;
    if (!std::getline(in, linea)) {
        throw std::ios_base::failure("Entrada finalizada");
    }
    return linea;
}

}  // namespace

std::string Validador::recortar(const std::string& texto) {
    const char* espacios = " \t\r\n";
    std::size_t inicio = texto.find_first_not_of(espacios);
    if (inicio == std::string::npos) {
        return "";
    }
    std::size_t fin = texto.find_last_not_of(espacios);
    return texto.substr(inicio, fin - inicio + 1);
}

int Validador::parseEntero(const std::string& texto) {
    std::string limpio = recortar(texto);
    if (limpio.empty()) {
        throw std::invalid_argument("texto vacío");
    }
    std::size_t pos = 0;
    int valor = 0;
    try {
        valor = std::stoi(limpio, &pos);  // lanza invalid_argument si no hay dígitos
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("número fuera de límites");
    }
    if (pos != limpio.size()) {
        throw std::invalid_argument("caracteres no numéricos");
    }
    return valor;
}

void Validador::validarEdad(int edad) {
    if (edad < 0 || edad > 120) {
        throw EdadInvalidaException(edad);
    }
}

int Validador::leerEntero(const std::string& mensaje, std::istream& in, std::ostream& out) {
    while (true) {
        out << mensaje;
        std::string linea = leerLinea(in);
        try {
            return parseEntero(linea);
        } catch (const std::invalid_argument&) {
            out << "Debe ingresar un número válido.\n";
        }
    }
}

int Validador::leerEnteroEnRango(const std::string& mensaje, int min, int max,
                                 std::istream& in, std::ostream& out) {
    while (true) {
        int valor = leerEntero(mensaje, in, out);
        if (valor >= min && valor <= max) {
            return valor;
        }
        out << "El valor debe estar entre " << min << " y " << max << ".\n";
    }
}

std::string Validador::leerTexto(const std::string& mensaje, std::istream& in,
                                 std::ostream& out) {
    while (true) {
        out << mensaje;
        std::string texto = recortar(leerLinea(in));
        if (texto.empty()) {
            out << "Este campo no puede estar vacío.\n";
        } else if (texto.find(',') != std::string::npos) {
            out << "No se permiten comas en este campo.\n";
        } else {
            return texto;
        }
    }
}
