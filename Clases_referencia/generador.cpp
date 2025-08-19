#include "generador.h"
#include <algorithm> // std::find_if
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // std::mt19937, std::uniform_real_distribution
#include <unordered_map>
#include <vector>
#include <unordered_map> // std::unordered_map
#include <iomanip> // std::setprecision

// Bases de datos para generación realista

// Nombres femeninos comunes en Colombia
const std::vector<std::string> nombresFemeninos = {
    "María",    "Luisa",   "Carmen",   "Ana",      "Sofía",
    "Isabel",   "Laura",   "Andrea",   "Paula",    "Valentina",
    "Camila",   "Daniela", "Carolina", "Fernanda", "Gabriela",
    "Patricia", "Claudia", "Diana",    "Lucía",    "Ximena"};

// Nombres masculinos comunes en Colombia
const std::vector<std::string> nombresMasculinos = {
    "Juan",   "Carlos",   "José",      "James",    "Andrés",   "Miguel",
    "Luis",   "Pedro",    "Alejandro", "Ricardo",  "Felipe",   "David",
    "Jorge",  "Santiago", "Daniel",    "Fernando", "Diego",    "Rafael",
    "Martín", "Óscar",    "Edison",    "Nestor",   "Gertridis"};

// Apellidos comunes en Colombia
const std::vector<std::string> apellidos = {
    "Gómez",   "Rodríguez", "Martínez", "López", "García", "Pérez",  "González",
    "Sánchez", "Ramírez",   "Torres",   "Díaz",  "Vargas", "Castro", "Ruiz",
    "Álvarez", "Romero",    "Suárez",   "Rojas", "Moreno", "Muñoz",  "Valencia",
};

// Principales ciudades colombianas
const std::vector<std::string> ciudadesColombia = {
    "Bogotá",      "Medellín",   "Cali",        "Barranquilla",  "Cartagena",
    "Bucaramanga", "Pereira",    "Santa Marta", "Cúcuta",        "Ibagué",
    "Manizales",   "Pasto",      "Neiva",       "Villavicencio", "Armenia",
    "Sincelejo",   "Valledupar", "Montería",    "Popayán",       "Tunja"};

const std::vector<std::string> &ciudadesColombiaRef = ciudadesColombia;
/**
 * Implementación de generarFechaNacimiento.
 *
 * POR QUÉ: Simular fechas de nacimiento realistas.
 * CÓMO: Día (1-28), mes (1-12), año (1960-2009).
 * PARA QUÉ: Atributo fechaNacimiento de Persona.
 */
