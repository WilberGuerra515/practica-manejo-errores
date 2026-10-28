// Pruebas de RepositorioAlumnos (archivo inexistente / corrupto). Responsable: Diego
#include <filesystem>
#include <fstream>
#include <string>

#include "RepositorioAlumnos.hpp"
#include "excepciones/ArchivoCorruptoException.hpp"
#include "excepciones/ArchivoNoEncontradoException.hpp"
#include "test_util.hpp"

namespace fs = std::filesystem;

static std::string escribir(const fs::path& carpeta, const std::string& nombre,
                            const std::string& contenido) {
    fs::path ruta = carpeta / nombre;
    std::ofstream(ruta) << contenido;
    return ruta.string();
}

/// Devuelve la línea reportada por ArchivoCorruptoException, o -1 si no se lanzó.
static int lineaDelError(const std::string& ruta) {
    try {
        RepositorioAlumnos(ruta).cargar();
    } catch (const ArchivoCorruptoException& e) {
        return e.linea();
    } catch (...) {
    }
    return -1;
}

int main() {
    fs::path tmp = fs::temp_directory_path() / "test_repositorio_alumnos";
    fs::remove_all(tmp);
    fs::create_directories(tmp);

    const std::string cab = "codigo,nombre,edad,carrera\n";

    // Archivo inexistente
    CHECK_THROWS(RepositorioAlumnos((tmp / "no_existe.csv").string()).cargar(),
                 ArchivoNoEncontradoException);

    // Archivo válido
    {
        std::string r = escribir(tmp, "ok.csv", cab + "A001,Ana,20,Sistemas\nA002,Luis,22,Civil\n");
        auto alumnos = RepositorioAlumnos(r).cargar();
        CHECK(alumnos.size() == 2);
        CHECK(alumnos[0].codigo() == "A001");
        CHECK(alumnos[1].edad() == 22);
    }

    // Archivo con CRLF y línea en blanco: se tolera
    {
        std::string r = escribir(tmp, "crlf.csv", "codigo,nombre,edad,carrera\r\nA001,Ana,20,Sistemas\r\n\r\n");
        CHECK(RepositorioAlumnos(r).cargar().size() == 1);
    }

    // Casos corruptos (con número de línea esperado)
    CHECK(lineaDelError(escribir(tmp, "vacio.csv", "")) == 1);
    CHECK(lineaDelError(escribir(tmp, "cab.csv", "a,b,c\nA001,Ana,20,Sis\n")) == 1);
    CHECK(lineaDelError(escribir(tmp, "cols.csv", cab + "A001,Ana,20,Sis\nA002,Luis,22\n")) == 3);
    CHECK(lineaDelError(escribir(tmp, "edad_txt.csv", cab + "A001,Ana,veinte,Sis\n")) == 2);
    CHECK(lineaDelError(escribir(tmp, "edad_rango.csv", cab + "A001,Ana,200,Sis\n")) == 2);
    CHECK(lineaDelError(escribir(tmp, "dup.csv", cab + "A001,Ana,20,Sis\nA001,Otra,21,Sis\n")) == 3);
    CHECK(lineaDelError(escribir(tmp, "vacios.csv", cab + "A001,,20,Sis\n")) == 2);

    // Guardar y volver a cargar (ida y vuelta), creando carpetas intermedias
    {
        std::string r = (tmp / "sub" / "carpeta" / "salida.csv").string();
        RepositorioAlumnos repo(r);
        repo.guardar({Alumno("B001", "Rosa", 30, "Derecho"), Alumno("B002", "Pedro", 18, "Medicina")});
        auto leidos = repo.cargar();
        CHECK(leidos.size() == 2);
        CHECK(leidos[0].nombre() == "Rosa");
        CHECK(leidos[1].carrera() == "Medicina");
    }

    // Los archivos de ejemplo del proyecto (si se ejecuta desde la raíz)
    if (fs::exists("sistema_alumnos/data/alumnos.csv")) {
        CHECK(RepositorioAlumnos("sistema_alumnos/data/alumnos.csv").cargar().size() == 5);
        CHECK(lineaDelError("sistema_alumnos/data/alumnos_corrupto.csv") == 3);
    }

    fs::remove_all(tmp);
    return resumen("test_repositorio");
}
