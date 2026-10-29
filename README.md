# Manejo de Errores y Excepciones (C++)

Repositorio del trabajo en grupo de la práctica **PRAC02 – Manejo de Errores**.

- **Práctica 5:** excepciones personalizadas (`EdadInvalidaException`).
- **Simulación de sistema:** Sistema de registro de alumnos con manejo de errores de
  entrada, archivo no encontrado/corrupto y excepciones personalizadas.

## Integrantes

| Integrante | Responsabilidad |
|---|---|
| Gerson | Líder técnico: estructura, build, `main.cpp` del sistema, revisión de PRs |
| Jaime | Práctica 5 completa |
| Wilber | Jerarquía de excepciones |
| Diego | Persistencia en archivo CSV y errores de archivo |
| Jhon | `Alumno` y `GestorAlumnos` |
| Cristhian | `Validador`, `Menu`, `Logger` y documentación |

Detalle en [`docs/reparto_tareas.md`](docs/reparto_tareas.md).

## Requisitos

- Compilador C++17 (g++ 8+, clang 7+ o MSVC 2019+)
- `make` **o** CMake 3.10+

## Compilar

Con Make (Linux/macOS/MinGW):

```bash
make            # compila practica5 y sistema_alumnos en build/
make test       # compila y ejecuta las pruebas
make clean
```

Con CMake:

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Ejecutar

```bash
./build/practica5
./build/sistema_alumnos                              # usa sistema_alumnos/data/alumnos.csv
./build/sistema_alumnos otra/ruta/alumnos.csv        # archivo alternativo
./build/sistema_alumnos sistema_alumnos/data/alumnos_corrupto.csv   # probar archivo corrupto
```

En Windows con CMake/Visual Studio los ejecutables quedan en `build/Debug/` o `build/Release/`.

## Estructura

```
practica5/          Práctica 5 (autónoma)
sistema_alumnos/    Simulación de sistema (include/, src/, data/, logs/)
tests/              Pruebas automáticas (sin librerías externas)
docs/               Catálogo de errores, casos de prueba y reparto de tareas
```

## Convenciones de Git

- Ramas: `main` (estable), `develop` (integración) y una rama por tarea (`feat/...`).
- Mensajes: `feat:`, `fix:`, `docs:`, `test:`, `chore:`.
- Todo cambio entra por Pull Request revisado por otro integrante.
- Cada integrante usa su propio usuario de Git (`git config user.name` / `user.email`).

## Documentación de errores

Ver [`docs/catalogo_errores.md`](docs/catalogo_errores.md) (requisito del enunciado).
