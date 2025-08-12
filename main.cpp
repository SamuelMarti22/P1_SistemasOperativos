#include <iostream>
#include <vector>
#include <limits> // Para manejo de límites de entrada
#include "persona.h"
#include "generador.h"

// Muestra menú de opciones al usuario
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ DE VISUALIZACIÓN ===";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Salir";
    std::cout << "\nSeleccione una opción: ";
}

int main() {
    // Inicializa semilla para números aleatorios
    srand(time(nullptr));
    int n;
    
    // Solicita tamaño de la colección
    std::cout << "Ingrese el número de personas a generar: ";
    std::cin >> n;
    
    // Validar entrada de tamaño (debe ser positivo)
    if (n <= 0) {
        std::cerr << "Error: Debe generar al menos 1 persona\n";
        return 1; // Retorna código de error
    }
    
    // Generar la colección de personas
    std::vector<Persona> personas = generarColeccion(n);
    // Almacenar tamaño en variable size_t para evitar problemas de signo
    const size_t tam = personas.size();  

    int opcion;
    // Bucle principal del menú
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        switch(opcion) {
            case 1: // Mostrar resumen de todas las personas
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                // Usar size_t para índice para evitar advertencias de comparación
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    personas[i].mostrarResumen(); // Método compacto
                    std::cout << "\n";
                }
                break;
                
            case 2: { // Mostrar detalles por índice numérico
                int indice;
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
                    // Verificar que el índice esté en rango válido
                    // Primero comprueba que no sea negativo, luego compara con tamaño
                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        personas[indice].mostrar(); // Método detallado
                    } else {
                        std::cout << "Índice fuera de rango!\n";
                    }
                } else {
                    // Limpiar estado de error en cin
                    std::cout << "Entrada inválida!\n";
                    std::cin.clear();
                    // Descarta entrada incorrecta
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
                
            case 3: { // Buscar por ID exacto
                std::string idBusqueda;
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;
                
                // Intenta encontrar la persona
                if(const Persona* encontrada = buscarPorID(personas, idBusqueda)) {
                    encontrada->mostrar(); // Muestra detalles si la encontró
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                break;
            }
                
            case 4: // Salir del programa
                std::cout << "Saliendo...\n";
                break;
                
            default: // Opción no válida
                std::cout << "Opción inválida!\n";
        }
    } while(opcion != 4); // Repite hasta seleccionar salir
    
    return 0;
}
