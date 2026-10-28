cmake_minimum_required(VERSION 3.10)
project(practica_manejo_errores VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4 /utf-8)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

# ---------------------------------------------------------------------------
# Práctica 5
# ---------------------------------------------------------------------------
add_library(practica5_core STATIC practica5/src/validador_edad.cpp)
target_include_directories(practica5_core PUBLIC practica5/include)

add_executable(practica5 practica5/src/main.cpp)
target_link_libraries(practica5 PRIVATE practica5_core)

# ---------------------------------------------------------------------------
# Sistema de registro de alumnos
# ---------------------------------------------------------------------------
add_library(sistema_core STATIC
  sistema_alumnos/src/Alumno.cpp
  sistema_alumnos/src/GestorAlumnos.cpp
  sistema_alumnos/src/Logger.cpp
  sistema_alumnos/src/Menu.cpp
  sistema_alumnos/src/RepositorioAlumnos.cpp
  sistema_alumnos/src/Validador.cpp
)
target_include_directories(sistema_core PUBLIC sistema_alumnos/include)

add_executable(sistema_alumnos sistema_alumnos/src/main.cpp)
target_link_libraries(sistema_alumnos PRIVATE sistema_core)
target_compile_definitions(sistema_alumnos PRIVATE
  RUTA_DATOS_DEFECTO="${CMAKE_CURRENT_SOURCE_DIR}/sistema_alumnos/data/alumnos.csv"
  RUTA_LOGS_DEFECTO="${CMAKE_CURRENT_SOURCE_DIR}/sistema_alumnos/logs/errores.log"
)

# ---------------------------------------------------------------------------
# Pruebas (ctest)
# ---------------------------------------------------------------------------
enable_testing()

add_executable(test_practica5 tests/test_practica5.cpp)
target_link_libraries(test_practica5 PRIVATE practica5_core)
target_include_directories(test_practica5 PRIVATE tests)
add_test(NAME practica5 COMMAND test_practica5)

foreach(nombre IN ITEMS validador repositorio gestor)
  add_executable(test_${nombre} tests/test_${nombre}.cpp)
  target_link_libraries(test_${nombre} PRIVATE sistema_core)
  target_include_directories(test_${nombre} PRIVATE tests)
  add_test(NAME ${nombre}
           COMMAND test_${nombre}
           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
