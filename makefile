# Makefile para el sistema de generación y análisis de datos de personas
# ------------------------------------------------------------
# Autor: Tu Nombre
# Versión: 1.0
# Fecha: $(date)
# ------------------------------------------------------------

# Configuración del compilador y flags
# ------------------------------------
# POR QUÉ: Especificar las opciones de compilación centralizadas
# CÓMO: Definir variables para compilador y flags
# PARA QUÉ: Facilita modificaciones y asegura consistencia
CXX = g++                         # Compilador C++ (GNU)
CXXFLAGS = -Wall -Wextra -pedantic -std=c++14 -O2  # Flags de compilación:
                                # -Wall: Todas las advertencias
                                # -Wextra: Advertencias adicionales
                                # -pedantic: Cumplimiento estricto del estándar
                                # -std=c++14: Usar estándar C++14
                                # -O2: Optimización de velocidad

# Configuración de archivos fuente
# --------------------------------
# POR QUÉ: Identificar todos los componentes del proyecto
# CÓMO: Listar archivos fuente y calcular objetos correspondientes
# PARA QUÉ: Automatizar el proceso de compilación
SRC = main.cpp persona.cpp generador.cpp monitor.cpp  # Fuentes principales
OBJ = $(SRC:.cpp=.o)            # Generar nombres de objetos (.o) a partir de fuentes
EXEC = programa                 # Nombre del ejecutable final

# Targets especiales (phony targets)
# ----------------------------------
# POR QUÉ: Indicar que estos targets no producen archivos con su nombre
# CÓMO: Declarándolos como .PHONY
# PARA QUÉ: Evitar conflictos con archivos reales llamados all, clean, etc.
.PHONY: all clean run

# Target principal
# ----------------
# POR QUÉ: Construir el ejecutable completo por defecto
# CÓMO: Dependiendo de los objetos (.o)
# PARA QUÉ: Compilar el programa con una sola orden (make)
all: $(EXEC)

# Regla de enlace
# ---------------
# POR QUÉ: Combinar todos los objetos en un ejecutable
# CÓMO: Invocando al compilador para la fase de enlace
# PARA QUÉ: Crear el programa ejecutable final
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^  # $@ = nombre del target (programa)
                                # $^ = todas las dependencias (archivos .o)

# Regla de compilación de objetos
# -------------------------------
# POR QUÉ: Compilar cada fuente individualmente
# CÓMO: Usando patrón para convertir .cpp a .o
# PARA QUÉ: Permitir compilación incremental (solo cambia lo modificado)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@  # $< = primer prerrequisito (archivo .cpp)
                                    # $@ = archivo objetivo (.o)

# Target para ejecutar el programa
# --------------------------------
# POR QUÉ: Automatizar compilación y ejecución en un solo paso
# CÓMO: Dependiendo del ejecutable, luego ejecutarlo
# PARA QUÉ: Flujo de trabajo eficiente durante desarrollo
run: $(EXEC)
	@echo "============================================="
	@echo "  Iniciando ejecución del programa..."
	@echo "============================================="
	@./$(EXEC)  # Ejecutar el programa después de compilar
	@echo "============================================="
	@echo "  Ejecución completada"
	@echo "============================================="

# Target para limpieza
# --------------------
# POR QUÉ: Eliminar archivos generados durante la compilación
# CÓMO: Eliminando objetos y ejecutable
# PARA QUÉ: Liberar espacio y asegurar compilación limpia
clean:
	rm -f $(OBJ) $(EXEC)  # Eliminar objetos y ejecutable
	@echo "Archivos de compilación eliminados"
