#include <iostream>
#include "./diffusive_sir.h"
#include "./state.h"

int main(int argc, char **argv){
    // simulation's time variables
    double const dt = std::atof(argv[5]); 
    double t=0, t_max = 90;
    
    // system-especific varibles
    int const N = std::atoi(argv[1]);
    double const infected = std::atof(argv[2]);
    double const density = std::atof(argv[3]);
    double const D = std::atof(argv[4]);
    double const recovery_time = std::atof(argv[6]); 
    double const infected_distance = std::atof(argv[7]);
    double const infected_prob = std::atof(argv[8]);
    
    // sir counter
    int s, i, r;

    d_sir Dsir(N, infected, density, D, dt, recovery_time, infected_distance, infected_prob);
    crono Cro(Dsir);
    s = Dsir.s(); i = Dsir.i(); r = Dsir.r();

    while(t < t_max){
        std::cout << t << "\t" << s << "\t" << i << "\t" << r << "\n";
        Dsir.get_survey(s, i, r);
        Cro.update(Dsir);
        Cro.end(Dsir);
        Dsir.move_p();
        t += dt;
    }

    return 0;
}