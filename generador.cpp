#include "generador.h"
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // std::mt19937, std::uniform_real_distribution
#include <vector>
#include <algorithm> // std::find_if
#include <unordered_map> // std::unordered_map

// Bases de datos para generación realista

// Nombres femeninos comunes en Colombia
const std::vector<std::string> nombresFemeninos = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
    "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Diana", "Lucía", "Ximena"
};

// Nombres masculinos comunes en Colombia
const std::vector<std::string> nombresMasculinos = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Nestor", "Gertridis"
};

// Apellidos comunes en Colombia
const std::vector<std::string> apellidos = {
    "Gómez", "Rodríguez", "Martínez", "López", "García", "Pérez", "González", "Sánchez", "Ramírez", "Torres",
    "Díaz", "Vargas", "Castro", "Ruiz", "Álvarez", "Romero", "Suárez", "Rojas", "Moreno", "Muñoz", "Valencia",
};

// Principales ciudades colombianas
const std::vector<std::string> ciudadesColombia = {
    "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
    "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
};

/**
 * Implementación de generarFechaNacimiento.
 * 
 * POR QUÉ: Simular fechas de nacimiento realistas.
 * CÓMO: Día (1-28), mes (1-12), año (1960-2009).
 * PARA QUÉ: Atributo fechaNacimiento de Persona.
 */
std::string generarFechaNacimiento() {
    int dia = 1 + rand() % 28;       // Día: 1 a 28 (evita problemas con meses)
    int mes = 1 + rand() % 12;        // Mes: 1 a 12
    int anio = 1960 + rand() % 50;    // Año: 1960 a 2009
    return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio);
}

/**
 * Implementación de generarID.
 * 
 * POR QUÉ: Generar identificadores únicos y secuenciales.
 * CÓMO: Contador estático que inicia en 1000000000 y se incrementa.
 * PARA QUÉ: Simular números de cédula.
 */
int generarID() {
    static long contador = 1000000000; // Inicia en 1,000,000,000
    return contador++; // Convierte a string e incrementa
}

/**
 * Implementación de randomDouble.
 * 
 * POR QUÉ: Generar números decimales aleatorios en un rango.
 * CÓMO: Mersenne Twister (mejor que rand()) y distribución uniforme.
 * PARA QUÉ: Valores de ingresos, patrimonio, etc.
 */
