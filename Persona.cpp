#include "persona.h"
#include <iostream>
#include <iomanip>  

Persona::Persona(const std::string& nombre, const std::string& apellido, const std::string& id,
                 const std::string& fechaNacimiento, const std::string& ciudad,
                 double ingresosAnuales, double patrimonio, double deudas, bool declaranteRenta)
    : nombre(nombre),
      apellido(apellido),
      id(id),
      fechaNacimiento(fechaNacimiento),
      ciudad(ciudad),
      ingresosAnuales(ingresosAnuales),
      patrimonio(patrimonio),
      deudas(deudas),
      declaranteRenta(declaranteRenta)
{}

//Implementación de getters (const)

std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getId() const { return id; }
std::string Persona::getFechaNacimiento() const { return fechaNacimiento; }
std::string Persona::getCiudad() const { return ciudad; }
double Persona::getIngresosAnuales() const { return ingresosAnuales; }
double Persona::getPatrimonio() const { return patrimonio; }
double Persona::getDeudas() const { return deudas; }
bool Persona::getDeclaranteRenta() const { return declaranteRenta; }

// Muestra información detallada de la persona
void Persona::mostrar() const {
    std::cout << "-------------------------------------\n";
    // Encabezado con cédula y nombre completo
    std::cout << "[" << id << "] Nombre: " << nombre << " " << apellido << "\n";
    // Datos personales
    std::cout << "   - Ciudad: " << ciudad << "\n";
    std::cout << "   - Fecha de nacimiento: " << fechaNacimiento << "\n\n";
    
    // Formato para valores monetarios (2 decimales)
    std::cout << std::fixed << std::setprecision(2);
    
    // Datos económicos
    std::cout << "   - Ingresos anuales: $" << ingresosAnuales << "\n";
    std::cout << "   - Patrimonio: $" << patrimonio << "\n";
    std::cout << "   - Deudas: $" << deudas << "\n";
    // Operador ternario para mostrar Sí/No según condición booleana
    std::cout << "   - Declarante de renta: " << (declaranteRenta ? "Sí" : "No") << "\n";
}

// Versión compacta para mostrar en listados
void Persona::mostrarResumen() const {
    // ID, nombre completo, ciudad e ingresos en una sola línea
    std::cout << "[" << id << "] " << nombre << " " << apellido
              << " | " << ciudad 
              << " | $" << std::fixed << std::setprecision(2) << ingresosAnuales;
}