# exporta o plot gerado para um png
# especifica 'grid' no plot
# para dois estimadores, usar: for[i=3:3]; para um estimador, usar: for[i=3:2]

set terminal png
set output 'simuladores.png'
set datafile missing '-'
set style data linespoints
set grid
plot 'simuladores.dat' using 2:xtic(1) title columnheader(2), for [i=3:3] '' using i title columnheader(i)