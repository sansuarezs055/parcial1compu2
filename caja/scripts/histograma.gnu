# Script para generar un histograma de velocidades (columna 3)

reset
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output "C:/Users/PC 1/Documents/trabajos/Semestre 6/computacional 1/Caja/results/histograma_velocidades.png"

# Título y etiquetas
set title "Histograma de velocidades"
set xlabel "Velocidad"
set ylabel "Frecuencia"

# Estilo del histograma
set style fill solid 0.6 border -1
set boxwidth 0.9 relative

# Número de bins (puedes ajustarlo según tus datos)
n_bins = 100

# Calcular límites del eje x automáticamente
stats "C:/Users/PC 1/Documents/trabajos/Semestre 6/computacional 1/Caja/datos.dat" using 3 nooutput
min_v = STATS_min
max_v = STATS_max
width = (max_v - min_v) / n_bins

# Función para agrupar valores en bins
bin(x,width) = width * floor(x/width) + width/2.0

# Plot del histograma
plot "C:/Users/PC 1/Documents/trabajos/Semestre 6/computacional 1/Caja/datos.dat" using (bin($3,width)):(1.0) smooth freq with boxes lc rgb "#4682b4" title "Velocidades"
