# Alternativa simple a CMake (Linux/macOS/MinGW). Uso: make | make test | make clean
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2
BUILD    := build

P5_INC   := -Ipractica5/include
SIS_INC  := -Isistema_alumnos/include
TEST_INC := -Itests

P5_SRC   := practica5/src/validador_edad.cpp
SIS_SRC  := $(filter-out sistema_alumnos/src/main.cpp,$(wildcard sistema_alumnos/src/*.cpp))
HEADERS  := $(wildcard practica5/include/*.hpp sistema_alumnos/include/*.hpp \
                       sistema_alumnos/include/excepciones/*.hpp tests/*.hpp)

DEFS := -DRUTA_DATOS_DEFECTO='"$(CURDIR)/sistema_alumnos/data/alumnos.csv"' \
        -DRUTA_LOGS_DEFECTO='"$(CURDIR)/sistema_alumnos/logs/errores.log"'

TESTS := test_practica5 test_validador test_repositorio test_gestor

.PHONY: all practica5 sistema_alumnos test clean

all: practica5 sistema_alumnos

practica5: $(BUILD)/practica5
sistema_alumnos: $(BUILD)/sistema_alumnos

$(BUILD)/practica5: practica5/src/main.cpp $(P5_SRC) $(HEADERS)
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(P5_INC) -o $@ practica5/src/main.cpp $(P5_SRC)

$(BUILD)/sistema_alumnos: sistema_alumnos/src/main.cpp $(SIS_SRC) $(HEADERS)
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(SIS_INC) $(DEFS) -o $@ sistema_alumnos/src/main.cpp $(SIS_SRC)

$(BUILD)/test_practica5: tests/test_practica5.cpp $(P5_SRC) $(HEADERS)
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(P5_INC) $(TEST_INC) -o $@ tests/test_practica5.cpp $(P5_SRC)

$(BUILD)/test_%: tests/test_%.cpp $(SIS_SRC) $(HEADERS)
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) $(SIS_INC) $(TEST_INC) -o $@ tests/test_$*.cpp $(SIS_SRC)

test: $(addprefix $(BUILD)/,$(TESTS))
	@for t in $(TESTS); do ./$(BUILD)/$$t || exit 1; done; echo "Todas las pruebas pasaron."

clean:
	rm -rf $(BUILD)
