N = 100
Inf = 0.011
den = 0.012
D = 100
dt = 0.01
r_t = 14.0
i_d = 2.0
i_p = 0.2

path_data = ./../data/data.txt

sir_plot: sir.png

%.x: %.cpp
	g++ -g $< -o $@

$(path_data): main.x
	./$< $(N) $(Inf) $(den) $(D) $(dt) $(r_t) $(i_d) $(i_p) 0 > ./../data/$@

sir.png: plot.gp $(path_data)
	gnuplot $<

gif: main.x
	./$< $(N) $(Inf) $(den) $(D) $(dt) $(r_t) $(i_d) $(i_p) 1 | gnuplot 

.PHONY: clean
clean:
	rm *.x ./../data/*.txt *.out