#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Clase para medir tiempo y memoria en Linux
class Monitor {
public:
    // Inicia la medición de tiempo
    void iniciar_tiempo() {
        inicio = std::chrono::high_resolution_clock::now();
    }
    
    // Detiene la medición de tiempo y devuelve milisegundos
    double detener_tiempo() {
        auto fin = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    }
    
    // Obtiene el consumo de memoria actual en KB usando /proc/self/statm
    long obtener_memoria() {
        // Abrir el archivo de estadísticas de memoria
        FILE* file = fopen("/proc/self/statm", "r");
        if (!file) {
            perror("Error al abrir /proc/self/statm");
            return 0;
        }
        
        long size, resident, shared, text, lib, data, dt;
        if (fscanf(file, "%ld %ld %ld %ld %ld %ld %ld", 
                  &size, &resident, &shared, &text, &lib, &data, &dt) != 7) {
            fclose(file);
            return 0;
        }
        
        fclose(file);
        
        // Obtener el tamaño de página del sistema
        long page_size = sysconf(_SC_PAGESIZE) / (1024*1024); // Convertir a KB
        
        // Memoria residente en KB (páginas * tamaño de página en KB)
        return resident * page_size;
    }
    
    // Registra estadísticas para una operación
    void registrar(const std::string& operacion, double tiempo, long memoria) {
        registros.push_back({operacion, tiempo, memoria});
        total_tiempo += tiempo;
        max_memoria = std::max(max_memoria, memoria);
    }
    
    // Muestra estadísticas de una operación
    void mostrar_estadistica(const std::string& operacion, double tiempo, long memoria) {
        std::cout << "\n[ESTADÍSTICAS] " << operacion << " - "
                  << "Tiempo: " << tiempo << " ms, "
                  << "Memoria: " << memoria << " KB\n";
    }
    
    // Muestra todas las estadísticas registradas
    void mostrar_resumen() {
        std::cout << "\n=== RESUMEN DE ESTADÍSTICAS ===";
        for (const auto& reg : registros) {
            std::cout << "\n" << reg.operacion << ": "
                      << reg.tiempo << " ms, " << reg.memoria << " KB";
        }
        std::cout << "\nTotal tiempo: " << total_tiempo << " ms";
        std::cout << "\nMemoria máxima: " << max_memoria << " KB\n";
    }
    
    // Exporta las estadísticas a un archivo CSV
    void exportar_csv(const std::string& nombre_archivo = "estadisticas.csv") {
        std::ofstream archivo(nombre_archivo);
        archivo << "Operacion,Tiempo(ms),Memoria(KB)\n";
        for (const auto& reg : registros) {
            archivo << reg.operacion << "," << reg.tiempo << "," << reg.memoria << "\n";
        }
        archivo.close();
        std::cout << "Estadísticas exportadas a " << nombre_archivo << "\n";
    }

private:
    struct Registro {
        std::string operacion;
        double tiempo;
        long memoria;
    };
    
    std::chrono::high_resolution_clock::time_point inicio;
    std::vector<Registro> registros;
    double total_tiempo = 0;
    long max_memoria = 0;
};

#endif // MONITOR_H