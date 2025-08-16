#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * Clase para monitorear el rendimiento (tiempo y memoria).
 * 
 * POR QUÉ: Cuantificar el rendimiento de las operaciones.
 * CÓMO: Midiendo tiempo con chrono y memoria con /proc/self/statm (Linux).
 * PARA QUÉ: Optimización y análisis de rendimiento.
 */
class Monitor {
public:
    void iniciar_tiempo();
    double detener_tiempo();
    long obtener_memoria();
    
    void registrar(const std::string& operacion, double tiempo, long memoria);
    void mostrar_estadistica(const std::string& operacion, double tiempo, long memoria);
    void mostrar_resumen();
    void exportar_csv(const std::string& nombre_archivo = "estadisticas.csv");

private:
    // Estructura para almacenar métricas de una operación
    struct Registro {
        std::string operacion; // Nombre de la operación
        double tiempo;         // Tiempo en milisegundos
        long memoria;          // Memoria en KB
    };
    
    std::chrono::high_resolution_clock::time_point inicio; // Punto de inicio del cronómetro
    std::vector<Registro> registros; // Historial de registros
    double total_tiempo = 0;         // Tiempo total acumulado
    long max_memoria = 0;            // Máximo de memoria utilizado
};

#endif // MONITOR_H