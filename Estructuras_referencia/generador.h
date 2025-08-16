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
const Persona* buscarPorID(const std::vector<Persona>& personas, const std::string& id);

#endif // GENERADOR_H