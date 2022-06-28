reset
set xlabel 'F(n)'
set ylabel 'time (ns)'
set title 'Fibonacci runtime no Preallocating'
set term png enhanced font 'Verdana,10'
set output 'plot.png'
set grid
plot [4000:5000][3600000:5700000] \
'plot' using 1:2 with linespoints linewidth 2 title "Fast Doubling",\

#'' using 1:3 with linespoints linewidth 2 title "Fast Doubling", \

