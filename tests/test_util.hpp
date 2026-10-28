// Mini-framework de pruebas (sin dependencias externas).
#pragma once

#include <iostream>

inline int g_fallos = 0;
inline int g_pruebas = 0;

#define CHECK(cond)                                                                  \
    do {                                                                             \
        ++g_pruebas;                                                                 \
        if (!(cond)) {                                                               \
            ++g_fallos;                                                              \
            std::cerr << "  FALLO " << __FILE__ << ":" << __LINE__ << " -> " #cond   \
                      << "\n";                                                       \
        }                                                                            \
    } while (0)

#define CHECK_THROWS(expr, Tipo)                                                     \
    do {                                                                             \
        ++g_pruebas;                                                                 \
        bool lanzo_ = false;                                                         \
        try {                                                                        \
            expr;                                                                    \
        } catch (const Tipo&) {                                                      \
            lanzo_ = true;                                                           \
        } catch (...) {                                                              \
        }                                                                            \
        if (!lanzo_) {                                                               \
            ++g_fallos;                                                              \
            std::cerr << "  FALLO " << __FILE__ << ":" << __LINE__                    \
                      << " -> se esperaba " #Tipo " en: " #expr "\n";                \
        }                                                                            \
    } while (0)

#define CHECK_NO_THROW(expr)                                                         \
    do {                                                                             \
        ++g_pruebas;                                                                 \
        try {                                                                        \
            expr;                                                                    \
        } catch (...) {                                                              \
            ++g_fallos;                                                              \
            std::cerr << "  FALLO " << __FILE__ << ":" << __LINE__                   \
                      << " -> no debía lanzar: " #expr "\n";                         \
        }                                                                            \
    } while (0)

inline int resumen(const char* nombre) {
    std::cout << nombre << ": " << (g_pruebas - g_fallos) << "/" << g_pruebas
              << " comprobaciones correctas\n";
    return g_fallos == 0 ? 0 : 1;
}
