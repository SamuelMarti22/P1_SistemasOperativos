# Makefile para compilación automatizada en Linux

# Configuración del compilador
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++14  # Usando C++14 para std::make_unique

# Archivos fuente y objetos
SRCS := generador.cpp main.cpp monitor.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := programa

# Objetivo principal: compilar el ejecutable
all: $(EXEC)

# Enlaza todos los objetos en el ejecutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas específicas para cada objeto con sus dependencias
generador.o: generador.cpp generador.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

monitor.o: monitor.cpp monitor.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp persona.h generador.h monitor.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpia archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

# Recompila todo desde cero
rebuild: clean all

# Ejecuta el programa después de compilar
run: $(EXEC)
	./$(EXEC)

# Declara objetivos que no son archivos
.PHONY: all clean rebuild run