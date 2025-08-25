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

// Crea una persona con datos aleatorios
Persona generarPersona();

// Genera colección de n personas
std::vector<Persona> generarColeccion(int n);

// Busca persona por ID en un vector
// Retorna puntero a persona si la encuentra, nullptr si no
// Búsqueda por ID usando punteros (structs con campos públicos)
const Persona* buscarPorID(const std::vector<Persona>& personas, const std::string& id);

const Persona* buscarMayorPatrimonio(const std::vector<Persona>* personas);

void buscarMayoresPatrimonioPorCiudad(const std::vector<Persona>* personas);

const Persona* buscarPersonaMasLongevaConCondicion(const std::vector<Persona>* personas) ;

void buscarMayoresPatrimonioPorGrupo(const std::vector<Persona>* personas);

void listarPersonasGrupo(const std::vector<Persona>* personas,char grupoDeclaracion,int* contador);

void calcularGrupoMayorPorCiudad(const std::vector<Persona> *personas);

void calcularPromedioPatrimonio(const std::vector<Persona> *personas);

const Persona* buscarMayorDeuda(const std::vector<Persona>* personas);

void buscarMayoresDeudasPorCiudad(const std::vector<Persona>* personas) ;

void buscarMayoresDeudasPorGrupo(const std::vector<Persona>* personas);

void mostrarPersonasMasLongevaPorCiudad_Vector(const std::vector<Persona>* personas);



#endif // GENERADOR_H