/**
 * @file IntegradorRK4.h
 * @brief Método Runge-Kutta 4 para ecuaciones de segundo orden (oscilador de Duffing acoplado).
 * @authors
 *   - Eric Jesús Arciniegas Barreto
 *   - Santiago Suárez Sánchez
 * @date 2025-10-28
 * @version 1.0
 */

#ifndef INTEGRADOR_RK4_H
#define INTEGRADOR_RK4_H

#include "OsciladorDuffing.h"
#include <cmath>
#include <iostream>

/**
 * @class IntegradorRK4
 * @brief Clase que implementa el método de integración Runge-Kutta 4 (RK4).
 */
class IntegradorRK4 {
 public:
  /**
   * @brief Integra las ecuaciones de movimiento del oscilador de Duffing acoplado.
   * @param osc Referencia al objeto OsciladorDuffing que contiene el sistema a integrar.
   */
  static void integrar(OsciladorDuffing& osc) {
    auto& t = osc.getTiempo();
    auto& x1 = osc.getX1();
    auto& x2 = osc.getX2();
    auto& y1 = osc.getY1();
    auto& y2 = osc.getY2();

    std::vector<double> k1(4), k2(4), l1(4), l2(4);

    for (size_t i = 0; i + 1 < t.size(); i++) {
      double h = t[i + 1] - t[i];

      // --- k's ---
      k1[0] = h * y1[i];
      k2[0] = h * y2[i];
      k1[1] = h * (y1[i] + k1[0] / 2);
      k2[1] = h * (y2[i] + k2[0] / 2);
      k1[2] = h * (y1[i] + k1[1] / 2);
      k2[2] = h * (y2[i] + k2[1] / 2);
      k1[3] = h * (y1[i] + k1[2]);
      k2[3] = h * (y2[i] + k2[2]);

      // --- l's ---
      l1[0] = h * osc.f1(t[i], x1[i], x2[i], y1[i], y2[i]);
      l2[0] = h * osc.f2(t[i], x1[i], x2[i], y1[i], y2[i]);

      l1[1] = h * osc.f1(t[i] + h / 2, x1[i] + k1[0] / 2, x2[i] + k2[0] / 2,
                         y1[i] + l1[0] / 2, y2[i] + l2[0] / 2);
      l2[1] = h * osc.f2(t[i] + h / 2, x1[i] + k1[0] / 2, x2[i] + k2[0] / 2,
                         y1[i] + l1[0] / 2, y2[i] + l2[0] / 2);

      l1[2] = h * osc.f1(t[i] + h / 2, x1[i] + k1[1] / 2, x2[i] + k2[1] / 2,
                         y1[i] + l1[1] / 2, y2[i] + l2[1] / 2);
      l2[2] = h * osc.f2(t[i] + h / 2, x1[i] + k1[1] / 2, x2[i] + k2[1] / 2,
                         y1[i] + l1[1] / 2, y2[i] + l2[1] / 2);

      l1[3] = h * osc.f1(t[i] + h, x1[i] + k1[2], x2[i] + k2[2],
                         y1[i] + l1[2], y2[i] + l2[2]);
      l2[3] = h * osc.f2(t[i] + h, x1[i] + k1[2], x2[i] + k2[2],
                         y1[i] + l1[2], y2[i] + l2[2]);

      // --- Actualización ---
      x1.push_back(x1[i] + (k1[0] + 2 * k1[1] + 2 * k1[2] + k1[3]) / 6);
      x2.push_back(x2[i] + (k2[0] + 2 * k2[1] + 2 * k2[2] + k2[3]) / 6);
      y1.push_back(y1[i] + (l1[0] + 2 * l1[1] + 2 * l1[2] + l1[3]) / 6);
      y2.push_back(y2[i] + (l2[0] + 2 * l2[1] + 2 * l2[2] + l2[3]) / 6);

      // --- Comprobación numérica ---
      if (!std::isfinite(x1.back()) || !std::isfinite(y1.back()) ||
          !std::isfinite(x2.back()) || !std::isfinite(y2.back())) {
        std::cerr << "NaN detectado en paso i=" << i << "\n";
        break;
      }
    }
  }
};

#endif  // INTEGRADOR_RK4_H
