#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
private:

    std::string nombre;           
    std::string apellido;         
    std::string id;
    std::string fechaNacimiento;                 
    std::string ciudad; 
    double ingresosAnuales;       
    double patrimonio;            
    double deudas;               
    bool declaranteRenta;         

public:
    PersonaRef(const std::string& nombre, const std::string& apellido, const std::string& id,
        const std::string& fechaNacimiento, const std::string& ciudad,
        double ingresosAnuales, double patrimonio, double deudas, bool declaranteRenta);

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getId() const;
    std::string getFechaNacimiento() const;
    std::string getCiudad() const;
    double getIngresosAnuales() const;
    double getPatrimonio() const;
    double getDeudas() const;
    bool getDeclaranteRenta() const;

    void mostrar() const;         
    void mostrarResumen() const;  
};

#endif 