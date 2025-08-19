#ifndef MONITOR_H
#define MONITOR_H

#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>  // std::function

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

    // Memoria pico (delta en el mismo proceso)
    void iniciar_memoria_pico();
    long memoria_pico_delta_kb() const;

    // Medir memoria consumida por una función, aisladamente (proceso hijo)
    long medir_memoria_funcion_kb(const std::function<void()>& fn);
    
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
    long peak_before_kb_ = 0; // para delta de pico (mismo proceso)
};

#endif // MONITOR_H