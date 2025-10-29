/**
 * @file main.cpp
 * @brief Programa principal del simulador de dinámica molecular de esferas en una caja 2D.
 *
 * Este código inicializa un conjunto de partículas (esferas) dentro de una caja
 * y simula su movimiento, colisiones y rebotes con las paredes. También genera
 * dos animaciones con Gnuplot: una de las trayectorias espaciales y otra del
 * histograma de velocidades.
 *
 * @authors
 * - Santiago Suárez
 * - Eric Arciniegas
 *
 * @date Octubre 2025
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>
#include "Esfera.hpp"   // Asumo que guardaste la clase en este archivo

using namespace std;

/**
 * @brief Función principal del simulador.
 *
 * El programa solicita parámetros iniciales (dimensión de la caja, número de
 * esferas, velocidad máxima, radio) y realiza la simulación del sistema.
 * Utiliza Gnuplot para graficar y crear animaciones de la evolución temporal.
 *
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {
    srand(time(nullptr));  // Semilla para números aleatorios

    cout << "=== Bienvenido al simulador de particulas ===" << endl;

    // --- Definir la caja ---
    double largo;
    cout << "Ingrese el largo del lado de la caja (positivo): ";
    cin >> largo;

    double half = largo / 2.0;
    Cajas caja;
    caja.inicio(-half, half, -half, half); // xmin, xmax, ymin, ymax

    // --- Numero de esferas ---
    int n;
    cout << "Ingrese el numero de esferas: ";
    cin >> n;

    // --- Calcular R ---
    int malla = static_cast<int>(ceil(sqrt(n)));

    // --- Velocidad maxima ---
    double vmax;
    cout << "Ingrese la velocidad maxima: ";
    cin >> vmax;

    // --- Radio ---
    double R;
    do {
        cout << "Ingrese el radio (Sugerido: " << 0.9 * largo / (2.0 * malla) << "): ";
        cin >> R;
        if (R <= 0 || R >= largo / (2.0 * malla)) {
            cout << "Valor fuera de rango. Intenta de nuevo.\n";
        }
    } while (R <= 0 || R >= largo / (2.0 * malla));

    // --- Crear array de esferas ---
    vector<Esfera> esferas(n);

    // --- Inicialización ---
    int idx = 0;
    double m0 = 1;
    for (int i = 0; i < malla && idx < n; i++) {
        for (int j = 0; j < malla && idx < n; j++) {
            // Posición en malla centrada
            double x0 = -half + (i + 0.5) * (largo / malla);
            double y0 = -half + (j + 0.5) * (largo / malla);

            // Generar velocidad aleatoria
            double ang = (2.0 * 3.14159265358979323846 * rand()) / RAND_MAX; // ángulo uniforme [0,2π)
            double v = (vmax * rand()) / RAND_MAX;         // magnitud aleatoria [0,vmax]
            double vx0 = v * cos(ang);
            double vy0 = v * sin(ang);

            // Inicializar esfera
            esferas[idx].inicio(m0, x0, y0, vx0, vy0, R);
            idx++;
        }
    }

    // --- Confirmación ---
    cout << "\nSe crearon " << n << " esferas dentro de la caja de lado " << largo << "." << endl;
    cout << "Radio asignado: " << R << endl;
    cout << "Velocidad maxima: " << vmax << endl;

    // --- Parámetros de simulación ---
    double dt = 0.01;  // paso temporal
    int pasos = 300;   // número de frames

    // --- Gnuplot ---
    FILE *gnuplot = popen("gnuplot -persist", "w");

    // ---- Primera parte: configuraciones iniciales ----
    fprintf(gnuplot, "set terminal gif animate delay 10 size 600,400\n");
    fprintf(gnuplot, "set output 'results/animacion.gif'\n");
    fprintf(gnuplot, "set xrange [-%f:%f]\n", largo/2, largo/2);
    fprintf(gnuplot, "set yrange [-%f:%f]\n", largo/2, largo/2);
    fflush(gnuplot);

    caja.actualizarPresion();

    // --- Abrir archivo de presiones ---
std::ofstream archivo_presion("results/presion.dat");
if (!archivo_presion.is_open()) {
    std::cerr << "No se pudo abrir results/presion.dat para escritura.\n";
    return 1;
}

// --- Bucle de simulación ---
for (int step = 0; step < pasos; step++) {

    // --- Calcular energía total ---
    double energia_total = 0.0;
    for (int i = 0; i < n; i++) {
        energia_total += 0.5 * m0 * esferas[i].Getv() * esferas[i].Getv();
    }

    // --- Guardar posiciones  ---
    std::ofstream archivo("results/datos.dat");
    for (int k = 0; k < n; k++) {
        archivo << esferas[k].Getx() << "\t"
                << esferas[k].Gety() << "\t"
                << esferas[k].Getv() << "\n";
    }
    archivo.close();

    // --- Gnuplot animación  ---
    fprintf(gnuplot, "set title sprintf('t = %.2f s   P = %.4f (Pa·m³)   E = %.4f J')\n", 
            step * dt, caja.Getp(), energia_total);
    fprintf(gnuplot, "plot '-' using 1:2 with points pt 7 ps %f notitle \n", 2*R/(0.9 * largo / (2.0 * malla)));
    caja.actualizarPresion();
    for (int k = 0; k < n; k++) {
        fprintf(gnuplot, "%f\t%f\n", esferas[k].Getx(), esferas[k].Gety());
    }
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);

    // --- Colisiones y rebotes ---
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            esferas[i].colision(esferas[j]);
        }
        esferas[i].rebotePared(caja);
        esferas[i].muevase(dt);
    }

    // --- Calcular presión promedio ---
    caja.calcularPresion();

    // --- Guardar presión en archivo ---
     archivo_presion << step*dt << "\t" << caja.Getp() << "\n";
}

// --- Cerrar archivo de presiones ---
archivo_presion.close();


    fprintf(gnuplot, "unset output \n");
    fflush(gnuplot);
    pclose(gnuplot);

   // === Segunda animación: histograma de velocidades ===
FILE *gnuplot2 = popen("gnuplot -persist", "w");

fprintf(gnuplot2, "reset\n");
fprintf(gnuplot2, "set encoding utf8\n");
fprintf(gnuplot2, "set terminal gif animate delay 10 size 800,600 enhanced font 'Arial,12'\n");
fprintf(gnuplot2, "set output 'results/histograma_velocidades.gif'\n");
fprintf(gnuplot2, "set xlabel 'Velocidad'\n");
fprintf(gnuplot2, "set ylabel 'Frecuencia'\n");
fprintf(gnuplot2, "set style fill solid 0.7 border -1\n");
fprintf(gnuplot2, "set boxwidth 0.9 relative\n");
fprintf(gnuplot2, "set grid ytics\n");
fprintf(gnuplot2, "n_bins = 100\n"); // Más divisiones = histograma más suave
fprintf(gnuplot2, "bin(x,width) = width * floor(x/width) + width/2.0\n");
fprintf(gnuplot2, "set key top right\n");  // leyenda arriba derecha
fflush(gnuplot2);

for (int step = 0; step < pasos; step++) {
    // --- Guardar velocidades ---
    {
        std::ofstream archivo("results/datos.dat");
        for (int k = 0; k < n; k++) {
            double v = esferas[k].Getv();
            if (std::isfinite(v) && v > 0.0)
                archivo << v << "\n";
        }
        archivo.close();
    }

    // --- Verificar si el archivo tiene datos ---
    std::ifstream check("results/datos.dat", std::ios::ate | std::ios::binary);
    if (check.tellg() < 5) continue;
    check.close();

    // --- Enviar comandos a gnuplot ---
    fprintf(gnuplot2, "stats 'results/datos.dat' using 1 nooutput\n");
    fprintf(gnuplot2, "min_v = STATS_min\n");
    fprintf(gnuplot2, "max_v = STATS_max\n");
    fprintf(gnuplot2, "if (max_v - min_v <= 1e-9) max_v = min_v + 1e-9\n");
    fprintf(gnuplot2, "width = (max_v - min_v) / n_bins\n");
    fprintf(gnuplot2, "set xrange [min_v:max_v]\n");
    fprintf(gnuplot2, "set yrange [0:*]\n");

    // Texto dinámico con tiempo y número de partículas
    fprintf(gnuplot2,
            "set label 1 sprintf('t = %.2f s', %f) at graph 0.02, 0.95 front tc rgb '#333333' font ',12'\n",
            step * dt, step * dt);
    fprintf(gnuplot2,
            "set label 2 sprintf('N = %d', %d) at graph 0.02, 0.88 front tc rgb '#333333' font ',12'\n",
            n, n);

    fprintf(gnuplot2,
            "set title sprintf('Distribución de velocidades - paso %d', %d)\n",
            step, step);

    fprintf(gnuplot2,
            "plot 'results/datos.dat' using (bin($1,width)):(1.0) smooth freq "
            "with boxes lc rgb '#1f77b4' title 'Velocidades'\n");

    // limpiar etiquetas para el siguiente frame
    fprintf(gnuplot2, "unset label 1\nunset label 2\n");
    fflush(gnuplot2);
}

fprintf(gnuplot2, "unset output\n");
fflush(gnuplot2);
pclose(gnuplot2);

return 0;
}
