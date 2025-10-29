set encoding utf8
set terminal q size 1200,600 enhanced font "Arial,12"
set grid
set palette rgbformulae 33,13,10
unset colorbox

#Leer encabezado de parámetros (primera línea que empieza con '#')
#parametros = system("grep '^#' results/datos.dat | head -n1 | cut -c3-")

# Título principal + parámetros debajo
set multiplot layout 1,2 title "Diagramas de fase - Osciladores acoplados\n"

# --- Diagrama de fase del oscilador 1 (x1 vs v1) ---
set xlabel "x1(m)"
set ylabel "v1(m/s)"
plot "results/datos.dat" using 2:4 with lines lc rgb "blue" title "Oscilador 1"

# --- Diagrama de fase del oscilador 2 (x2 vs v2) ---
set xlabel "x2(m)"
set ylabel "v2(m/s)"
plot "results/datos.dat" using 3:5 with lines lc rgb "red" title "Oscilador 2"

# --- x1 vs x2 (correlación de posiciones) ---
#set xlabel "x1(m)"
#set ylabel "x2(m)"
#plot "results/datos.dat" using 2:3 with lines lc rgb "purple" title "x1 vs x2"

# --- y1 vs y2 (correlación de velocidades) ---
#set xlabel "v1(m)"
#set ylabel "v2(m)"
#plot "results/datos.dat" using 4:5 with lines lc rgb "green" title "y1 vs y2"

unset multiplot
pause -1 "Presiona Enter para salir"
