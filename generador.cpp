#include "generador.h"
#include <algorithm> // std::find_if
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <random>    // std::mt19937, std::uniform_real_distribution
#include <unordered_map>
#include <vector>

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

char grupoRenta(int id) {
  if (id < 40) {
    return 'A';
  }
  if (id > 39 && id < 80) {
    return 'B';
  }
  if (id > 79 && id < 100) {
    return 'C';
  };
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
  std::string nombre =
      esHombre ? nombresMasculinos[rand() % nombresMasculinos.size()]
               : nombresFemeninos[rand() % nombresFemeninos.size()];

  // Construye apellido compuesto (dos apellidos aleatorios)
  std::string apellido = apellidos[rand() % apellidos.size()];
  apellido += " ";
  apellido += apellidos[rand() % apellidos.size()];

  // Genera los demás atributos
  long id = generarID();
  char grupoDeclaracion = grupoRenta(id % 100);

  std::string ciudad = ciudadesColombia[rand() % ciudadesColombia.size()];
  std::string fecha = generarFechaNacimiento();

  // Genera datos financieros realistas
  double ingresos = randomDouble(10000000, 500000000); // 10M a 500M COP
  double patrimonio = randomDouble(0, 2000000000);     // 0 a 2,000M COP
  double deudas =
      randomDouble(0, patrimonio * 0.7); // Deudas hasta el 70% del patrimonio
  bool declarante = (ingresos > 50000000) &&
                    (rand() % 100 > 30); // Probabilidad 70% si ingresos > 50M

  return Persona(nombre, apellido, std::to_string(id), ciudad, fecha, ingresos,
                 patrimonio, deudas, declarante, grupoDeclaracion);
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
const Persona *buscarPorID(const std::vector<Persona> &personas,
                           const std::string &id) {
  // Usa find_if con una lambda para buscar por ID
  auto it = std::find_if(personas.begin(), personas.end(),
                         [&id](const Persona &p) { return p.getId() == id; });

  if (it != personas.end()) {
    return &(*it); // Devuelve puntero a la persona encontrada
  } else {
    return nullptr; // No encontrado
  }
}

// Función para calcular el grupo más grande por ciudad
void calcularGrupoMayorPorCiudad(const std::vector<Persona> &personas) {
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
  for (const Persona &persona : personas) {
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

// Función que calcula el promedio de patrimonio por ciudad
void calcularPromedioPatrimonio(const std::vector<Persona> &personas) {
  double ciudadesPromedios[20] = {0};
  int conteoCiudad[20] = {0};

  // Recorremos a cada persona y sumamos el patrimonio por ciudad
  for (const Persona &persona : personas) {
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
