# Script: results/graficar_presion.gnu
# Grafica presión vs tiempo

reset
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'results/presion_vs_t.png'

set title "Evolución de la presión en la caja"
set xlabel "Tiempo [s]"
set ylabel "Presión promedio [Pa·m³]"
set grid

# Graficar los datos (columna 1 = tiempo, columna 2 = presión)
plot 'results/presion.dat' using 1:2 with lines lw 2 lc rgb '#1f77b4' title 'Presión'
