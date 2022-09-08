#include <iostream>
#include "./diffusive_sir.h"

int main(){
    double dt=0.01, t=0, t_max = 14;
    d_sir D(100, 0.011, 0.012);

    while(t <= t_max){
        std::cout << t << "\t";
        D.show();
        D.move_p();
        t += dt;
    }

    return 0;
}