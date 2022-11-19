# unset key 
set xlabel 'Time (days)'
set ylabel 'Populace'
set grid
set term png
set out './../data/sir.png'
set title 'SIR population'
plot "./../data/data.txt" u 1:2 w l t 'Susceptible', "./../data/data.txt" u 1:3 w l t 'Infected', "./../data/data.txt" u 1:4 w l t 'Recovered'