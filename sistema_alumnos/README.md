# Sistema de registro de alumnos

Mini-sistema por consola que registra, busca, elimina y lista alumnos, guardando los
datos en `data/alumnos.csv`. El foco es el **manejo de errores**.

## Uso

```bash
# desde la raíz del repositorio
make sistema_alumnos
./build/sistema_alumnos
```

Menú: `1` Registrar · `2` Buscar · `3` Eliminar · `4` Listar · `0` Salir.
Los cambios se guardan automáticamente tras registrar o eliminar.

## Arquitectura

| Componente | Archivo | Rol |
|---|---|---|
| Excepciones | `include/excepciones/*.hpp` | Jerarquía basada en `SistemaException` |
| `Alumno` | `Alumno.hpp/.cpp` | Entidad de datos |
| `GestorAlumnos` | `GestorAlumnos.hpp/.cpp` | Reglas de negocio (edad, duplicados, no encontrado) |
| `RepositorioAlumnos` | `RepositorioAlumnos.hpp/.cpp` | Lectura/escritura CSV (no encontrado / corrupto) |
| `Validador` | `Validador.hpp/.cpp` | Lectura segura de datos de entrada |
| `Logger` | `Logger.hpp/.cpp` | Registro en `logs/errores.log` |
| `Menu` | `Menu.hpp/.cpp` | Interfaz y captura de excepciones |
| `main.cpp` | `main.cpp` | Carga inicial e integración |

```
SistemaException (std::exception)
├── EdadInvalidaException           1001
├── AlumnoNoEncontradoException     2001
├── AlumnoDuplicadoException        2002
├── ArchivoNoEncontradoException    3001
└── ArchivoCorruptoException        3002
```

## Formato del archivo de datos

```
codigo,nombre,edad,carrera
A001,Ana Torres,20,Ingeniería de Sistemas
```

- `data/alumnos.csv`: datos válidos de ejemplo.
- `data/alumnos_corrupto.csv`: filas mal formadas para probar `ArchivoCorruptoException`.

Los errores y su tratamiento están en [`../docs/catalogo_errores.md`](../docs/catalogo_errores.md).
