# Práctica 5 – Excepciones personalizadas (C++)

**Objetivo:** crear y lanzar una excepción propia.

| Requisito | Implementación |
|---|---|
| Crear `EdadInvalidaException` | `include/EdadInvalidaException.hpp` (hereda de `std::exception`) |
| Lanzarla si edad < 0 o > 120 | `src/validador_edad.cpp` → `validarEdad(int)` |
| Capturarla y mostrar "Edad fuera de rango" | `src/main.cpp` (bloque `catch`) |

Además se controla la entrada no numérica (`std::invalid_argument`) mostrando
"Debe ingresar un número válido."

## Compilar y ejecutar

Desde la raíz del repositorio:

```bash
make practica5
./build/practica5
```

o con CMake:

```bash
cmake -B build && cmake --build build
./build/practica5
```

## Ejemplo de ejecución

```
Ingrese una edad: 25
Edad válida: 25
Ingrese una edad: 150
Edad fuera de rango
  (detalle técnico: Edad fuera de rango: 150 (valores permitidos: 0 a 120))
Ingrese una edad: -3
Edad fuera de rango
  (detalle técnico: Edad fuera de rango: -3 (valores permitidos: 0 a 120))
Ingrese una edad: abc
Debe ingresar un número válido.
Ingrese una edad: salir
Programa finalizado.
```
