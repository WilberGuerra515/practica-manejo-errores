// Responsable: Cristhian
#include "Logger.hpp"

#include <ctime>
#include <filesystem>
#include <fstream>

void Logger::configurar(const std::string& nuevaRuta) { ruta() = nuevaRuta; }

std::string& Logger::ruta() {
    static std::string r = "logs/errores.log";
    return r;
}

void Logger::info(const std::string& mensaje) { escribir("INFO", mensaje); }
void Logger::advertencia(const std::string& mensaje) { escribir("AVISO", mensaje); }
void Logger::error(const std::string& mensaje) { escribir("ERROR", mensaje); }

void Logger::escribir(const char* nivel, const std::string& mensaje) {
    // Un fallo al registrar nunca debe tumbar el programa: se ignora en silencio.
    try {
        std::filesystem::path destino(ruta());
        if (destino.has_parent_path()) {
            std::error_code ec;
            std::filesystem::create_directories(destino.parent_path(), ec);
        }
        std::ofstream archivo(destino, std::ios::app);
        if (!archivo) {
            return;
        }

        std::time_t ahora = std::time(nullptr);
        std::tm fecha{};
#ifdef _WIN32
        localtime_s(&fecha, &ahora);
#else
        localtime_r(&ahora, &fecha);
#endif
        char marca[32];
        std::strftime(marca, sizeof(marca), "%Y-%m-%d %H:%M:%S", &fecha);

        archivo << marca << " [" << nivel << "] " << mensaje << "\n";
    } catch (...) {
    }
}
