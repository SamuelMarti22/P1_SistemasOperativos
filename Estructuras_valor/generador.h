#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"
#include <vector>

// --- Funciones para generación de datos aleatorios ---

// Genera fecha aleatoria entre 1960-2010
std::string generarFechaNacimiento();

// Genera ID único secuencial
std::string generarID();

// Genera número decimal en rango [min, max]
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

// Genera colección de n personas
std::vector<Persona> generarColeccion(int n);

// Busca persona por ID en un vector
// Retorna una copia de la persona si la encuentra, o una persona vacía si no
Persona buscarPorID(const std::vector<Persona>& personas, const std::string& id);


/**
 * Busca la persona con mayor patrimonio en todo el país.
 * Retorna una copia de la persona encontrada (struct, por valor).
 */
Persona buscarMayorPatrimonio(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor patrimonio en cada ciudad.
 * Usa struct y acceso directo a atributos públicos.
 */
void buscarMayoresPatrimonioPorCiudad(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor patrimonio por grupo de declaración.
 * Usa struct y por valor.
 */
void buscarMayoresPatrimonioPorGrupo(std::vector<Persona> personas);

/**
 * Busca la persona con mayor deuda en todo el país.
 * Retorna una copia de la persona encontrada (struct, por valor).
 */
Persona buscarMayorDeuda(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor deuda en cada ciudad.
 * Usa struct y por valor.
 */
void buscarMayoresDeudasPorCiudad(std::vector<Persona> personas);

/**
 * Imprime un listado con la persona de mayor deuda por grupo de declaración.
 * Usa struct y por valor.
 */
void buscarMayoresDeudasPorGrupo(std::vector<Persona> personas);

void listarPersonasGrupo(std::vector<Persona> personas, char grupoDeclaracion, int contador);

/**
 * Obtiene un listado con la persona más longeva de todo el país.
 * Retorna una copia de la persona encontrada (struct, por valor).
 */
Persona buscarPersonaMasLongevaConCondicion(std::vector<Persona> personas);

/**
 * Obtiene la persona más longeva de cada ciudad.
 * Usa struct y por valor.
 */
void mostrarPersonasMasLongevaPorCiudad_Vector(std::vector<Persona> personas);

// Definición de la función que calcula el grupo con más personas de cada ciudad
void calcularGrupoMayorPorCiudad(std::vector<Persona> personas);

// Definición de la función que calcula los promedios de patrimonio por ciudad, y muestra los primeros 3
void calcularPromedioPatrimonio(std::vector<Persona> personas);


#endif // GENERADOR_H