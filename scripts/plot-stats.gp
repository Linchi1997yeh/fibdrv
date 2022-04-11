reset
set xlabel 'F(n)'
set ylabel 'time (ns)'
set title 'Fibonacci runtime'
set term png enhanced font 'Verdana,10'
set output 'plot.png'
set grid
plot [0:100][0:150] \
'plot' using 1:2 with linespoints linewidth 2 title "Fast Doubling",\
'' using 1:3 with linespoints linewidth 2 title "Iterative", \
'' using 1:4 with linespoints linewidth 2 title "Time difference"