std::string generarFechaNacimiento() {
  int dia = 1 + rand() % 28;     // Día: 1 a 28 (evita problemas con meses)
  int mes = 1 + rand() % 12;     // Mes: 1 a 12
  int anio = 1960 + rand() % 50; // Año: 1960 a 2009
  return std::to_string(dia) + "/" + std::to_string(mes) + "/" +
         std::to_string(anio);
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
  return contador++;                 // Convierte a string e incrementa
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
const Persona* buscarPorID(const std::vector<Persona>* personas, const std::string* id) {
    // Usamos lower_bound para encontrar la posición del primer elemento no menor que 'id'
    auto it = std::lower_bound(personas->begin(), personas->end(), *id, 
        [](const Persona& p, const std::string& id) {
            return p.getId() < id;  // Compara por el ID de la persona
        });

    // Verificamos si encontramos el elemento exacto
    if (it != personas->end() && it->getId() == *id) {
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
const Persona* buscarMayorPatrimonio(const std::vector<Persona>* personas) {
    // Si no hay personas en la colección, no hay máximo que buscar
    if (personas->empty()) return nullptr;

    // std::max_element recorre el rango y devuelve un iterador al elemento máximo
    // La lambda compara dos Personas devolviendo true si 'a' tiene patrimonio menor que 'b'
    auto it = std::max_element(personas->begin(), personas->end(),
        [](const Persona& a, const Persona& b) {
            return a.getPatrimonio() < b.getPatrimonio();
        });

    // Retornamos un puntero a la Persona con mayor patrimonio
    return &(*it);
}

/**
 * Imprime un listado de las personas con mayor patrimonio en cada ciudad.
 * 
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada ciudad de Colombia.
 * CÓMO: Usando un mapa temporal para ir guardando, por ciudad, la persona con
 *       mayor patrimonio encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por ciudad.
 */

// Busca e imprime la persona con mayor patrimonio por cada ciudad
void buscarMayoresPatrimonioPorCiudad(const std::vector<Persona>* personas) {
  // Mapa que guarda, para cada ciudad, un puntero a la Persona con mayor patrimonio
  std::unordered_map<std::string, const Persona*> mayoresPorCiudad;
  mayoresPorCiudad.reserve(64); // Reserva aproximada para evitar rehashes innecesarios

  // Recorremos todas las personas y seleccionamos la de mayor patrimonio por ciudad
  for (const auto& p : *personas) {
      const std::string& ciudad = p.getCiudadNacimiento(); // obtenemos la ciudad

      // Referencia al puntero asociado a esa ciudad en el mapa.
      // Si la ciudad no existe aún, se crea con valor nullptr.
      const Persona*& best = mayoresPorCiudad[ciudad];

      // Si no había persona registrada o esta tiene más patrimonio, actualizamos
      if (best == nullptr || p.getPatrimonio() > best->getPatrimonio()) {
          best = &p;
      }
  }

  // Encabezado de salida
  std::cout << "\n=== Personas con mayor patrimonio por ciudad ===\n";

  // Configuramos el formato: fijo, con decimales (2) → se imprime como decimal
  std::cout << std::fixed << std::setprecision(2);

  // Recorremos el mapa e imprimimos los resultados
  for (const auto& kv : mayoresPorCiudad) {
      const std::string& ciudad = kv.first;   // clave del mapa = ciudad
      const Persona* persona = kv.second;     // valor = puntero a Persona
      if (!persona) continue;                 // seguridad por si hubiera nulos

      // Mostramos ciudad y datos de la persona con mayor patrimonio
      std::cout << "- " << ciudad << ": "
                << persona->getNombre() << " "
                << persona->getApellido() << " ("
                << persona->getPatrimonio() << ")\n";
  }
}

/**
 * Imprime un listado de las personas con mayor patrimonio por grupo de declaración.
 * 
 * POR QUÉ: Encontrar a la persona con mayor patrimonio en cada grupo de declaración.
 * CÓMO: Usando un mapa temporal para ir guardando, por grupo, la persona con
 *       mayor patrimonio encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor patrimonio por grupo.
 */
 // Busca e imprime la persona con mayor patrimonio por cada grupo
void buscarMayoresPatrimonioPorGrupo(const std::vector<Persona>* personas) {
  // Mapa que guarda, para cada grupo (char), un puntero a la Persona con mayor patrimonio encontrada
  std::unordered_map<char, const Persona*> mayoresPorGrupo;
  mayoresPorGrupo.reserve(personas->size()); // Reservamos espacio (si son pocos grupos, esto se puede ajustar)

  // Recorremos todas las personas para determinar la de mayor patrimonio por grupo
  for (const auto& p : *personas) {
      char grupo = p.getGrupoDeclaracion(); // Obtenemos el grupo de declaración

      auto it = mayoresPorGrupo.find(grupo);
      // Si el grupo no está en el mapa o encontramos una persona con mayor patrimonio, actualizamos
      if (it == mayoresPorGrupo.end() || p.getPatrimonio() > it->second->getPatrimonio()) {
          mayoresPorGrupo[grupo] = &p;
      }
  }

  // Encabezado del reporte
  std::cout << "\n=== Personas con mayor patrimonio por grupo ===\n";

  // Configuramos el formato numérico una sola vez:
  // - std::fixed: siempre notación decimal (no científica)
  // - std::setprecision(2): con dos decimales, es decir, número decimal
  std::cout << std::fixed << std::setprecision(2);

  // Recorremos el mapa e imprimimos los resultados
  for (const auto& kv : mayoresPorGrupo) { // kv es un par {grupo, persona}
      char grupo = kv.first;               // La clave del mapa es el grupo
      const Persona* persona = kv.second;  // El valor es un puntero a la Persona correspondiente
      if (!persona) continue;              // Seguridad: si no hay persona, saltamos

      // Imprimimos el grupo y los datos de la persona con mayor patrimonio
      std::cout << "- " << grupo << ": "
                << persona->getNombre() << " "
                << persona->getApellido() << " ("
                << persona->getPatrimonio() << ")\n";
  }
}



/**
 * Implementación de buscarPersonaMasLongevaConCondicion--
 * 
 * POR QUÉ: Encontrar la persona más longeva (con la fecha de nacimiento más antigua) en una colección de personas.
 * CÓMO: Recorriendo el vector de personas y comparando fechas de nacimiento; si se encuentra la fecha más antigua posible, termina la búsqueda anticipadamente.
 * PARA QUÉ: Para obtener rápidamente la persona más longeva en el país, optimizando el tiempo si aparece la fecha mínima.
 */
const Persona* buscarPersonaMasLongevaConCondicion(const std::vector<Persona>* personas) { //toma el vector de Persona como input
    if (personas->empty()) return nullptr;

    const std::string fechaObjetivo = "1/1/1960";  //fecha mas antigua posible
    const Persona* masLongeva = &(*personas)[0];  //inicialización de puntero con primera Persona
    std::string fechaMasLongeva = masLongeva->getFechaNacimiento();   

    for (size_t i = 1; i < personas->size(); ++i) {  //recorrido del vector desde la seguna Persona
        const std::string fechaActual = (*personas)[i].getFechaNacimiento();
        if (fechaActual < fechaMasLongeva) {   
            masLongeva = &(*personas)[i];  //actualiza puntero despues de comparación
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
void mostrarPersonasMasLongevaPorCiudad_Vector(const std::vector<Persona>* personas) { //recibe referencia
    std::vector<std::pair<std::string, const Persona*>> resultado; //lista dinamica de pares (ciudad, persona*) 

    for (const auto& persona : *personas) {  
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
void listarPersonasGrupo(const std::vector<Persona>* personas,char grupoDeclaracion,int* contador) {
    if (!personas) { std::cerr << "[listar] personas == nullptr\n"; return; }
    if (!contador) { std::cerr << "[listar] contador == nullptr\n"; return; }

    // Opcional: normalizar a mayúscula por si el usuario escribe 'a'/'b'/'c'
    grupoDeclaracion = std::toupper(static_cast<unsigned char>(grupoDeclaracion));

    std::cout << "Personas del grupo " << grupoDeclaracion << " encontradas:\n";
    for (const Persona& p : *personas) {
        if (p.getGrupoDeclaracion() == grupoDeclaracion) {
            std::cout << p.getId() << " " << p.getNombre() << " " << p.getPatrimonio() << "\n";
            ++(*contador);
        }
    }
}

/**
 * Implementación de calcularGrupoMayorPorCiudad.
 * 
 * POR QUÉ: Calcular el grupo con más personas en cada ciudad.
 * CÓMO: Recorriendo el vector de personas, agrupando por grupo y las cantidades de cada grupo por ciudad.
 * PARA QUÉ: Para visualizar, por ciudad, cuál es el grupo con más personas, útil para estadísticas y reportes por región.
 */
// Función para calcular el grupo más grande por ciudad
void calcularGrupoMayorPorCiudad(const std::vector<Persona> *personas) {
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
  for (const Persona &persona : *personas) {
    std::string ciudad = persona.getCiudadNacimiento();
    char grupo = persona.getGrupoDeclaracion();

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
    case 0:
      ciudad = "Bogotá";
      break;
    case 1:
      ciudad = "Medellín";
      break;
    case 2:
      ciudad = "Cali";
      break;
    case 3:
      ciudad = "Barranquilla";
      break;
    case 4:
      ciudad = "Cartagena";
      break;
    case 5:
      ciudad = "Bucaramanga";
      break;
    case 6:
      ciudad = "Pereira";
      break;
    case 7:
      ciudad = "Santa Marta";
      break;
    case 8:
      ciudad = "Cúcuta";
      break;
    case 9:
      ciudad = "Ibagué";
      break;
    case 10:
      ciudad = "Manizales";
      break;
    case 11:
      ciudad = "Pasto";
      break;
    case 12:
      ciudad = "Neiva";
      break;
    case 13:
      ciudad = "Villavicencio";
      break;
    case 14:
      ciudad = "Armenia";
      break;
    case 15:
      ciudad = "Sincelejo";
      break;
    case 16:
      ciudad = "Valledupar";
      break;
    case 17:
      ciudad = "Montería";
      break;
    case 18:
      ciudad = "Popayán";
      break;
    case 19:
      ciudad = "Tunja";
      break;
    default:
      ciudad = "Ciudad no encontrada";
      break;
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

/**
 * Implementación de calcularPromedioPatrimonio.
 * 
 * POR QUÉ: Calcular el patrimonio promedio de cada ciudad, y mostrar los 3 primeros.
 * CÓMO: Recorriendo el vector de personas, e ir haciendo la sumatoria de los patrimonios por ciudad, y la cuenta de personas por ciudad, para al final asignarle a cada ciudad su promedio, organizando las ciudades por promedio, y mostrando las 3 con el promedio más alto.
 * PARA QUÉ: Para visualizar, en el país, las 3 ciudades con el promedio de patrimonio más alto, útil para estadísticas y reportes de la región.
 */
// Función que calcula el promedio de patrimonio por ciudad
void calcularPromedioPatrimonio(const std::vector<Persona> *personas) {
  double ciudadesPromedios[20] = {0};
  int conteoCiudad[20] = {0};

  // Recorremos a cada persona y sumamos el patrimonio por ciudad
  for (const Persona &persona : *personas) {
    std::string ciudad = persona.getCiudadNacimiento();
    double patrimonio = persona.getPatrimonio();

    // Buscar el índice de la ciudad
    int index1;
    for (int i = 0; i < 20; i++) {
      if (ciudadesColombiaRef[i] == ciudad) {
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
      promediosConId.push_back(
          {promedio, i}); // Guardar el promedio junto con el ID de la ciudad
    }
  }

  // Ordenamos por promedio (en orden descendente)
  std::sort(promediosConId.begin(), promediosConId.end(),
            [](const std::pair<float, int> &a, const std::pair<float, int> &b) {
              return a.first >
                     b.first; // Ordenamos por el primer valor (promedio)
            });

  std::cout << "Promedio de patrimonio por ciudad:\n";

  // Ajustar el formato para mostrar sin notación científica
  std::cout << std::fixed
            << std::setprecision(
                   2); // Fija a dos decimales y evita notación científica
  std::cout << std::showpoint; // Asegura que se muestren los ceros decimales

  for (int i = 0; i < 3 && i < promediosConId.size(); ++i) {
    int idCiudad = promediosConId[i].second; // Obtenemos el ID de la ciudad
    std::cout << ciudadesColombia[idCiudad] << ": " << promediosConId[i].first
              << std::endl;
  }
}

/**
 * Implementación de buscarMayorDeuda.
 * 
 * POR QUÉ: Determinar la persona con mayor deuda en la colección de personas.
 * CÓMO: Implementando una búsqueda lineal usando std::max_element con una lambda
 *       que compara la deuda de dos personas.
 * PARA QUÉ: Obtener información de la persona con mayor deuda
 *           para su posterior visualización o procesamiento.
 */
const Persona* buscarMayorDeuda(const std::vector<Persona>* personas) {
    // Si no hay personas en la colección, no hay máximo que buscar
    if (personas->empty()) return nullptr;

    // std::max_element recorre el rango y devuelve un iterador al elemento máximo
    // La lambda compara dos Personas devolviendo true si 'a' tiene deuda menor que 'b'
    auto it = std::max_element(personas->begin(), personas->end(),
        [](const Persona& a, const Persona& b) {
            return a.getDeudas() < b.getDeudas();
        });

    // Retornamos un puntero a la Persona con mayor deuda
    return &(*it);
}

/**
 * Imprime un listado de las personas con mayor deuda en cada ciudad.
 * 
 * POR QUÉ: Encontrar a la persona con mayor deuda en cada ciudad de la colección.
 * CÓMO: Usando un mapa temporal para ir guardando, por ciudad, la persona con
 *       mayor deuda encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor deuda por ciudad.
 */
 void buscarMayoresDeudasPorCiudad(const std::vector<Persona>* personas) {
  // Mapa que guarda, para cada ciudad, un puntero a la Persona con mayor deuda encontrada
  std::unordered_map<std::string, const Persona*> mayoresPorCiudad;
  mayoresPorCiudad.reserve(personas->size()); // Reservamos (se puede ajustar según nº de ciudades)

  // Recorremos todas las personas y actualizamos si encontramos mayor deuda en la ciudad
  for (const auto& p : *personas) {
      const std::string& ciudad = p.getCiudadNacimiento(); // ciudad asociada a la persona
      auto it = mayoresPorCiudad.find(ciudad);

      // Si la ciudad no estaba o la persona actual tiene más deuda, actualizamos
      if (it == mayoresPorCiudad.end() || p.getDeudas() > it->second->getDeudas()) {
          mayoresPorCiudad[ciudad] = &p;
      }
  }

  // Encabezado del reporte
  std::cout << "\n=== Personas con mayor deuda por ciudad ===\n";

  // Configuramos el formato de salida una sola vez:
  // - std::fixed: evita notación científica
  // - std::setprecision(2): con dos decimales → valor decimal
  std::cout << std::fixed << std::setprecision(2);

  // Recorremos el mapa e imprimimos los resultados
  for (const auto& kv : mayoresPorCiudad) { // kv: {ciudad, persona}
      const std::string& ciudad = kv.first; // clave = ciudad
      const Persona* persona = kv.second;   // valor = persona con mayor deuda
      if (!persona) continue;               // seguridad ante punteros nulos

      // Mostramos ciudad y datos de la persona con mayor deuda
      std::cout << "- " << ciudad << ": "
                << persona->getNombre() << " "
                << persona->getApellido() << " ("
                << persona->getDeudas() << ")\n";
  }
}



/**
 * Imprime un listado de las personas con mayor deuda por grupo de declaración.
 * 
 * POR QUÉ: Encontrar a la persona con mayor deuda en cada grupo de declaración.
 * CÓMO: Usando un mapa temporal para ir guardando, por grupo, la persona con
 *       mayor deuda encontrada hasta el momento.
 * PARA QUÉ: Listar y mostrar personas con mayor deuda por grupo.
 */
// Busca e imprime la persona con mayor deuda por cada grupo
void buscarMayoresDeudasPorGrupo(const std::vector<Persona>* personas) {
  // Mapa que guarda, para cada grupo (char), un puntero a la Persona con mayor deuda encontrada
  std::unordered_map<char, const Persona*> mayoresPorGrupo;
  mayoresPorGrupo.reserve(personas->size()); // Reservamos (puede ser mucho para pocos grupos, ajustar si hace falta)

  // Recorremos todas las personas y mantenemos la de mayor deuda por grupo
  for (const auto& p : *personas) {
      char grupo = p.getGrupoDeclaracion(); // Obtenemos el grupo (clave del mapa)

      // Buscamos si ya hay alguien registrado para este grupo
      auto it = mayoresPorGrupo.find(grupo);

      // Si el grupo aún no está o esta persona tiene más deuda que la registrada, actualizamos
      if (it == mayoresPorGrupo.end() || p.getDeudas() > it->second->getDeudas()) {
          mayoresPorGrupo[grupo] = &p;
      }
  }

  // Encabezado de salida
  std::cout << "\n=== Personas con mayor deuda por grupo ===\n";

  // Configuramos formato de salida una sola vez:
  // - std::fixed: evita notación científica
  // - std::setprecision(0): sin decimales, valor entero
  std::cout << std::fixed << std::setprecision(0);

  // Recorremos el mapa e imprimimos los resultados
  for (const auto& kv : mayoresPorGrupo) { // kv es un par {grupo, persona*}
      char grupo = kv.first;               // Clave: grupo
      const Persona* persona = kv.second;  // Valor: puntero a la persona con mayor deuda en ese grupo
      if (!persona) continue;              // Seguridad ante posibles nulos

      // Imprimimos grupo y datos de la persona con mayor deuda
      std::cout << "- " << grupo << ": "
                << persona->getNombre() << " "
                << persona->getApellido() << " ("
                << persona->getDeudas() << ")\n";
  }
}



