#include "generador.h"
#include "monitor.h"
#include "persona.h"
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>

/**
 * Muestra el menú principal de la aplicación.
 */
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Mostrar estadísticas de rendimiento";
    std::cout << "\n5. Persona más longeva";
    std::cout << "\n6. Persona con mayor patrimonio";
    std::cout << "\n7. Listar y contar Grupos";
    std::cout << "\n8. Grupo con más personas de una ciudad";
    std::cout << "\n9. 3 ciudades con mayor promedio de patrimonio";
    std::cout << "\n10. Persona con mayor deuda";
    std::cout << "\n11. Salir";
    std::cout << "\nSeleccione una opción: ";
}

int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    Monitor monitor; 
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        int filtradoPersonaLongeva;
        int filtradoPersonaPatrimonio;
        int filtradoPersonaDeuda;
        int listadoGrupos;
        std::string ciudadPersona;
        char calendario;
        int contador = 0;
        
        long memoria_inicio = monitor.obtener_memoria(); 
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                monitor.iniciar_tiempo();
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));
                
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: { // Mostrar resumen
                monitor.iniciar_tiempo();
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            case 2: { // Detalle por índice
                monitor.iniciar_tiempo();
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        (*personas)[indice].mostrar();
                    } else {
                        std::cout << "Índice fuera de rango!\n";
                    }
                } else {
                    std::cout << "Entrada inválida!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                double tiempo_detalle = monitor.detener_tiempo();
                long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
                break;
            }
                
            case 3: { // Buscar por ID
                monitor.iniciar_tiempo();
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;
                std::string* idBusqueda= idBusqueda; // (línea original, no modificada)
                
                if(const Persona* encontrada = buscarPorID(personas.get(), idBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 4: // Estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 5: { // Persona más longeva
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\n1. Persona mas longeva  por país";
                std::cout << "\n2. Persona mas longeva por cada ciudad";
                std::cout << "\nSeleccione una opción: ";
                std::cin >> filtradoPersonaLongeva;

                switch (filtradoPersonaLongeva) {
                    case 1: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        if (const Persona* p = buscarPersonaMasLongevaConCondicion(personas.get())) {
                            std::cout << "\n=== Persona más longeva en Colombia ===\n";
                            p->mostrar();
                        }

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Persona más longeva en Colombia", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Persona más longeva en Colombia", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 2: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        mostrarPersonasMasLongevaPorCiudad_Vector(personas.get());

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Persona más longeva por ciudad", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Persona más longeva por ciudad", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    default:
                        std::cout << "Opción no válida.\n";
                        break;
                }
                break;
            }

            case 6: { // Mayor patrimonio
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\n1. Mayor patrimonio en todo el país";
                std::cout << "\n2. Mayor patrimonio por ciudad";
                std::cout << "\n3. Mayor patrimonio por grupo de declaración";
                std::cout << "\nSeleccione una opción: ";
                std::cin >> filtradoPersonaPatrimonio;

                switch (filtradoPersonaPatrimonio) {
                    case 1: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        if (const Persona* p = buscarMayorPatrimonio(personas.get())) {
                            std::cout << "\n=== Persona con mayor patrimonio en Colombia ===\n";
                            p->mostrar();
                        }

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor patrimonio en Colombia", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor patrimonio en Colombia", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 2: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        buscarMayoresPatrimonioPorCiudad(personas.get());

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 3: { 

                        buscarMayoresPatrimonioPorGrupo(personas.get());

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor patrimonio por grupo", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor patrimonio por grupo", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    default:
                        std::cout << "Opción inválida!\n";
                }
                break;
            }
            
            case 7: { // Listar y contar personas por calendario
                std::cout << "\n1. Listar y contar por calendario especifico (Grupo A,B o C) ";
                std::cout << "\n2. Listar y contar en todos los calendarios (Grupo A,B y C) ";
                std::cout << "\n3. Validar Grupo al que pertenece";
                std::cout << "\n   Ingresar opcion:";
                std::cin >> listadoGrupos;

                switch(listadoGrupos) {
                    case 1: {
                        monitor.iniciar_tiempo();
                        std::cout << "\nIngresar calendario (A-B-C): ";
                        std::cin >> calendario;
                        listarPersonasGrupo(personas.get(), calendario, &contador);
                        std::cout << "\nA grupo " << calendario << " pertenecen " << contador << " personas"; 
                        break;
                    }
                    case 2: {
                        // monitor.iniciar_tiempo();
                        listarPersonasGrupo(personas.get(),'A', &contador);
                        std::cout << "\nA grupo A pertenecen" << contador << " personas"; 
                        contador = 0;
                        listarPersonasGrupo(personas.get(),'B', &contador);
                        std::cout << "\nA grupo B pertenecen" << contador << " personas"; 
                        contador = 0;
                        listarPersonasGrupo(personas.get(),'C', &contador);
                        std::cout << "\nA grupo C pertenecen" << contador << " personas"; 
                        // monitor...
                        break;
                    }
                    case 3: {
                        // monitor.iniciar_tiempo();
                        std::cout << "\nIngrese el ID a buscar: ";
                        std::cin >> idBusqueda;
                        std::string* idBusqueda= idBusqueda; // (línea original, no modificada)
                        if(const Persona* encontrada = buscarPorID(personas.get(), idBusqueda)) {
                            encontrada->mostrar();
                        } else {
                            std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                        }
                        // monitor...
                        break;
                    }
                    default:
                        break;
                }
                break; // ← cierra el case 7 del switch principal
            }

            case 8: { // Grupo con más personas de una ciudad
                monitor.iniciar_tiempo();
                memoria_inicio = monitor.obtener_memoria();
                calcularGrupoMayorPorCiudad(personas.get());
                break;
            }

            case 9: { // 3 ciudades con patrimonio promedio más alto
                monitor.iniciar_tiempo();
                memoria_inicio = monitor.obtener_memoria();
                calcularPromedioPatrimonio(personas.get());
                break;
            }

            case 10: { // Persona con mayor deuda
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\n1. Mayor deuda en todo el país";
                std::cout << "\n2. Mayor deuda por ciudad";
                std::cout << "\n3. Mayor deuda por grupo de declaración";
                std::cout << "\nSeleccione una opción: ";
                std::cin >> filtradoPersonaDeuda;

                switch (filtradoPersonaDeuda) {
                    case 1: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        if (const Persona* p = buscarMayorDeuda(personas.get())) {
                            std::cout << "\n=== Persona con mayor deuda en Colombia ===\n";
                            p->mostrar();
                        }

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor deuda en Colombia", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor deuda en Colombia", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 2: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();
                        buscarMayoresDeudasPorCiudad(personas.get());

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor deuda por ciudad", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor deuda por ciudad", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 3: { 
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        buscarMayoresDeudasPorGrupo(personas.get());

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor deuda por grupo", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor deuda por grupo", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    default:
                        std::cout << "Opción inválida!\n";
                        break;
                }
                break; // ← cierra el case 10 del switch principal
            }

            case 11: { // Salida
                std::cout << "Saliendo...\n";
                break;
            }

            default:
                std::cout << "Opción inválida!\n";
                break;
        }
    
        // Mostrar estadísticas para algunas opciones
        if ((opcion >= 0 && opcion <= 3) || (opcion >= 8 && opcion <= 9)) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
    } while (opcion != 11);
   
    return 0;
}
