# Create a README.md file with the requested content
readme_content = """# Proyecto: Comparativa C++ — Clases vs Estructuras · Valor vs Punteros

Estudio corto de rendimiento y complejidad sobre operaciones con **Personas** en C++14.  
Se implementan **4 variantes** del mismo programa para comparar **modelo de datos** y **técnica de paso/acceso**:

| Carpeta | Modelo | Paso/Acceso |
|---|---|---|
| `Clases_valor` | `class Persona` (getters) | Por **valor / refs const** |
| `Clases_referencia` | `class Persona` (getters) | Por **punteros** |
| `Estructuras_valor` | `struct Persona` (campos públicos) | Por **valor / refs const** |
| `Estructuras_referencia` | `struct Persona` (campos públicos) | Por **punteros** |

---

## Objetivo
- Medir tiempo y memoria al:
  - Generar **N** personas.
  - **Buscar por ID** (vector ordenado + `lower_bound`).
  - **Listar / contar por grupo** (A/B/C) según los **dos últimos dígitos** del documento.
  - Consultas por ciudad / mayor patrimonio / mayor deuda / persona más longeva.
- Comparar impacto de **clases vs estructuras** y **valor vs punteros**.

## Drive
En el siguiente enlace encontrará el video explicativo, la evidencia de las metricas y el analisis del mismo
https://drive.google.com/drive/folders/1KFjlo0IqYnI-6Lye1jmXSC16zY92x3eJ?usp=sharing
---

## Requisitos
- Linux/macOS (o WSL) con `g++ (C++14)` y `make`.

---


