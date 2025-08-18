#include "generador.h"
#include "monitor.h"
#include "persona.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <limits>
#include <memory>

/**
 * Muestra el menú principal de la aplicación.
 *
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
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

/**
 * Punto de entrada principal del programa.
 *
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    std::vector<Persona> personas;

    Monitor monitor; // Monitor para medir rendimiento
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales para uso en los casos
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        int filtradoPersonaLongeva;
        int filtradoPersonaPatrimonio;
        int listadoGrupos;
        std::string ciudadPersona;
        char calendario;
        int contador = 0;
        int filtradoPersonaDeuda;
        
        long memoria_inicio = monitor.obtener_memoria(); ;
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                 // Iniciar medición de tiempo y memoria para la operación actual
                monitor.iniciar_tiempo();
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de personas
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                
                // Mover el conjunto 
                personas = std::move(nuevasPersonas);
                
                // Medir tiempo y memoria usada
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                // Registrar la operación
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: { // Mostrar resumen de todas las personas
                monitor.iniciar_tiempo();
                if (personas.empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas.size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    personas[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                break;
            }
                
            case 2: { // Mostrar detalle por índice
                monitor.iniciar_tiempo();
                if (personas.empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                tam = personas.size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        personas[indice].mostrar();
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
                if (personas.empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;

                Persona encontrada = buscarPorID(personas, idBusqueda);
                if (encontrada.id == idBusqueda) {
                    encontrada.mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 4: // Mostrar estadísticas de rendimiento
                monitor.mostrar_resumen();
                break;
                
            case 5: // Persona más longeva
                if (personas.empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\n1. Persona mas longeva  por país";
                std::cout << "\n2. Persona mas longeva por cada ciudad";
                std::cout << "\nSeleccione una opción: ";
                std::cin >> filtradoPersonaLongeva;

                switch (filtradoPersonaLongeva) {
                    case 1: { // Persona mas longeva por país
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        Persona p = buscarPersonaMasLongevaConCondicion(personas);
                        if (p.id != "") {
                            std::cout << "\n=== Persona más longeva en Colombia ===\n";
                            p.mostrar();
                        }

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Persona más longeva en Colombia", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Persona más longeva en Colombia", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 2: { // Persona mas longeva por ciudad
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        mostrarPersonasMasLongevaPorCiudad_Vector(personas);

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

            case 6: // Persona con Mayor patrimonio
                if (personas.empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                std::cout << "\n1. Mayor patrimonio en todo el país";
                std::cout << "\n2. Mayor patrimonio por ciudad";
                std::cout << "\n3. Mayor patrimonio por grupo de declaración";
                std::cout << "\nSeleccione una opción: ";
                std::cin >> filtradoPersonaPatrimonio;

                switch (filtradoPersonaPatrimonio) {
                    case 1: { // Mayor patrimonio en Colombia
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        Persona p = buscarMayorPatrimonio(personas);
                        if (p.id != "") {
                            std::cout << "\n=== Persona con mayor patrimonio en Colombia ===\n";
                            p.mostrar();
                        }

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor patrimonio en Colombia", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor patrimonio en Colombia", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 2: { // Mayor patrimonio por ciudad
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        buscarMayoresPatrimonioPorCiudad(personas);

                        double tiempo_busqueda = monitor.detener_tiempo();
                        long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        monitor.mostrar_estadistica("Mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                        monitor.registrar("Mayor patrimonio por ciudad", tiempo_busqueda, memoria_busqueda);
                        break;
                    }

                    case 3: { // Mayor patrimonio por grupo de declaración
                        monitor.iniciar_tiempo();
                        memoria_inicio = monitor.obtener_memoria();

                        buscarMayoresPatrimonioPorGrupo(personas);

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
            
            case 7: // Listar y contar personas por calendario
                std::cout << "\n1. Listar y contar por calendario especifico (Grupo A,B o C) ";
                std::cout << "\n2. Listar y contar en todos los calendarios (Grupo A,B y C) ";
                std::cout << "\n3. Validar Grupo al que pertenece";
                std::cin >> listadoGrupos;
                switch(listadoGrupos) {
                    case 1:
                    monitor.iniciar_tiempo();
                        std::cout << "\nIngresar calendario (A-B-C)";
                        std::cin >> calendario;
                        listarPersonasGrupo(personas,calendario,contador);
                        std::cout << "\nA grupo "<< calendario <<"pertenecen"<< contador << "personas"; 
                        break;

                    case 2:
                        // monitor.iniciar_tiempo();
                        listarPersonasGrupo(personas,'A',contador);
                        std::cout << "\nA grupo A pertenecen"<< contador << "personas"; 
                        contador = 0;
                        listarPersonasGrupo(personas,'B',contador);
                        std::cout << "\nA grupo B pertenecen"<< contador << "personas"; 
                        contador = 0;
                         listarPersonasGrupo(personas,'C',contador);
                        std::cout << "\nA grupo C pertenecen"<< contador << "personas"; 

                        // double tiempo_detalle = monitor.detener_tiempo();
                        // long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                        // monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
                        break;
                    case 3: 
                        // monitor.iniciar_tiempo();
                        std::cout << "\nIngrese el ID a buscar: ";
                        std::cin >> idBusqueda;
                        Persona encontrada = buscarPorID(personas, idBusqueda);
                        if (encontrada.id != "") {
                            encontrada.mostrar();
                        } else {
                            std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                        }
                        
                        // double tiempo_busqueda = monitor.detener_tiempo();
                        // long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                        // monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                        break;

                }
                break;

    case 8: // Grupo con más personas de una ciudad
    {
      monitor.iniciar_tiempo();
      memoria_inicio = monitor.obtener_memoria();
      calcularGrupoMayorPorCiudad(personas);
      break;
    }
    case 9: { // 3 ciudades con patrimonio promedio más alto
      monitor.iniciar_tiempo();
      memoria_inicio = monitor.obtener_memoria();
      calcularPromedioPatrimonio(personas);
      break;
    }
    case 10: // Persona con mayor deuda
        if (personas.empty()) {
            std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
            break;
        }

        std::cout << "\n1. Mayor deuda en todo el país";
        std::cout << "\n2. Mayor deuda por ciudad";
        std::cout << "\n3. Mayor deuda por grupo de declaración";
        std::cout << "\nSeleccione una opción: ";
        std::cin >> filtradoPersonaDeuda;

        switch (filtradoPersonaDeuda) {
            case 1: { // Mayor deuda en Colombia
                monitor.iniciar_tiempo();
                memoria_inicio = monitor.obtener_memoria();

                Persona p = buscarMayorDeuda(personas);
                if (p.id != "") {
                    std::cout << "\n=== Persona con mayor deuda en Colombia ===\n";
                    p.mostrar();
                }

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.mostrar_estadistica("Mayor deuda en Colombia", tiempo_busqueda, memoria_busqueda);
                monitor.registrar("Mayor deuda en Colombia", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 2: { // Mayor deuda por ciudad
                monitor.iniciar_tiempo();
                memoria_inicio = monitor.obtener_memoria();

                buscarMayoresDeudasPorCiudad(personas);

                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.mostrar_estadistica("Mayor deuda por ciudad", tiempo_busqueda, memoria_busqueda);
                monitor.registrar("Mayor deuda por ciudad", tiempo_busqueda, memoria_busqueda);
                break;
            }

            case 3: { // Mayor deuda por grupo de declaración
                monitor.iniciar_tiempo();
                memoria_inicio = monitor.obtener_memoria();

                buscarMayoresDeudasPorGrupo(personas);


                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.mostrar_estadistica("Mayor deuda por grupo", tiempo_busqueda, memoria_busqueda);
                monitor.registrar("Mayor deuda por grupo", tiempo_busqueda, memoria_busqueda);
                break;
            }

            default:
                std::cout << "Opción inválida!\n";
        }
        break;

    case 11: // Salida
      std::cout << "Saliendo...\n";
      break;

    default:
      std::cout << "Opción inválida!\n";
    }

    // Mostrar estadísticas de la operación (excepto para opciones 4,5,6)
    if ((opcion >= 0 && opcion <= 3) || (opcion >= 8 && opcion <= 10)) {
      double tiempo = monitor.detener_tiempo();
      long memoria = monitor.obtener_memoria() - memoria_inicio;
      monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo,
                                  memoria);
    }

  } while (opcion != 11);

  return 0;
}
