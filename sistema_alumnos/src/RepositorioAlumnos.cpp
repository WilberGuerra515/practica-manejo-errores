// Responsable: Diego
#include "RepositorioAlumnos.hpp"

#include <filesystem>
#include <fstream>
#include <set>
#include <stdexcept>

#include "Validador.hpp"
#include "excepciones/ArchivoCorruptoException.hpp"
#include "excepciones/ArchivoNoEncontradoException.hpp"
#include "excepciones/EdadInvalidaException.hpp"

namespace {

/// Divide por comas conservando los campos vacíos ("a,,b," -> 4 campos).
std::vector<std::string> dividir(const std::string& linea) {
    std::vector<std::string> campos;
    std::size_t inicio = 0;
    while (true) {
        std::size_t coma = linea.find(',', inicio);
        if (coma == std::string::npos) {
            campos.push_back(linea.substr(inicio));
            break;
        }
        campos.push_back(linea.substr(inicio, coma - inicio));
        inicio = coma + 1;
    }
    return campos;
}

std::string sinRetornoDeCarro(std::string linea) {
    if (!linea.empty() && linea.back() == '\r') {
        linea.pop_back();
    }
    return linea;
}

}  // namespace

RepositorioAlumnos::RepositorioAlumnos(std::string ruta) : ruta_(std::move(ruta)) {}

std::vector<Alumno> RepositorioAlumnos::cargar() const {
    std::ifstream archivo(ruta_);
    if (!archivo.is_open()) {
        throw ArchivoNoEncontradoException(ruta_);
    }

    std::string linea;
    int numero = 0;

    // Cabecera obligatoria
    if (!std::getline(archivo, linea)) {
        throw ArchivoCorruptoException(ruta_, 1, "el archivo está vacío (falta la cabecera)");
    }
    ++numero;
    if (sinRetornoDeCarro(linea) != cabecera()) {
        throw ArchivoCorruptoException(
            ruta_, numero, std::string("cabecera inválida, se esperaba '") + cabecera() + "'");
    }

    std::vector<Alumno> alumnos;
    std::set<std::string> codigos;

    while (std::getline(archivo, linea)) {
        ++numero;
        linea = sinRetornoDeCarro(linea);
        if (Validador::recortar(linea).empty()) {
            continue;  // se ignoran líneas en blanco
        }

        std::vector<std::string> campos = dividir(linea);
        if (campos.size() != 4) {
            throw ArchivoCorruptoException(
                ruta_, numero,
                "se esperaban 4 columnas y se encontraron " + std::to_string(campos.size()));
        }
        for (std::string& campo : campos) {
            campo = Validador::recortar(campo);
        }
        if (campos[0].empty() || campos[1].empty() || campos[3].empty()) {
            throw ArchivoCorruptoException(ruta_, numero, "hay campos obligatorios vacíos");
        }

        int edad = 0;
        try {
            edad = Validador::parseEntero(campos[2]);
        } catch (const std::invalid_argument&) {
            throw ArchivoCorruptoException(ruta_, numero,
                                           "la edad '" + campos[2] + "' no es numérica");
        }
        try {
            Validador::validarEdad(edad);
        } catch (const EdadInvalidaException&) {
            throw ArchivoCorruptoException(ruta_, numero,
                                           "la edad " + std::to_string(edad) +
                                               " está fuera de rango (0-120)");
        }
        if (!codigos.insert(campos[0]).second) {
            throw ArchivoCorruptoException(ruta_, numero,
                                           "código repetido '" + campos[0] + "'");
        }

        alumnos.emplace_back(campos[0], campos[1], edad, campos[3]);
    }

    return alumnos;
}

void RepositorioAlumnos::guardar(const std::vector<Alumno>& alumnos) const {
    std::filesystem::path destino(ruta_);
    if (destino.has_parent_path()) {
        std::error_code ec;
        std::filesystem::create_directories(destino.parent_path(), ec);
    }

    std::ofstream archivo(destino, std::ios::trunc);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir '" + ruta_ + "' para escritura.");
    }

    archivo << cabecera() << "\n";
    for (const Alumno& a : alumnos) {
        archivo << a.codigo() << ',' << a.nombre() << ',' << a.edad() << ',' << a.carrera()
                << "\n";
    }
    archivo.flush();
    if (!archivo) {
        throw std::runtime_error("Error al escribir en '" + ruta_ + "'.");
    }
}
