#ifndef _DIFFUSIVE_H_
#define _DIFFUSIVE_H_

#include <iostream>
#include <cmath>
#include "Random64.h"

class d_sir;
class crono;

Crandom rand64(1);

// %-------------------------------------------------------%
// %------------------% DIFFUSIVE CLASS %------------------%
// %-------------------------------------------------------%

class d_sir {
public:
    d_sir (int Number, double infected, double density);
    ~d_sir ();

    void boot();
    void show();
    void get_survey(int &s, int &i, int &r);
    void sneeze(int ii);
    double distance(int n, int m);
    void move_p();
    // void evolve(double t_max);

    int s(){return S;};
    int i(){return I;};
    int r(){return R;};

    friend class crono;

private:
    int N, Infected; double Density, L;
    double * position;
    int * state;
    int S, I, R;
private:
    double D = 100, dt = 0.01;
    double recovery_time = 14.0, infected_distance = 2.0, infected_prob = 0.2;
};

d_sir::d_sir (int Number, double infected, double density){
    N = Number; Infected = int(N * infected); Density = density;
    L = sqrt(N / Density);
    S = 0; I = 0; R = 0;
    position = new double [2*N];
    state = new int [N];
    for(int ii = 0; ii < 2*N; ii++)
        *(position + ii) = 0.0;
    for(int ii = 0; ii < N; ii++)
        *(state + ii) = 0;

    boot();
}

d_sir::~d_sir (){
    if (position != nullptr)
        delete [] position;
    if (state != nullptr)
        delete [] state;
}

void d_sir::boot(){
    int P;

    for (int ii = 0 ; ii < 2*N; ii++){
        *(position + ii) = L * rand64.r();
    }

    for (int ii = 0; ii < Infected; ii++){
        bool coin = true;
        while(coin){
            P = int((N+1)*rand64.r());
            if (state[P] != 1){
                *(state + P) = 1;
                coin = false;
            }
        }
    }

}

double d_sir::distance(int n, int m){
    double x = *(position + n) - *(position + m); 
    double y = *(position + N + n) - *(position + N + m);
    double d = sqrt(pow(x,2) + pow(y,2));
    return d;
}

void d_sir::get_survey(int &s, int &i, int &r){
    s = 0; i = 0; r = 0;
    for (int ii = 0; ii < N ; ii++){
        if (state[ii] == 1)
            i += 1;
        else if (state[ii] == 0){
            s += 1;
            sneeze(ii);
        }
        else r += 1;
    }
}

void d_sir::sneeze(int ii){
    double d = 0;

    for(int jj = 0; jj < N; jj++){
        if (state[jj] == 1){
            d = distance(ii, jj);
        }
        else continue;
        double r = rand64.r();
        if (d<=infected_distance && r <= infected_prob ){
            *(state + ii) = 1;
        }
    }
}

void d_sir::move_p(){
    double mu = 0.0, sigma = sqrt(2.0 * D * dt);

    for (int ii = 0 ; ii < 2*N; ii++){
        double dx = rand64.gauss(mu, sigma);
        *(position + ii) += dx;
        if(position[ii] > L)
            *(position + ii) -= 2 * dx;
        if(position[ii] < 0)
            *(position + ii) += 2 * dx;
    }
}

void d_sir::show(){
    // std::cout << "Position = ";
    // for(int kk = 0; kk < 2*N; kk++)
    //     std::cout << *(position + kk) << "\t";
    // std::cout << "\n";

    // std::cout << "State = ";
    // for(int kk = 0; kk < N; kk++)
    //     std::cout << *(state + kk) << "\t";
    // std::cout << "\n";

    get_survey(S, I, R);
    std::cout << S << "\t" << I << "\t" << R << "\n";
}

// %-------------------------------------------------------%
// %------------------% CRONOMETER CLASS %-----------------%
// %-------------------------------------------------------%

class crono{
public:
    crono (d_sir & Diffusive);
    ~crono ();

    void end(d_sir & Diffusive);
    void update(d_sir & Diffusive);
private:
    double * time;
};

crono::crono(d_sir & Diffusive){
    time = new double [Diffusive.N];
    for(int ii = 0; ii < Diffusive.N; ii++)
        *(time + ii) = 0.0;
}

crono::~crono(){
    if(time != nullptr)
        delete [] time;
}

void crono::update(d_sir & Diffusive){
    for(int kk = 0; kk < Diffusive.N ; kk++){
        if(Diffusive.state[kk] == 1){
            *(time + kk) += Diffusive.dt;
        }
    }
}

void crono::end(d_sir & Diffusive){
    for(int kk = 0; kk < Diffusive.N; kk++){
        if(time[kk] > Diffusive.recovery_time){
            *(time + kk) = -666;
            *(Diffusive.state + kk) = 2;
        }
    }
}

#endif