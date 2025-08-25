# 📊 Manejo de Grandes Volúmenes de Datos en Linux con C/C++

**Proyecto:** Comparativa de rendimiento en C++ — **Clases vs. Estructuras · Valor vs. Punteros**  

Este proyecto estudia cómo distintas formas de modelar y acceder a los datos en **C++14** afectan el rendimiento y el consumo de memoria al trabajar con grandes volúmenes de información (10 millones de registros de personas).  

---

## 📂 Variantes implementadas  

Se desarrollaron cuatro implementaciones equivalentes que solo difieren en:  
1. **Modelo de datos** → `class` (encapsulación, constructores, métodos) vs `struct` (almacenador plano con campos públicos).  
2. **Forma de acceso** → **por valor** (copia de los datos) vs **por punteros** (referencias en memoria).  

| Carpeta                  | Modelo            | Paso / Acceso         |
|---------------------------|------------------|-----------------------|
| `Clases_valor`           | `class Persona`   | Por **valor / refs const** |
| `Clases_apuntador`       | `class Persona`   | Por **punteros**      |
| `Estructuras_valor`      | `struct Persona`  | Por **valor / refs const** |
| `Estructuras_apuntador`  | `struct Persona`  | Por **punteros**      |

---

## 🎯 Objetivo del estudio  

- Evaluar cómo influyen estas decisiones de diseño en:  
  - Tiempo de ejecución.  
  - Consumo de memoria.  
- Medir estas métricas en distintas operaciones:  
  - Generación masiva de personas.  
  - Búsquedas por ID.  
  - Listado y conteo por grupo.  
  - Consultas específicas (por ciudad, mayor patrimonio, mayor deuda, persona más longeva).  
- Identificar las ventajas y desventajas de cada enfoque.  

---

## 🔍 Hallazgos clave  

- **Acceso por punteros** → evita copias innecesarias, mantiene la memoria más estable y es más eficiente en búsquedas puntuales.  
- **Acceso por valor** → penaliza en memoria y tiempo al duplicar objetos, pero se beneficia de la **localidad en memoria** para recorridos largos.  
- **Clases** → suelen mostrar un desempeño más consistente debido a las optimizaciones del compilador y el uso de constructores.  
- **Estructuras** → más livianas en diseño, pero con diferencias menos marcadas cuando se comparan en operaciones de gran escala.  

---

## 🎥 Evidencias y análisis  

Toda la evidencia del proyecto (video explicativo, métricas completas y análisis detallado) se encuentra disponible en el siguiente enlace:  

🔗 [Google Drive – Evidencias y análisis](https://drive.google.com/drive/folders/1KFjlo0IqYnI-6Lye1jmXSC16zY92x3eJ?usp=sharing)  

---

## ⚙️ Requisitos de ejecución  

- **Sistema:** Linux / macOS (o WSL en Windows).  
- **Compilador:** `g++` con soporte **C++14`.  
- **Herramienta de construcción:** `make`.  

### ▶️ Compilación y ejecución  

```bash
make
./programa
