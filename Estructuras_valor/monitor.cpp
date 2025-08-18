#include "monitor.h"
#include <unistd.h> // sysconf
#include <cstdio>   // FILE, fscanf

/**
 * Inicia el cronómetro.
 * 
 * POR QUÉ: Comenzar a medir el tiempo de una operación.
 * CÓMO: Guardando el tiempo actual en 'inicio'.
 * PARA QUÉ: Poder calcular la duración después.
 */
void Monitor::iniciar_tiempo() {
    inicio = std::chrono::high_resolution_clock::now();
}

/**
 * Detiene el cronómetro y devuelve el tiempo transcurrido.
 * 
 * POR QUÉ: Obtener la duración de una operación.
 * CÓMO: Calculando la diferencia entre el tiempo actual y 'inicio'.
 * PARA QUÉ: Conocer el tiempo que tomó una operación.
 * @return Tiempo en milisegundos con decimales.
 */
double Monitor::detener_tiempo() {
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    return duracion.count();
}

/**
 * Obtiene la memoria residente actual (RSS) del proceso en KB.
 * 
 * POR QUÉ: Medir el consumo de memoria física.
 * CÓMO: Leyendo el archivo /proc/self/statm (específico de Linux).
 * PARA QUÉ: Monitorear el uso de memoria en operaciones críticas.
 * @return Memoria residente en KB, o 0 en caso de error.
 */
long Monitor::obtener_memoria() {
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
    
    // Calcular memoria en KB: resident (páginas) * tamaño_página (KB)
    long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;
    return resident * page_size_kb;
}

/**
 * Registra una operación con sus métricas de tiempo y memoria.
 * 
 * POR QUÉ: Almacenar estadísticas para análisis posterior.
 * CÓMO: Guardando un nuevo Registro en el vector y actualizando acumulados.
 * PARA QUÉ: Tener un histórico de rendimiento.
 */
void Monitor::registrar(const std::string& operacion, double tiempo, long memoria) {
    registros.push_back({operacion, tiempo, memoria});
    total_tiempo += tiempo;
    if (memoria > max_memoria) {
        max_memoria = memoria;
    }
}

/**
 * Muestra las estadísticas de una operación.
 * 
 * POR QUÉ: Feedback inmediato al usuario.
 * CÓMO: Imprimiendo en consola.
 * PARA QUÉ: Visualizar el rendimiento de una operación concreta.
 */
void Monitor::mostrar_estadistica(const std::string& operacion, double tiempo, long memoria) {
    std::cout << "\n[ESTADÍSTICAS] " << operacion << " - "
              << "Tiempo: " << tiempo << " ms, "
              << "Memoria: " << memoria << " KB\n";
}

/**
 * Muestra un resumen de todas las estadísticas registradas.
 * 
 * POR QUÉ: Proporcionar una visión global del rendimiento.
 * CÓMO: Iterando sobre todos los registros e imprimiéndolos.
 * PARA QUÉ: Análisis comparativo de diferentes operaciones.
 */
void Monitor::mostrar_resumen() {
    std::cout << "\n=== RESUMEN DE ESTADÍSTICAS ===";
    for (const auto& reg : registros) {
        std::cout << "\n" << reg.operacion << ": "
                  << reg.tiempo << " ms, " << reg.memoria << " KB";
    }
    std::cout << "\nTotal tiempo: " << total_tiempo << " ms";
    std::cout << "\nMemoria máxima: " << max_memoria << " KB\n";
}

/**
 * Exporta las estadísticas a un archivo CSV.
 * 
 * POR QUÉ: Permitir análisis con herramientas externas (Excel, Python, etc.).
 * CÓMO: Escribiendo en un archivo de texto con formato CSV.
 * PARA QUÉ: Generar reportes y gráficos.
 * @param nombre_archivo Nombre del archivo CSV (por defecto "estadisticas.csv")
 */
void Monitor::exportar_csv(const std::string& nombre_archivo) {
    std::ofstream archivo(nombre_archivo);
    if (!archivo) {
        std::cerr << "Error al abrir archivo: " << nombre_archivo << std::endl;
        return;
    }
    archivo << "Operacion,Tiempo(ms),Memoria(KB)\n";
    for (const auto& reg : registros) {
        archivo << reg.operacion << "," << reg.tiempo << "," << reg.memoria << "\n";
    }
    archivo.close();
    std::cout << "Estadísticas exportadas a " << nombre_archivo << "\n";
}