Simulación de Dinámica Molecular

Este proyecto implementa una simulación de dinámica molecular en C++, organizada según la Google C++ Style Guide. El código calcula y analiza el comportamiento dinámico de partículas en interacción, permitiendo generar datos, gráficas y animaciones.

Estructura del proyecto

Caja/
├── include/ → Cabeceras y librerías propias (.hpp)
├── src/ → Código fuente principal (.cpp)
├── scripts/ → Scripts de Gnuplot
├── results/ → Gráficas, GIFs, listas de datos, etc.
├── documents/ → Informe físico en LaTeX y diagrama de flujo
├── Makefile → Compilación y ejecución de la simulación
├── documents/makedoc → Compilación del informe en LaTeX
└── README.md → Este archivo

Compilación

Desde la raíz del proyecto ejecutar:

make

Esto compila todos los archivos .cpp del directorio src/ y genera el ejecutable en bin/simulacion.

Ejecución

Ejecutar la simulación directamente con:

make run

Limpieza

Para eliminar los archivos objeto y binarios:

make clean

Generar informe en LaTeX

Dentro de documents/ hay un archivo makedoc que automatiza la compilación del informe.
Puedes generarlo directamente desde la raíz del proyecto con:

make docs

Esto creará documents/informe.pdf (a partir de documents/informe.tex).

Generación de gráficas con Gnuplot

Los scripts de Gnuplot están en el directorio scripts/.
Ejemplo para reproducir un histograma de velocidades:

gnuplot scripts/histograma.gnu

Los resultados (gráficas o GIFs) se almacenan automáticamente en results/.

Documentación con Doxygen

Para generar documentación automática del código fuente (a partir de los comentarios tipo Doxygen), usar:

doxygen Doxyfile

Esto generará una documentación navegable en docs/html/index.html.

Análisis físico sugerido (para documents/informe.tex)

El documento debe incluir las siguientes secciones:

Objetivos: explicar el propósito de la simulación.

Modelo físico y método numérico: detallar la integración (por ejemplo, Verlet o Leapfrog).

Validación: mostrar conservación de energía, convergencia o comparación con soluciones analíticas.

Resultados: incluir tablas y gráficas de results/.

Discusión: interpretación física de los resultados.

Conclusiones: resumen de hallazgos principales.

Dependencias

Compilador C++17 o superior (g++, clang++, etc.)

Gnuplot (para gráficas)

LaTeX (para el informe)

Doxygen (para documentación del código)

Ejemplo de flujo de trabajo

Compilar la simulación: make

Ejecutar el programa: make run

Generar las gráficas con Gnuplot: gnuplot scripts/histograma.gnu

Compilar el informe en LaTeX: make docs

(Opcional) Crear documentación del código: doxygen Doxyfile

Licencia

Este proyecto es de uso académico y libre para modificación con fines de aprendizaje o investigación.

Autor: [Tu nombre aquí]
Última actualización: Octubre 2025