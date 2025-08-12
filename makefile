# Archivos fuente y objetos
SRCS := generador.cpp main.cpp # Persona.h es header-only ahora
OBJS := $(SRCS:.cpp=.o)
EXEC := programa # Nombre del ejecutable final

# Objetivo principal: compilar el ejecutable
all: $(EXEC)

# Enlaza todos los objetos en el ejecutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas específicas para cada objeto con sus dependencias

# generador.o depende de generador.cpp y sus headers
generador.o: generador.cpp generador.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# main.o depende de main.cpp y sus headers
main.o: main.cpp persona.h generador.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpia archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

# Ejecuta el programa después de compilar
run: $(EXEC)
	./$(EXEC)
