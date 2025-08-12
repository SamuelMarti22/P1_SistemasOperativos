#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"
#include <vector>

// --- Funciones para generación de datos aleatorios ---

// Genera fecha aleatoria
std::string generarFechaNacimiento();

// Generar cédula única secuencial
std::string generarCedula();

// Crear persona aleatoriamente
Persona generarPersona();

// Generar lista de personas
std::vector<Persona> ListaPersonas(int n);

#endif // GENERADOR_H

