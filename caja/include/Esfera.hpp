/**
 * @file Esfera.hpp
 * @brief Definición de las clases Cajas y Esfera para la simulación de dinámica molecular.
 *
 * Este archivo contiene las clases responsables de representar las partículas (esferas)
 * y los límites del contenedor (caja) donde ocurre la simulación.
 *
 * @authors
 * - Santiago Suárez
 * - Eric Arciniegas
 */

#include <iostream>
#include <cmath>

/**
 * @class Cajas
 * @brief Representa los límites del contenedor en la simulación.
 *
 * La clase almacena los bordes de la caja (xmin, xmax, ymin, ymax)
 * y las variables necesarias para el cálculo de la presión promedio
 * durante la simulación de partículas.
 */
class Cajas {
private:
    double xmin, xmax, ymin, ymax;  ///< Límites del contenedor.
    double p, n, pn;                ///< Variables de presión acumulada y promedio.

public:
    /**
     * @brief Devuelve el límite mínimo en X.
     */
    double Getxmin() const { return xmin; }

    /**
     * @brief Devuelve el límite máximo en X.
     */
    double Getxmax() const { return xmax; }

    /**
     * @brief Devuelve el límite mínimo en Y.
     */
    double Getymin() const { return xmin; }

    /**
     * @brief Devuelve el límite máximo en Y.
     */
    double Getymax() const { return xmax; }

    /**
     * @brief Devuelve la presión promedio actual.
     */
    double Getp() const { return p; }

    /**
     * @brief Inicializa los límites de la caja.
     * @param x1 Límite mínimo en X.
     * @param x2 Límite máximo en X.
     * @param y1 Límite mínimo en Y.
     * @param y2 Límite máximo en Y.
     */
    void inicio(double x1, double x2, double y1, double y2) {
        xmin = x1;
        xmax = x2;
        ymin = y1;
        ymax = y2;
    }

    /**
     * @brief Reinicia los acumuladores de presión.
     */
    void actualizarPresion() {
        p = 0;
        pn = 0;
        n = 0;
    }

    /**
     * @brief Acumula contribuciones a la presión.
     * @param mv2 Producto masa × velocidad².
     */
    void calcularPresionN(double mv2) {
        pn += mv2 / 3;
        n += 1;
    }

    /**
     * @brief Calcula la presión promedio actual.
     */
    void calcularPresion() { p = pn / n; }
};

/**
 * @class Esfera
 * @brief Representa una partícula (esfera) dentro de la simulación.
 *
 * La clase gestiona la posición, velocidad, radio y dinámica de cada
 * esfera, incluyendo colisiones entre partículas y rebotes con las paredes.
 */
class Esfera {
private:
    double m;      ///< Masa de la esfera.
    double x, y;   ///< Posición de la esfera.
    double vx, vy; ///< Componentes de la velocidad.
    double theta;  ///< Ángulo de la velocidad respecto al eje X.
    double R;      ///< Radio de la esfera.

public:
    /**
     * @brief Devuelve la posición X.
     */
    double Getx() const { return x; }

    /**
     * @brief Devuelve la posición Y.
     */
    double Gety() const { return y; }

    /**
     * @brief Devuelve la magnitud de la velocidad.
     */
    double Getv() const { return std::sqrt(vx * vx + vy * vy); }

    /**
     * @brief Inicializa las propiedades de la esfera.
     * @param m0 Masa.
     * @param x0 Posición en X.
     * @param y0 Posición en Y.
     * @param vx0 Velocidad en X.
     * @param vy0 Velocidad en Y.
     * @param R0 Radio.
     */
    void inicio(double m0, double x0, double y0, double vx0, double vy0, double R0) {
        m = m0;
        x = x0;
        y = y0;
        vx = vx0;
        vy = vy0;
        R = R0;
        actualizarAngulo();
    }

    /**
     * @brief Actualiza la posición de la partícula según el tiempo dado.
     * @param t Paso temporal.
     */
    void muevase(double t) {
        x += vx * t;
        y += vy * t;
    }

    /**
     * @brief Actualiza el ángulo de la velocidad.
     */
    void actualizarAngulo() { theta = std::atan2(vy, vx); }

    /**
     * @brief Detecta y maneja rebotes contra las paredes de la caja.
     * @param caja Objeto Cajas que define los límites.
     */
    void rebotePared(Cajas &caja) {
        if ((x - caja.Getxmin()) <= R || (caja.Getxmax() - x) <= R) {
            vx = -vx;
            actualizarAngulo();
            caja.calcularPresionN(m * (vx * vx + vy * vy));
        }
        if ((y - caja.Getymin()) <= R || (caja.Getymax() - y) <= R) {
            vy = -vy;
            actualizarAngulo();
            caja.calcularPresionN(m * (vx * vx + vy * vy));
        }
    }

    /**
     * @brief Detecta y resuelve colisiones elásticas con otra esfera.
     * @param otra Referencia a otra Esfera.
     */
    void colision(Esfera &otra) {
        double dx = otra.x - x;
        double dy = otra.y - y;
        double dist2 = dx * dx + dy * dy;
        double Rsum = R + otra.R;

        if (dist2 <= Rsum * Rsum) {
            double dist = std::sqrt(dist2);
            if (dist == 0) return;

            double nx = dx / dist;
            double ny = dy / dist;

            double vn1 = vx * nx + vy * ny;
            double vn2 = otra.vx * nx + otra.vy * ny;

            double vn1_new = vn2;
            double vn2_new = vn1;

            vx += (vn1_new - vn1) * nx;
            vy += (vn1_new - vn1) * ny;
            otra.vx += (vn2_new - vn2) * nx;
            otra.vy += (vn2_new - vn2) * ny;

            actualizarAngulo();
            otra.actualizarAngulo();
        }
    }
};
