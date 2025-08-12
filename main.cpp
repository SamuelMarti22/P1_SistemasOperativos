#include <iostream>
#include <vector>
#include <limits> 
#include "persona.h"
#include "generador.h"

void menu() {
    std::cout << "\n\n=== PANEL DE SELECCIÓN ===";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por cédula";
    std::cout << "\n4. Salir";
    std::cout << "\nSeleccione una opción: "; 
}
