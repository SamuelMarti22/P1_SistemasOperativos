#include "generador.h"
#include "persona.h"
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // Generadores aleatorios modernos
#include <vector>
#include <algorithm> // Para find_if
#include <unordered_map>
#include <iomanip>

// --- Bases de datos para generación realista ---

// Nombres femeninos comunes en Colombia
const std::vector<std::string> nombresFemeninos = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
    "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Diana", "Lucía", "Ximena"
};

// Nombres masculinos comunes en Colombia
const std::vector<std::string> nombresMasculinos = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Sofia","Camila","Juana","Ana","Laura","Karla","Andrea","Daniela","Alejandra","Martina",
    "Nelly","María","Nestor","Trinidad","Fernanda", "Carolina", "Lina", "Gertridis"
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

// Implementación de funciones generadoras

std::string generarFechaNacimiento() {
    // Genera día aleatorio (1-28 para simplificar)
    int dia = 1 + rand() % 28;
    // Mes aleatorio (1-12)
    int mes = 1 + rand() % 12;
    // Año entre 1960-2010
    int anio = 1960 + rand() % 50;
    
    // Convierte a string en formato DD/MM/AAAA
    return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio);
}

std::string generarID() {
    static long contador = 1000000000; // ID inicial
    return std::to_string(contador++); // Incrementa después de usar
}

char grupoRenta(int id, bool declarante) {
    if (declarante) {
        if (id < 40) { return 'A'; }
        if (id > 39 && id < 80) { return 'B'; }
        if (id > 79 && id < 100) { return 'C'; }
    } else {
        return 'N';
    }
    return 'N';
}

