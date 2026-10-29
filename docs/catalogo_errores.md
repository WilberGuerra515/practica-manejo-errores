# Catálogo de errores – Sistema de registro de alumnos

Documentación breve de los errores que puede generar el sistema y cómo se manejan.

## 1. Errores de entrada de datos

| Error | Causa | Detección | Manejo |
|---|---|---|---|
| Entrada no numérica | Se escribe texto donde se espera un número (menú o edad) | `Validador::parseEntero` lanza `std::invalid_argument` | Mensaje "Debe ingresar un número válido." y se vuelve a pedir |
| Opción de menú fuera de rango | Opción distinta de 0–4 | `Validador::leerEnteroEnRango` | Mensaje con el rango permitido y se vuelve a pedir |
| Campo de texto vacío | El usuario solo presiona Enter | `Validador::leerTexto` | Mensaje y se vuelve a pedir |
| Campo con comas | Rompería el formato CSV | `Validador::leerTexto` | Mensaje y se vuelve a pedir |
| Número demasiado grande | Desborda `int` | `std::out_of_range` convertido a `invalid_argument` | Igual que entrada no numérica |
| Cierre de entrada (Ctrl+D / Ctrl+Z) | EOF en `stdin` | `std::ios_base::failure` | El programa finaliza de forma ordenada (evita bucle infinito) |

## 2. Errores de reglas de negocio (excepciones personalizadas)

| Excepción | Código | Causa | Manejo |
|---|---|---|---|
| `EdadInvalidaException` | 1001 | Edad < 0 o > 120 al registrar | `Menu` muestra "Edad fuera de rango", no se registra, queda en el log |
| `AlumnoDuplicadoException` | 2002 | Código ya registrado | Se rechaza el registro y se informa |
| `AlumnoNoEncontradoException` | 2001 | Buscar o eliminar un código inexistente | Mensaje y retorno al menú |

## 3. Errores de archivo

| Excepción | Código | Causa | Manejo |
|---|---|---|---|
| `ArchivoNoEncontradoException` | 3001 | `alumnos.csv` no existe o no se puede abrir | `main` avisa, inicia con lista vacía y crea el archivo al guardar |
| `ArchivoCorruptoException` | 3002 | Cabecera inválida, columnas ≠ 4, campos vacíos, edad no numérica o fuera de rango, código repetido, archivo vacío | `main` indica la **línea** del error y ofrece continuar con lista vacía (se crea `.bak` del original) o cancelar |
| `std::runtime_error` al guardar | – | Sin permisos, disco lleno, ruta inválida | `Menu` avisa que los cambios no se guardaron y registra en el log |

## 4. Errores inesperados

Cualquier otra `std::exception` se captura en `Menu` (se informa y se vuelve al menú)
y en `main` (error fatal, código de salida 1). Todo queda en `logs/errores.log`.

## 5. Registro (log)

`Logger` escribe en `logs/errores.log` con fecha y nivel:

- `INFO`: inicio y fin del sistema.
- `AVISO`: errores de usuario o de datos recuperables (edad inválida, duplicado, no encontrado, archivo no encontrado).
- `ERROR`: errores críticos (archivo corrupto, fallo al guardar, error inesperado).

Si el log no se puede escribir, el error se ignora para no tumbar el programa.

## 6. Buenas prácticas aplicadas

- Se capturan excepciones **específicas** antes de la genérica.
- Mensajes claros, con la causa y el dato problemático.
- Las excepciones no se usan para el flujo normal (validar una edad es la excepción, no el camino habitual).
- Jerarquía propia con código de error, capturable como `SistemaException`.
- Un archivo corrupto nunca se sobrescribe sin respaldo previo.
