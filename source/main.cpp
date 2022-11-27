#include <iostream>
#include "./diffusive_sir.h"
#include "./anima.h"

int main(int argc, char **argv){
    // simulation's time variables
    double const dt = std::atof(argv[5]); 
    double t=0, t_max = 25;
    
    // system-especific varibles
    int const N = std::atoi(argv[1]);
    double const infected = std::atof(argv[2]);
    double const density = std::atof(argv[3]);
    double const D = std::atof(argv[4]);
    double const recovery_time = std::atof(argv[6]); 
    double const infected_distance = std::atof(argv[7]);
    double const infected_prob = std::atof(argv[8]);
    int const An = std::atoi(argv[9]);
    
    // sir counter
    int s, i, r;

    d_sir Dsir(N, infected, density, D, dt, recovery_time, infected_distance, infected_prob);
    crono Cro(Dsir);
    s = Dsir.s(); i = Dsir.i(); r = Dsir.r();

    if(An == 0)
        plot_sir(Dsir, Cro, s, i, r, t_max, dt);
    if(An == 1)
        plot_evolution(N, density, Dsir, Cro, s, i, r, t_max, dt);

    return 0;
}