# Reparto de tareas (asignación aleatoria)

| Integrante | Rol | Responsabilidad principal | Rama |
|---|---|---|---|
| **Gerson** | Líder técnico / Integración | Repo, `CMakeLists.txt`, `Makefile`, `.gitignore`, `sistema_alumnos/src/main.cpp`, revisión de PRs, tag `v1.0` | `chore/setup-gerson` |
| **Jaime** | Práctica 5 | Todo `practica5/` y `tests/test_practica5.cpp` | `feat/practica5-jaime` |
| **Wilber** | Jerarquía de excepciones | `sistema_alumnos/include/excepciones/` | `feat/excepciones-wilber` |
| **Diego** | Persistencia y archivos | `RepositorioAlumnos`, `data/*.csv`, `tests/test_repositorio.cpp` | `feat/repositorio-diego` |
| **Jhon** | Lógica del sistema | `Alumno`, `GestorAlumnos`, `tests/test_gestor.cpp` | `feat/gestor-jhon` |
| **Cristhian** | Entrada, UI y documentación | `Validador`, `Menu`, `Logger`, `tests/test_validador.cpp`, `docs/`, `README.md` | `feat/ui-cristhian` |

## Reglas para que todos tengan commits

1. Mínimo **5 commits** por integrante en su rama, pequeños y descriptivos.
2. Cada tarea entra por **Pull Request** revisado por otro integrante.
3. Cada integrante revisa **al menos 1 PR** de un compañero.
4. Cada quien commitea con su propio usuario de Git, verificado en GitHub.
5. Mensajes: `feat:`, `fix:`, `docs:`, `test:`, `chore:`.
   Ejemplo: `feat(practica5): lanzar EdadInvalidaException fuera de 0-120`.

## Revisores (rotativo)

| Autor | Revisor |
|---|---|
| Jaime | Wilber |
| Wilber | Jhon |
| Jhon | Diego |
| Diego | Cristhian |
| Cristhian | Gerson |
| Gerson | Jaime |

## Cronograma

| Fase | Contenido | Responsables |
|---|---|---|
| 1. Setup | Repo, estructura, build, `.gitignore` | Gerson |
| 2. Base | Excepciones + Práctica 5 | Wilber, Jaime |
| 3. Núcleo | Repositorio, Gestor, Validador | Diego, Jhon, Cristhian |
| 4. Integración | Menú, `main.cpp`, logger | Cristhian, Gerson |
| 5. Pruebas y docs | Tests, catálogo de errores, README | Todos |
| 6. Cierre | Revisión final y tag `v1.0` | Gerson |

## Sugerencia de commits por persona (para repartir el historial)

- **Gerson:** `chore: estructura inicial de carpetas`, `chore: agregar .gitignore`, `build: CMakeLists`, `build: Makefile`, `feat(sistema): main.cpp con carga y respaldo de archivo corrupto`, `chore: release v1.0`.
- **Jaime:** `feat(practica5): EdadInvalidaException`, `feat(practica5): validarEdad`, `feat(practica5): main con try/catch`, `test(practica5): pruebas de límites`, `docs(practica5): README`.
- **Wilber:** `feat: SistemaException base`, `feat: EdadInvalidaException`, `feat: AlumnoNoEncontradoException`, `feat: AlumnoDuplicadoException`, `feat: excepciones de archivo`.
- **Diego:** `feat: RepositorioAlumnos.cargar`, `feat: ArchivoNoEncontrado`, `feat: detección de filas corruptas`, `feat: RepositorioAlumnos.guardar`, `test: test_repositorio`, `chore: datos de ejemplo`.
- **Jhon:** `feat: clase Alumno`, `feat: GestorAlumnos.registrar`, `feat: buscar/eliminar`, `feat: validación de duplicados`, `test: test_gestor`.
- **Cristhian:** `feat: Validador`, `feat: Logger`, `feat: Menu`, `test: test_validador`, `docs: catálogo de errores`, `docs: casos de prueba y README`.
