# Casos de prueba

## Automáticos (`make test` / `ctest`)

| Suite | Qué verifica |
|---|---|
| `test_practica5` | Límites 0 y 120 válidos; -1 y 121 lanzan `EdadInvalidaException`; el mensaje contiene la edad |
| `test_validador` | `parseEntero`, `validarEdad`, reintentos de lectura, rechazo de vacío y comas, EOF |
| `test_repositorio` | Archivo inexistente, válido, con CRLF, vacío, cabecera mala, columnas faltantes, edad no numérica/fuera de rango, código repetido, ida y vuelta de guardado |
| `test_gestor` | Registro, duplicado, edad inválida (sin registrar), no encontrado, eliminar |

## Manuales

### Práctica 5 (`./build/practica5`)

| # | Entrada | Resultado esperado |
|---|---|---|
| 1 | `25` | `Edad válida: 25` |
| 2 | `0` y `120` | Válidas (límites) |
| 3 | `-1` | `Edad fuera de rango` |
| 4 | `121` | `Edad fuera de rango` |
| 5 | `abc`, `12x`, `3.5`, vacío | `Debe ingresar un número válido.` |
| 6 | `salir` | Termina |

### Sistema de alumnos (`./build/sistema_alumnos`)

| # | Acción | Resultado esperado |
|---|---|---|
| 1 | Menú: `9` o `abc` | Mensaje de error y vuelve a pedir |
| 2 | Registrar con edad `abc` | "Debe ingresar un número válido." y repite la edad |
| 3 | Registrar con edad `300` | "Edad fuera de rango", no se registra |
| 4 | Registrar código `A001` (ya existe) | Error de duplicado |
| 5 | Buscar o eliminar `ZZZ` | "No existe un alumno con el código 'ZZZ'." |
| 6 | Registrar un alumno válido y reabrir el programa | El alumno persiste |
| 7 | Ejecutar con una ruta que no existe | Aviso, lista vacía, archivo creado al guardar |
| 8 | Ejecutar con `data/alumnos_corrupto.csv` | Error con número de línea; responder `n` cancela |
| 9 | Igual que 8 y responder `s` | Se crea `alumnos_corrupto.csv.bak` y se inicia vacío |
| 10 | Cerrar la entrada (Ctrl+D) en cualquier prompt | Finaliza sin colgarse |
