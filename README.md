# Project_Anger_Flanger 🎛️

Este proyecto ofrece una implementación básica de un **efecto flanger** en **C++**, diseñada como base para integración en proyectos de procesamiento de audio.

---

## 🧩 Contenido actual

- `flanger.cpp` — Código principal con lógica del flanger:
  - Lectura y escritura de archivos WAV (usando librerías estándar).
  - Aplicación de **delay modulada** para generar el efecto flanger.
- `flanger.h` — Declaraciones de funciones y estructuras usadas en `flanger.cpp`.
- `Makefile` — Script de compilación en entornos Unix/Linux.
- `README.md` — Documentación general del proyecto.

---

## ⚙️ Funcionalidades implementadas

- Configuración de parámetros:
  - `depth` (profundidad del efecto)
  - `rate` (velocidad de modulación)
  - `mix` (mezcla entre señal original y procesada)
- Procesamiento por bloques con buffer circular.
- Salida en WAV preservando resolución y formato.

---

## 🚀 Cómo compilar y ejecutar

1. Clona el repositorio:

```bash
git clone https://github.com/SesbastianEP29/Project_Anger_Flanger.git
cd Project_Anger_Flanger
