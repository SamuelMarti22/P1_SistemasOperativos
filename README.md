# Manejo de Grandes Volúmenes de Datos en Linux con C/C++
Proyecto: Comparativa C++ — Clases vs Estructuras · Valor vs Punteros

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

## Analisis

| Variante               |    N | Generación (ms) | Memoria gen (KB) | Buscar ID (ms) | Listar grupo A (ms) |
|------------------------|-----:|----------------:|-----------------:|---------------:|--------------------:|
| Clases_valor           | 10M |        2537.75         |       1970776           |        9555.62        |         11272.36            |
| Clases_apuntador    | 10M |        3343.28         |       1970816           |        6944.74        |            43483.47        |
| Estructuras_valor      | 10M |       16455.12          |       2018720           |       13213.49         |       32580.23              |
| Estructuras_apuntador | 10M |   35926.4              |    2018760              |      1099.47          |       52418.86              |


## Drive
En el siguiente enlace encontrará el video explicativo, la evidencia de las metricas y el analisis del mismo
https://drive.google.com/drive/folders/1KFjlo0IqYnI-6Lye1jmXSC16zY92x3eJ?usp=sharing

---
## Requisitos
- Linux/macOS (o WSL) con `g++ (C++14)` y `make`.

---