double randomDouble(double min, double max) {
    static std::mt19937 generator(time(nullptr)); // Semilla basada en tiempo
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

char grupoRenta(int id, bool declarante){
    if (declarante){
        if (id<40){ return 'A';}
        if (id>39 && id <80) {return 'B';}
        if (id>79 && id<100) {return 'C';}}
    else{
        return 'N';
    }
}
/**
 * Implementación de generarPersona.
 * 
 * POR QUÉ: Crear una persona con datos aleatorios.
 * CÓMO: Seleccionando aleatoriamente de las bases de datos y generando números.
 * PARA QUÉ: Generar datos de prueba.
 */
Persona generarPersona() {
    // Decide si es hombre o mujer
    bool esHombre = rand() % 2;
    
    // Selecciona nombre según género
    std::string nombre = esHombre ? 
        nombresMasculinos[rand() % nombresMasculinos.size()] :
        nombresFemeninos[rand() % nombresFemeninos.size()];
    
    // Construye apellido compuesto (dos apellidos aleatorios)
    std::string apellido = apellidos[rand() % apellidos.size()];
    apellido += " ";
    apellido += apellidos[rand() % apellidos.size()];
    
    // Genera los demás atributos
    long id = generarID();

    std::string ciudad = ciudadesColombia[rand() % ciudadesColombia.size()];
    std::string fecha = generarFechaNacimiento();
    
    // Genera datos financieros realistas
    double ingresos = randomDouble(10000000, 500000000);   // 10M a 500M COP
    double patrimonio = randomDouble(0, 2000000000);       // 0 a 2,000M COP
    double deudas = randomDouble(0, patrimonio * 0.7);     // Deudas hasta el 70% del patrimonio
    bool declarante = (ingresos > 50000000) && (rand() % 100 > 30); // Probabilidad 70% si ingresos > 50M
    char grupoDeclaracion = grupoRenta(id%100, declarante);
    
    return Persona(nombre, apellido, std::to_string(id), ciudad, fecha, ingresos, patrimonio, deudas, declarante, grupoDeclaracion);
}

/**
 * Implementación de generarColeccion.
 * 
 * POR QUÉ: Generar un conjunto de n personas.
 * CÓMO: Reservando espacio y agregando n personas generadas.
 * PARA QUÉ: Crear datasets para pruebas.
 */
std::vector<Persona> generarColeccion(int n) {
    std::vector<Persona> personas;
    personas.reserve(n); // Reserva espacio para n personas (eficiencia)
    
    for (int i = 0; i < n; ++i) {
        personas.push_back(generarPersona());
    }
    
    return personas;
}

/**
 * Implementación de buscarPorID.
 * 
 * POR QUÉ: Encontrar una persona por su ID en una colección.
 * CÓMO: Usando un algoritmo de búsqueda secuencial (lineal).
 * PARA QUÉ: Para operaciones de búsqueda en la aplicación.
 */
const Persona* buscarPorID(const std::vector<Persona>& personas, const std::string& id) {
    // Usamos lower_bound para encontrar la posición del primer elemento no menor que 'id'
    auto it = std::lower_bound(personas.begin(), personas.end(), id, 
        [](const Persona& p, const std::string& id) {
            return p.getId() < id;  // Compara por el ID de la persona
        });

    // Verificamos si encontramos el elemento exacto
    if (it != personas.end() && it->getId() == id) {
        return &(*it);  // Retorna un puntero a la persona encontrada
    } else {
        return nullptr;  // Si no se encuentra, devuelve nullptr
    }
}

/**
 * Implementación de buscarMayorPatrimonio.
 * 
 * POR QUÉ: Determinar la persona con mayor patrimonio en Colombia.
 * CÓMO: Implementando una búsqueda lineal usando std::max_element con una lambda
 *       que compara el patrimonio de dos personas.
 * PARA QUÉ: Obtener información de la persona con mayor patrimonio en el país
 *           para su posterior visualización o procesamiento.
 */
const Persona* buscarMayorPatrimonio(const std::vector<Persona>& personas) {
    // Si no hay personas en la colección, no hay máximo que buscar
    if (personas.empty()) return nullptr;

    // std::max_element recorre el rango y devuelve un iterador al elemento máximo
    // La lambda compara dos Personas devolviendo true si 'a' tiene patrimonio menor que 'b'
    auto it = std::max_element(personas.begin(), personas.end(),
        [](const Persona& a, const Persona& b) {
            return a.getPatrimonio() < b.getPatrimonio();
        });

    // Retornamos un puntero a la Persona con mayor patrimonio
    return &(*it);
}

/**
 * Obtiene una lista con las personas que tienen el mayor patrimonio en cada ciudad.
 * 
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada ciudad de Colombia.
 * CÓMO: Usando un mapa temporal para ir guardando, por ciudad, la persona con
 *       mayor patrimonio encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por ciudad.
 * 
 * @param personas   Vector con todas las personas.
 * @return           Vector de punteros a las personas con mayor patrimonio en cada ciudad.
 */
std::vector<const Persona*> buscarMayoresPorCiudad(const std::vector<Persona>& personas) {
    std::unordered_map<std::string, const Persona*> mayoresPorCiudad;
    mayoresPorCiudad.reserve(personas.size()); // Evita rehashes innecesarios

    // Recorremos todas las personas
    for (const auto& p : personas) {
        const std::string& ciudad = p.getCiudadNacimiento(); // referencia para evitar copia

        auto it = mayoresPorCiudad.find(ciudad);
        if (it == mayoresPorCiudad.end() || p.getPatrimonio() > it->second->getPatrimonio()) {
            mayoresPorCiudad[ciudad] = &p;
        }
    }

    // Convertimos el mapa en un vector (versión compatible con C++14, sin structured bindings)
    std::vector<const Persona*> resultado;
    resultado.reserve(mayoresPorCiudad.size());

    for (const auto& par : mayoresPorCiudad) {
        const std::string& ciudad = par.first;
        const Persona* persona = par.second;
        resultado.push_back(persona);
    }

    return resultado;
}

/**
 * Obtiene una lista con las personas que tienen el mayor patrimonio por grupo de declaración.
 * 
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada grupo de declaración.
 * CÓMO: Usando un mapa temporal para ir guardando, por grupo, la persona con
 *       mayor patrimonio encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por grupo.
 * 
 * @param personas   Vector con todas las personas.
 * @return           Vector de punteros a las personas con mayor patrimonio en cada grupo.
 */
std::vector<const Persona*> buscarMayoresPorGrupo(const std::vector<Persona>& personas) {
    std::unordered_map<char, const Persona*> mayoresPorGrupo;
    mayoresPorGrupo.reserve(personas.size()); // Evita rehashes innecesarios

    // Recorremos todas las personas
    for (const auto& p : personas) {
        char grupo = p.getGrupoDeclaracion();

        auto it = mayoresPorGrupo.find(grupo);
        if (it == mayoresPorGrupo.end() || p.getPatrimonio() > it->second->getPatrimonio()) {
            mayoresPorGrupo[grupo] = &p;
        }
    }

    // Convertimos el mapa en un vector (versión compatible con C++14)
    std::vector<const Persona*> resultado;
    resultado.reserve(mayoresPorGrupo.size());

    for (const auto& par : mayoresPorGrupo) {
        char grupo = par.first;
        const Persona* persona = par.second;
        resultado.push_back(persona);
    }

    return resultado;
}

/**
 * Implementación de buscarPersonaMasLongevaConCondicion.
 * 
 * POR QUÉ: Encontrar la persona más longeva (con la fecha de nacimiento más antigua) en una colección de personas.
 * CÓMO: Recorriendo el vector de personas y comparando fechas de nacimiento; si se encuentra la fecha más antigua posible, termina la búsqueda anticipadamente.
 * PARA QUÉ: Para obtener rápidamente la persona más longeva en el país, optimizando el tiempo si aparece la fecha mínima.
 */
const Persona* buscarPersonaMasLongevaConCondicion(const std::vector<Persona>& personas) { //toma el vector de Persona como input
    if (personas.empty()) return nullptr;

    const std::string fechaObjetivo = "1/1/1960";  //fecha mas antigua posible
    const Persona* masLongeva = &personas[0];  //inicialización de puntero con primera Persona
    std::string fechaMasLongeva = masLongeva->getFechaNacimiento();   

    for (size_t i = 1; i < personas.size(); ++i) {  //recorrido del vector desde la seguna Persona
        const std::string fechaActual = personas[i].getFechaNacimiento();
        if (fechaActual < fechaMasLongeva) {   
            masLongeva = &personas[i];  //actualiza puntero despues de comparación
            fechaMasLongeva = masLongeva->getFechaNacimiento();
            if (fechaMasLongeva == fechaObjetivo) {
                break; // Ya encontramos la más longeva posible
            }
        }
    }
    return masLongeva;   //puntero a la mas longeva
}


/**
 * Implementación de mostrarPersonasMasLongevaPorCiudad_Vector.
 * 
 * POR QUÉ: Mostrar la persona más longeva de cada ciudad en una colección de personas.
 * CÓMO: Recorriendo el vector de personas, agrupando por ciudad y comparando fechas de nacimiento para cada grupo.
 * PARA QUÉ: Para visualizar, por ciudad, quién es la persona más longeva, útil para estadísticas y reportes por región.
 */
void mostrarPersonasMasLongevaPorCiudad_Vector(const std::vector<Persona>& personas) { //recibe referencia
    std::vector<std::pair<std::string, const Persona*>> resultado; //lista dinamica de pares (ciudad, persona*) 

    for (const auto& persona : personas) {  
        std::string ciudad = persona.getCiudadNacimiento();
        auto iter = std::find_if(resultado.begin(), resultado.end(), //observa si ya hay un par con esa ciudad
            [&ciudad](const std::pair<std::string, const Persona*>& par) {  //compara el  par guardado con ciudad (de la iteración)
                return par.first == ciudad;
            });
        if (iter == resultado.end()) { //si no está la ciudad, se agrega
            resultado.push_back({ciudad, &persona});
        } else {  //si ya está,compara fechas con la persona(second) y actualiza si es necesario
            if (persona.getFechaNacimiento() < iter->second->getFechaNacimiento()) {
                iter->second = &persona;
            }
        }
    }

    std::cout << "\n=== Persona más longeva por ciudad ===\n";
    for (const auto& par : resultado) {
        std::cout << "- " << par.first << ": "
                  << par.second->getNombre() << " "
                  << par.second->getApellido() << " ("
                  << par.second->getFechaNacimiento() << ")\n";
    }
}

void listarPersonasGrupo(const std::vector<Persona>& personas, char grupoDeclaracion, int& contador) {
    // Recorremos todas las personas y contamos las que cumplen con la condición
    std::cout << "Persona del grupo " << grupoDeclaracion << " encontradas:"<<std::endl;
    for (const Persona& p : personas) {
        if (p.getGrupoDeclaracion() == grupoDeclaracion) {
            std::cout << p.getId()<<" "<<p.getNombre()<<" "<<p.getPatrimonio() << std::endl;
            ++contador;  
        }
    }
}