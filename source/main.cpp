#include <iostream>
#include "./diffusive_sir.h"

int main(){
    double dt=0.01, t=0, t_max = 90;
    d_sir D(1000, 0.011, 0.012);
    crono C(D);

    while(t < t_max){
        std::cout << t << "\t";
        D.show();
        C.update(D);
        C.end(D);
        D.move_p();
        t += dt;
    }

    return 0;
}