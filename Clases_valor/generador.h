#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"
#include <vector>

// Funciones para generación de datos aleatorios

/**
 * Genera una fecha de nacimiento aleatoria entre 1960 y 2010.
 * 
 * POR QUÉ: Simular fechas realistas para personas.
 * CÓMO: Combinando números aleatorios para día, mes y año.
 * PARA QUÉ: Inicializar el atributo fechaNacimiento de Persona.
 */
std::string generarFechaNacimiento();

/**
 * Genera un ID único secuencial.
 * 
 * POR QUÉ: Necesidad de identificadores únicos para cada persona.
 * CÓMO: Usando un contador estático que incrementa en cada llamada.
 * PARA QUÉ: Garantizar unicidad en los IDs.
 */
int generarID();

/**
 * Genera un número decimal aleatorio en un rango [min, max].
 * 
 * POR QUÉ: Necesidad de valores realistas para ingresos, patrimonio, etc.
 * CÓMO: Usando un generador Mersenne Twister y una distribución uniforme.
 * PARA QUÉ: Producir valores financieros aleatorios pero dentro de rangos lógicos.
 */
double randomDouble(double min, double max);

/**
 * Genera una Persona "vacía" con valores por defecto para representar "no encontrado".
 * 
 * POR QUÉ: Necesitamos un objeto Persona válido cuando no se encuentra una persona.
 * CÓMO: Creando una Persona con valores por defecto que se puedan identificar fácilmente.
 * PARA QUÉ: Evitar errores de compilación y mantener el enfoque por valor.
 */
Persona generarPersonaVacia();

/**
 * Crea una persona con datos aleatorios.
 * 
 * POR QUÉ: Automatizar la creación de registros de personas.
 * CÓMO: Combinando las funciones generadoras y bases de datos de nombres, apellidos, etc.
 * PARA QUÉ: Poblar el sistema con datos de prueba.
 */
Persona generarPersona();

/**
 * Genera una colección (vector) de n personas.
 * 
 * POR QUÉ: Crear conjuntos de datos de diferentes tamaños.
 * CÓMO: Llamando a generarPersona() n veces.
 * PARA QUÉ: Pruebas de rendimiento y funcionalidad con volúmenes variables.
 */
std::vector<Persona> generarColeccion(int n);

/**
 * Busca una persona por ID en un vector de personas.
 * 
 * POR QUÉ: Recuperar una persona específica de una colección.
 * CÓMO: Usando un algoritmo de búsqueda lineal (o binaria si se ordena).
 * PARA QUÉ: Implementar funcionalidad de búsqueda en la aplicación.
 * 
 * @param personas Vector de personas donde buscar.
 * @param id ID a buscar.
 * @return Objeto Persona con el ID buscado, o un objeto Persona vacío si no se encuentra.
 */
Persona buscarPorID(std::vector<Persona> personas, std::string id);

/**
 * Busca la persona con mayor patrimonio en todo el país.
 */
Persona buscarMayorPatrimonio(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor patrimonio en cada ciudad.
 */
void buscarMayoresPatrimonioPorCiudad(std::vector<Persona> personas);


/**
 * Imprime un listado con la persona de mayor patrimonio por grupo de declaración.
 */
void buscarMayoresPatrimonioPorGrupo(std::vector<Persona> personas);

/**
 * Busca la persona con mayor deuda en todo el país.
 */
Persona buscarMayorDeuda(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor deuda en cada ciudad.
 */
void buscarMayoresDeudasPorCiudad(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor deuda por grupo de declaración.
 */
void buscarMayoresDeudasPorGrupo(std::vector<Persona> personas);

void listarPersonasGrupo(std::vector<Persona> personas, char grupoDeclaracion, int contador);

/**
 * Obtiene un listado con la persona más longeva de todo el país.
 */
Persona buscarPersonaMasLongevaConCondicion(std::vector<Persona> personas);   //toma del vector personas por valor

/**
 * Obtiene la persona mas longeva de cada ciudad
 */
void mostrarPersonasMasLongevaPorCiudad_Vector(std::vector<Persona> personas);


//Definición de la función que calcula el grupo con más personas de cada ciudad
void calcularGrupoMayorPorCiudad(std::vector<Persona> personas);

//Definición de la función que calcula los promedios de patrimonio por ciudad, y muestra los primeros 3
void calcularPromedioPatrimonio(std::vector<Persona> personas);

#endif // GENERADOR_H



