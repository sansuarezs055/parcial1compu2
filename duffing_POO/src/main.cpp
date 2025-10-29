/**
 * @file main.cpp
 * @brief Programa principal: simulación del oscilador de Duffing acoplado.
 * @details
 * Implementa el flujo principal del programa, creando el directorio de resultados,
 * configurando los parámetros físicos, integrando el sistema con RK4 y guardando
 * los datos resultantes.
 *
 * @authors
 *   - Eric Jesús Arciniegas Barreto
 *   - Santiago Suárez Sánchez
 *
 * @date 2025-10-28
 */

#include "OsciladorDuffing.h"
#include "IntegradorRK4.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <direct.h>   // Para _mkdir() en Windows
#else
#include <sys/stat.h> // Para mkdir() en Linux
#endif

/// Crea una carpeta en el sistema operativo sin usar <filesystem>.
/// @param ruta Ruta del directorio a crear.
void CrearDirectorio(const std::string& ruta) {
#ifdef _WIN32
  _mkdir(ruta.c_str());
#else
  mkdir(ruta.c_str(), 0777);
#endif
}

/// Función principal del programa.
int main() {
  CrearDirectorio("results");

  // --- Parámetros del sistema ---
  const double kAlpha = -1.0;        ///< Término lineal restaurador
  const double kBeta = 3.0;          ///< No linealidad cúbica
  const double kGamma = 1.5;         ///< Amplitud de la fuerza externa
  const double kOmega = 0.6;         ///< Frecuencia de la fuerza externa
  const double kCoupling = 0.0;      ///< Constante de acoplamiento
  const std::vector<double> kMass = {1.0, 1.0};     ///< Masas de los osciladores
  const std::vector<double> kDamping = {0.05, 0.05}; ///< Coeficiente de fricción

  // --- Inicialización del sistema ---
  OsciladorDuffing duffing(kAlpha, kBeta, kGamma, kOmega, kCoupling, kMass, kDamping);

  // t0, tf, dt, x1_0, x2_0, v1_0, v2_0
duffing.inicializar(0.0, 70.0, 0.01, -1.0 + 0.0001, 1.0 + 0.0001, 0.0, 0.0);

  // --- Integración numérica ---
IntegradorRK4::integrar(duffing);
  // --- Guardar datos ---
duffing.guardarDatos("datos");


  std::cout << "Simulación completada. Datos en results/datos.dat\n";
  std::cout << "Ejecuta: gnuplot scripts/graficar.gnu\n";
  return 0;
}
