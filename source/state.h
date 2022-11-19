#include <iostream>
#include "./diffusive_sir.h"

void show_state(d_sir & Dsir, int N){
    double * position = Dsir.Position();
    int * state = Dsir.State();

    for(int ii = 0; ii < N; ii++){
        if(state[ii] == 0)
            std::cout << position[ii] << "\t" << position[ii+N];
        else if(state[ii] == 0)
            std::cout << "\t" << position[ii] << "\t" << position[ii+N];
        else
            std::cout << "\t" << position[ii] << "\t" << position[ii+N];
        std::cout << std::endl;
    }

}