double randomDouble(double min, double max) {
    // Generador moderno Mersenne Twister
    static std::mt19937 generator(time(nullptr));
    // Distribución uniforme en rango [min, max]
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

/**
 * Implementación de generarPersona para struct y por valor.
 *
 * POR QUÉ: Crear una persona con datos aleatorios.
 * CÓMO: Seleccionando aleatoriamente de las bases de datos y generando números.
 * PARA QUÉ: Generar datos de prueba.
 */
Persona generarPersona() {
    Persona p; // struct, por valor

    // Decide si es hombre o mujer
    bool esHombre = rand() % 2;
    
    // Selecciona nombre según género
    p.nombre = esHombre ? 
        nombresMasculinos[rand() % nombresMasculinos.size()] :
        nombresFemeninos[rand() % nombresFemeninos.size()];
    
    // Construye apellido compuesto (dos apellidos aleatorios)
    p.apellido = apellidos[rand() % apellidos.size()] + " " +
                 apellidos[rand() % apellidos.size()];
    
    // Genera los demás atributos
    p.id = generarID();

    p.ciudadNacimiento = ciudadesColombia[rand() % ciudadesColombia.size()];
    p.fechaNacimiento = generarFechaNacimiento();
    
    // Genera datos financieros realistas
    p.ingresosAnuales = randomDouble(10000000, 500000000);   // 10M a 500M COP
    p.patrimonio = randomDouble(0, 2000000000);              // 0 a 2,000M COP
    p.deudas = randomDouble(0, p.patrimonio * 0.7);          // Deudas hasta el 70% del patrimonio
    p.declaranteRenta = (p.ingresosAnuales > 50000000) && (rand() % 100 > 30); // Probabilidad 70% si ingresos > 50M
    p.grupoDeclaracion = grupoRenta(std::stol(p.id) % 100, p.declaranteRenta);
    
    return p; // struct, por valor
}

std::vector<Persona> generarColeccion(int n) {
    std::vector<Persona> personas;
    // Reserva espacio para n personas (optimización)
    personas.reserve(n);
    
    // Genera n personas y las añade al vector
    for (int i = 0; i < n; ++i) {
        personas.push_back(generarPersona());
    }
    
    return personas;
}

Persona buscarPorID(const std::vector<Persona>& personas, const std::string& id) {
    auto it = std::lower_bound(personas.begin(), personas.end(), id, 
        [](const Persona& p, const std::string& id) {
            return p.id < id;  // Acceso directo al atributo público
        });

    if (it != personas.end() && it->id == id) {
        return *it;  // Retorna copia de la persona encontrada
    } else {
        return generarPersonaVacia();  // Si no se encuentra, devuelve una persona vacía
    }
}

/**
 * Genera una Persona "vacía" con valores por defecto para representar "no encontrado".
 * 
 * POR QUÉ: Necesitamos un objeto Persona válido cuando no se encuentra una persona.
 * CÓMO: Creando una Persona con valores por defecto que se puedan identificar fácilmente.
 * PARA QUÉ: Evitar errores de compilación y mantener el enfoque por valor.
 */
Persona generarPersonaVacia() {
    return Persona{"", "", "", "", "", 0.0, 0.0, 0.0, false, 'N' };
}

Persona buscarMayorPatrimonio(std::vector<Persona> personas) {
    // Si la lista está vacía, devolvemos un objeto Persona vacío
    if (personas.empty()) return generarPersonaVacia();

    // Encontramos y copiamos directamente la persona con mayor patrimonio
    Persona mayor = *std::max_element(personas.begin(), personas.end(),
        [](const Persona& a, const Persona& b) {
            return a.patrimonio < b.patrimonio;
        });

    // Devolvemos la persona con mayor patrimonio
    return mayor;
}

/**
 * Imprime un listado de las personas con mayor patrimonio en cada ciudad.
 *
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada ciudad de Colombia.
 * CÓMO: Usando un mapa temporal para guardar, por ciudad, la persona con
 *       mayor patrimonio encontrada (acceso directo a atributos públicos del struct).
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por ciudad, usando struct y por valor.
 */
void buscarMayoresPatrimonioPorCiudad(std::vector<Persona> personas) {
    std::unordered_map<std::string, Persona> mayoresPorCiudad;
    mayoresPorCiudad.reserve(personas.size());
    // Recorremos todas las personas (acceso directo a atributos públicos)
    for (const auto& p : personas) {
        std::string ciudad = p.ciudadNacimiento;

        auto it = mayoresPorCiudad.find(ciudad);
        if (it == mayoresPorCiudad.end()) {
            mayoresPorCiudad.insert({ciudad, p});
        } else if (p.patrimonio > it->second.patrimonio) {
            it->second = p;
        }
    }
    std::cout << "\n=== Personas con mayor patrimonio por ciudad ===\n";
    for (const auto& par : mayoresPorCiudad) {
        std::cout << "- " << par.first << ": "
                  << par.second.nombre << " "
                  << par.second.apellido << " ("
                  << std::fixed << std::setprecision(2) << par.second.patrimonio << ")\n";
    }
}

/**
 * Imprime un listado de las personas con mayor patrimonio por grupo de declaración.
 * 
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada grupo de declaración.
 * CÓMO: Usando un mapa temporal para ir guardando, por grupo, la persona con
 *       mayor patrimonio encontrada hasta el momento (acceso directo a atributos públicos del struct).
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por grupo usando struct y por valor.
 */
void buscarMayoresPatrimonioPorGrupo(std::vector<Persona> personas) {
    // Mapa temporal que guarda, por cada grupo, la persona con mayor patrimonio
    std::unordered_map<char, Persona> mayoresPorGrupo;
    mayoresPorGrupo.reserve(personas.size()); // evita rehashes innecesarios

    // Recorremos todas las personas (copias, acceso directo a atributos públicos)
    for (const auto& p : personas) {
        char grupo = p.grupoDeclaracion;

        // Si el grupo no existe o esta persona tiene más patrimonio, actualizamos
        auto it = mayoresPorGrupo.find(grupo);
        if (it == mayoresPorGrupo.end()) {
            // Si el grupo no existe, lo insertamos
            mayoresPorGrupo.insert({grupo, p});
        } else if (p.patrimonio > it->second.patrimonio) {
            // Si existe y tiene más patrimonio, actualizamos
            it->second = p;
        }
    }

    std::cout << "\n=== Personas con mayor patrimonio por grupo de declaración ===\n";
    for (const auto& par : mayoresPorGrupo) { 
        std::cout << "- " << par.first << ": "
                  << par.second.nombre << " "
                  << par.second.apellido << " ("
                  << std::fixed << std::setprecision(2) << par.second.patrimonio << ")\n";
    }
}

/**
 * Implementación de buscarPersonaMasLongevaConCondicion--
 * 
 * POR QUÉ: Encontrar la persona más longeva (con la fecha de nacimiento más antigua) en una colección de personas.
 * CÓMO: Recorriendo el vector de personas y comparando fechas de nacimiento; si se encuentra la fecha más antigua posible, termina la búsqueda anticipadamente.
 * PARA QUÉ: Para obtener rápidamente la persona más longeva en el país, optimizando el tiempo si aparece la fecha mínima.
 * (Usa struct y acceso directo a atributos públicos, retorna por valor)
 */
Persona buscarPersonaMasLongevaConCondicion(std::vector<Persona> personas) {
    if (personas.empty()) return generarPersonaVacia();

    const std::string fechaObjetivo = "1/1/1960";  // fecha más antigua posible
    Persona masLongeva = personas[0];              // copia de la primera Persona
    std::string fechaMasLongeva = masLongeva.fechaNacimiento;

    for (size_t i = 1; i < personas.size(); ++i) {
        const std::string fechaActual = personas[i].fechaNacimiento;
        if (fechaActual < fechaMasLongeva) {
            masLongeva = personas[i];
            fechaMasLongeva = masLongeva.fechaNacimiento;
            if (fechaMasLongeva == fechaObjetivo) {
                break; // Ya encontramos la más longeva posible
            }
        }
    }
    return masLongeva; // devuelve copia de la persona más longeva
}

/**
 * Implementación de mostrarPersonasMasLongevaPorCiudad_Vector adaptada para struct y por valor.
 * 
 * POR QUÉ: Mostrar la persona más longeva de cada ciudad en una colección de personas.
 * CÓMO: Recorriendo el vector de personas, agrupando por ciudad y comparando fechas de nacimiento para cada grupo.
 * PARA QUÉ: Para visualizar, por ciudad, quién es la persona más longeva, útil para estadísticas y reportes por región.
 */
void mostrarPersonasMasLongevaPorCiudad_Vector(std::vector<Persona> personas) { //recibe por valor
    std::vector<std::pair<std::string, Persona>> resultado; //lista dinamica de pares (ciudad, persona) por valor

    for (auto persona : personas) {  //copia en cada iteración
        std::string ciudad = persona.ciudadNacimiento; // acceso directo
        auto iter = std::find_if(resultado.begin(), resultado.end(), //observa si ya hay un par con esa ciudad
            [ciudad](const std::pair<std::string, Persona> par) {  //compara el par guardado con ciudad (de la iteración)
                return par.first == ciudad;
            });
        if (iter == resultado.end()) { //si no está la ciudad, se agrega
            resultado.push_back({ciudad, persona}); //copia de la persona
        } else {  //si ya está,compara fechas con la persona(second) y actualiza si es necesario
            if (persona.fechaNacimiento < iter->second.fechaNacimiento) { // acceso directo
                iter->second = persona; //copia de la persona más longeva
            }
        }
    }

    std::cout << "\n=== Persona más longeva por ciudad ===\n";
    for (auto par : resultado) {  //copia del par para mantener enfoque 100% por valor
        std::cout << "- " << par.first << ": "
                  << par.second.nombre << " "      // acceso directo
                  << par.second.apellido << " ("   // acceso directo
                  << par.second.fechaNacimiento << ")\n"; // acceso directo
    }
}

void listarPersonasGrupo(std::vector<Persona> personas, char grupoDeclaracion, int contador) {
    // Recorremos todas las personas y contamos las que cumplen con la condición
    std::cout << "Persona del grupo " << grupoDeclaracion << " encontradas:" << std::endl;
    for (Persona p : personas) {  // copia en cada iteración
        if (p.grupoDeclaracion == grupoDeclaracion) { // acceso directo al atributo del struct
            std::cout << p.id << " " << p.nombre << " " << p.patrimonio << std::endl; // acceso directo
            ++contador;  
        }
    }
}

// Función para calcular el grupo más grande por ciudad (struct y por valor)
void calcularGrupoMayorPorCiudad(std::vector<Persona> personas) {
  // Inicialización de las variables
  int ciudadesGrupos[20][3] = {{0}}; // 20 ciudades, 3 grupos
  std::unordered_map<std::string, int> ciudadIndex = {
      {"Bogotá", 0},       {"Medellín", 1},       {"Cali", 2},
      {"Barranquilla", 3}, {"Cartagena", 4},      {"Bucaramanga", 5},
      {"Pereira", 6},      {"Santa Marta", 7},    {"Cúcuta", 8},
      {"Ibagué", 9},       {"Manizales", 10},     {"Pasto", 11},
      {"Neiva", 12},       {"Villavicencio", 13}, {"Armenia", 14},
      {"Sincelejo", 15},   {"Valledupar", 16},    {"Montería", 17},
      {"Popayán", 18},     {"Tunja", 19}};

  // Recorremos las personas y sumamos los grupos
  for (Persona persona : personas) {  // copia en cada iteración
    std::string ciudad = persona.ciudadNacimiento; // acceso directo
    char grupo = persona.grupoDeclaracion;         // acceso directo

    int index1 = ciudadIndex[ciudad];
    if (grupo != 'N') {
      int index2 = (grupo == 'A' ? 0 : (grupo == 'B' ? 1 : 2));
      ciudadesGrupos[index1][index2]++;
    }
  }

  // Mostrar el grupo mayor por ciudad
  for (int i = 0; i < 20; i++) {
    std::string ciudad;
    switch (i) {
    case 0:  ciudad = "Bogotá"; break;
    case 1:  ciudad = "Medellín"; break;
    case 2:  ciudad = "Cali"; break;
    case 3:  ciudad = "Barranquilla"; break;
    case 4:  ciudad = "Cartagena"; break;
    case 5:  ciudad = "Bucaramanga"; break;
    case 6:  ciudad = "Pereira"; break;
    case 7:  ciudad = "Santa Marta"; break;
    case 8:  ciudad = "Cúcuta"; break;
    case 9:  ciudad = "Ibagué"; break;
    case 10: ciudad = "Manizales"; break;
    case 11: ciudad = "Pasto"; break;
    case 12: ciudad = "Neiva"; break;
    case 13: ciudad = "Villavicencio"; break;
    case 14: ciudad = "Armenia"; break;
    case 15: ciudad = "Sincelejo"; break;
    case 16: ciudad = "Valledupar"; break;
    case 17: ciudad = "Montería"; break;
    case 18: ciudad = "Popayán"; break;
    case 19: ciudad = "Tunja"; break;
    default: ciudad = "Ciudad no encontrada"; break;
    }

    // Encontramos el grupo con más personas
    int mayorGrupo = std::max(
        {ciudadesGrupos[i][0], ciudadesGrupos[i][1], ciudadesGrupos[i][2]});
    char mayorGrupoLetra = (mayorGrupo == ciudadesGrupos[i][0])   ? 'A'
                           : (mayorGrupo == ciudadesGrupos[i][1]) ? 'B'
                                                                  : 'C';

    // Mostramos el resultado
    std::cout << "El grupo con más personas en la ciudad " << ciudad
              << " es el grupo " << mayorGrupoLetra << " con " << mayorGrupo
              << " personas." << std::endl;
  }
}

// Función que calcula el promedio de patrimonio por ciudad (struct y por valor)
void calcularPromedioPatrimonio(std::vector<Persona> personas) {
  double ciudadesPromedios[20] = {0};
  int conteoCiudad[20] = {0};

  // Recorremos a cada persona y sumamos el patrimonio por ciudad
  for (Persona persona : personas) {  // copia en cada iteración
    std::string ciudad = persona.ciudadNacimiento; // acceso directo
    double patrimonio = persona.patrimonio;        // acceso directo

    // Buscar el índice de la ciudad
    int index1;
    for (int i = 0; i < 20; i++) {
      if (ciudadesColombia[i] == ciudad) {
        index1 = i;
        break;
      }
    }
    // Incrementamos la cuenta de personas y sumamos el patrimonio
    ciudadesPromedios[index1] += patrimonio;
    conteoCiudad[index1]++;
  }
  // Creamos un arreglo de pares (promedio, idCiudad) para ordenar
  std::vector<std::pair<float, int>> promediosConId;

  // Calculamos los promedios y agregarlos con su ID
  for (int i = 0; i < 20; i++) {
    if (conteoCiudad[i] > 0) { // Si hay al menos una persona en esa ciudad
      float promedio = ciudadesPromedios[i] / conteoCiudad[i];
      promediosConId.push_back({promedio, i}); // Guardar el promedio junto con el ID de la ciudad
    }
  }

  // Ordenamos por promedio (en orden descendente)
  std::sort(promediosConId.begin(), promediosConId.end(),
            [](std::pair<float, int> a, std::pair<float, int> b) {  // por valor para mantener enfoque 100% por valor
              return a.first > b.first; // Ordenamos por el primer valor (promedio)
            });

  std::cout << "Promedio de patrimonio por ciudad:\n";

  // Ajustar el formato para mostrar sin notación científica
  std::cout << std::fixed << std::setprecision(2); // Fija a dos decimales y evita notación científica
  std::cout << std::showpoint; // Asegura que se muestren los ceros decimales

  for (size_t i = 0; i < 3 && i < promediosConId.size(); ++i) {
    int idCiudad = promediosConId[i].second; // Obtenemos el ID de la ciudad
    std::cout << ciudadesColombia[idCiudad] << ": " << promediosConId[i].first << std::endl;
  }
}


/**
 * Busca la persona con mayor deuda en todo el país (struct y por valor).
 * 
 * POR QUÉ: Determinar la persona con mayor deuda en la colección de personas.
 * CÓMO: Implementando una búsqueda lineal usando std::max_element con una lambda
 *       que compara la deuda de dos personas.
 * PARA QUÉ: Obtener información de la persona con mayor deuda
 *           para su posterior visualización o procesamiento.
 * 
 * @param personas Vector con todas las personas.
 * @return Objeto Persona con mayor deuda, o un objeto Persona vacío si la lista está vacía.
 */
Persona buscarMayorDeuda(std::vector<Persona> personas) {
    // Si la lista está vacía, devolvemos un objeto Persona vacío
    if (personas.empty()) return generarPersonaVacia();

    // Encontramos y copiamos directamente la persona con mayor deuda
    Persona mayor = *std::max_element(personas.begin(), personas.end(),
        [](Persona a, Persona b) {
            return a.deudas < b.deudas; // acceso directo al atributo
        });

    // Devolvemos la persona con mayor deuda
    return mayor;
}

/**
 * Imprime un listado de las personas con mayor deuda en cada ciudad (struct y por valor).
 * 
 * POR QUÉ: Encontrar a la persona con mayor deuda en cada ciudad de la colección.
 * CÓMO: Usando un mapa temporal para ir guardando, por ciudad, la persona con
 *       mayor deuda encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor deuda por ciudad.
 */
void buscarMayoresDeudasPorCiudad(std::vector<Persona> personas) {
    std::unordered_map<std::string, Persona> mayoresPorCiudad;
    mayoresPorCiudad.reserve(personas.size()); // Evita rehashes innecesarios

    // Recorremos todas las personas
    for (auto p : personas) {  // copia en cada iteración
        std::string ciudad = p.ciudadNacimiento; // acceso directo

        auto it = mayoresPorCiudad.find(ciudad);
        if (it == mayoresPorCiudad.end()) {
            // Si la ciudad no existe, la insertamos
            mayoresPorCiudad.insert({ciudad, p});
        } else if (p.deudas > it->second.deudas) { // acceso directo
            // Si existe y tiene más deuda, actualizamos
            it->second = p;  // copia completa
        }
    }

    std::cout << "\n=== Personas con mayor deuda por ciudad ===\n";
    for (auto par : mayoresPorCiudad) { 
      std::cout << "- " << par.first << ": "
                << par.second.nombre << " "      // acceso directo
                << par.second.apellido << " ("   // acceso directo
                << std::fixed << std::setprecision(2) << par.second.deudas << ")\n"; // acceso directo
    }
}

/**
 * Imprime un listado de las personas con mayor deuda por grupo de declaración (struct y por valor).
 * 
 * POR QUÉ: Encontrar a la persona con mayor deuda en cada grupo de declaración.
 * CÓMO: Usando un mapa temporal para ir guardando, por grupo, la persona con
 *       mayor deuda encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor deuda por grupo.
 */
void buscarMayoresDeudasPorGrupo(std::vector<Persona> personas) {
    // Mapa temporal que guarda, por cada grupo, la persona con mayor deuda
    std::unordered_map<char, Persona> mayoresPorGrupo;
    mayoresPorGrupo.reserve(personas.size()); // evita rehashes innecesarios

    // Recorremos todas las personas (copias)
    for (auto p : personas) {
        char grupo = p.grupoDeclaracion; // acceso directo

        // Si el grupo no existe o esta persona tiene más deuda, actualizamos
        auto it = mayoresPorGrupo.find(grupo);
        if (it == mayoresPorGrupo.end()) {
            // Si el grupo no existe, lo insertamos
            mayoresPorGrupo.insert({grupo, p});
        } else if (p.deudas > it->second.deudas) { // acceso directo
            // Si existe y tiene más deuda, actualizamos
            it->second = p; // copia completa de Persona
        }
    }

    std::cout << "\n=== Personas con mayor deuda por grupo de declaración ===\n";
    for (auto par : mayoresPorGrupo) { 
      std::cout << "- " << par.first << ": "
                << par.second.nombre << " "      // acceso directo
                << par.second.apellido << " ("   // acceso directo
                << std::fixed << std::setprecision(2) << par.second.deudas << ")\n"; // acceso directo
    }
}