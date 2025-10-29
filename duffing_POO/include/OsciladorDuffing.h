/**
 * @file OsciladorDuffing.h
 * @brief Definición de la clase OsciladorDuffing que modela un sistema acoplado de Duffing.
 * @details
 * Contiene los parámetros del sistema, las ecuaciones de movimiento (f1, f2),
 * la inicialización de condiciones y el guardado de resultados.
 *
 * @authors
 *   - Eric Jesús Arciniegas Barreto
 *   - Santiago Suárez Sánchez
 * @date 2025-10-28
 * @version 1.0
 */

#ifndef OSCILADOR_DUFFING_H
#define OSCILADOR_DUFFING_H

#include <cmath>
#include <fstream>
#include <string>
#include <vector>

/**
 * @class OsciladorDuffing
 * @brief Representa un sistema de dos osciladores de Duffing acoplados.
 */
class OsciladorDuffing {
 private:
  // --- Parámetros del sistema ---
  double alfa;    ///< Término lineal restaurador
  double beta;    ///< No linealidad cúbica
  double gamma;   ///< Amplitud de la fuerza externa
  double omega;   ///< Frecuencia de la fuerza externa
  double k;       ///< Constante de acoplamiento
  std::vector<double> m;      ///< Masas de los osciladores
  std::vector<double> delta;  ///< Coeficiente de fricción

  // --- Variables del estado ---
  std::vector<double> t;   ///< Tiempo
  std::vector<double> x1;  ///< Posición del oscilador 1
  std::vector<double> x2;  ///< Posición del oscilador 2
  std::vector<double> y1;  ///< Velocidad del oscilador 1
  std::vector<double> y2;  ///< Velocidad del oscilador 2

 public:
  /**
   * @brief Constructor de la clase OsciladorDuffing.
   * @param alfa_ Parámetro alfa.
   * @param beta_ Parámetro beta.
   * @param gamma_ Amplitud de la fuerza externa.
   * @param omega_ Frecuencia angular.
   * @param k_ Constante de acoplamiento.
   * @param m_ Vector de masas.
   * @param delta_ Vector de coeficientes de fricción.
   */
  OsciladorDuffing(double alfa_, double beta_, double gamma_, double omega_,
                   double k_, const std::vector<double>& m_,
                   const std::vector<double>& delta_)
      : alfa(alfa_),
        beta(beta_),
        gamma(gamma_),
        omega(omega_),
        k(k_),
        m(m_),
        delta(delta_) {}

  /**
   * @brief Inicializa las condiciones iniciales del sistema.
   * @param t0 Tiempo inicial.
   * @param tf Tiempo final.
   * @param dt Paso temporal.
   * @param x1_0 Posición inicial del oscilador 1.
   * @param x2_0 Posición inicial del oscilador 2.
   * @param y1_0 Velocidad inicial del oscilador 1.
   * @param y2_0 Velocidad inicial del oscilador 2.
   */
  void inicializar(double t0, double tf, double dt, double x1_0, double x2_0,
                   double y1_0, double y2_0) {
    for (double ti = t0; ti <= tf; ti += dt) t.push_back(ti);
    x1 = {x1_0};
    x2 = {x2_0};
    y1 = {y1_0};
    y2 = {y2_0};
  }

  /**
   * @brief Ecuación diferencial para el oscilador 1.
   */
  double f1(double t_, double x1_, double x2_, double y1_, double y2_) const {
    return -(y1_ * delta[0] + m[0] * alfa * x1_ + beta * std::pow(x1_, 3) +
             k * (x1_ - x2_) + gamma * std::cos(omega * t_)) /
           m[0];
  }

  /**
   * @brief Ecuación diferencial para el oscilador 2.
   */
  double f2(double t_, double x1_, double x2_, double y1_, double y2_) const {
    return -(y2_ * delta[1] + m[1] * alfa * x2_ + beta * std::pow(x2_, 3) +
             k * (x2_ - x1_)) /
           m[1];
  }

  // --- Getters ---
  std::vector<double>& getTiempo() { return t; }
  std::vector<double>& getX1() { return x1; }
  std::vector<double>& getX2() { return x2; }
  std::vector<double>& getY1() { return y1; }
  std::vector<double>& getY2() { return y2; }

  /**
   * @brief Guarda los resultados de la simulación en un archivo.
   * @param nombre Nombre base del archivo (sin extensión).
   */
  void guardarDatos(const std::string& nombre) const {
    std::ofstream file("results/" + nombre + ".dat");
    file << "# alfa=" << alfa << " beta=" << beta << " gamma=" << gamma
         << " omega=" << omega << " k=" << k << "\n";
    for (size_t i = 0; i < t.size() && i < x1.size(); ++i) {
      file << t[i] << " " << x1[i] << " " << x2[i] << " " << y1[i] << " "
           << y2[i] << "\n";
    }
    file.close();
  }
};

#endif  // OSCILADOR_DUFFING_H
