#include <iostream>
#include <cmath>
#include <random>

class d_sir {
public:
    d_sir ();
    d_sir (int Number, double infected, double density);
    ~d_sir ();

    void boot();
    void show();
    void get_survey(int &s, int &i, int &r);
    void sneeze();
    double distance(int n, int m);
    void move_p();
    // void evolve(double t_max);

    int get_s(){return S;};
    int get_i(){return I;};
    int get_r(){return R;};

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

d_sir::d_sir (){ 
    position = new double [1];
    position[0] = 0.0;
    state = new int [1];
    state[0] = 0;
}

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
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0.0, 1.0);
    
    std::random_device r;
    std::mt19937 gen(r());
    std::uniform_int_distribution<> distrib(0, N-1);

    for (int ii = 0 ; ii < 2*N; ii++){
        *(position + ii) = L * distr(eng);
    }

    for (int ii = 0; ii < Infected; ii++){
        bool coin = true;
        while(coin){
            int P = distrib(gen);
            if (state[P] != 1){
                *(state + P) = 1;
                // std::cout << P << std::endl;
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
    for (int ii = 0; ii < N ; ii++){
        if (state[ii] == 0)
            s += 1;
        else if (state[ii] == 1)
            i += 1;
        else r += 1;
    }
}

void d_sir::sneeze(){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0.0, 1.0);
    double d;
    for (int ii = 0; ii < N ; ii++){
        d = infected_distance + 1;
        if (state[ii] == 0){
            for(int jj = 0; jj < N; ii++){
                if (state[jj] == 1){
                    d = distance(ii, jj);
                }
                double r = distr(eng);
                if (d<=infected_distance && r <= infected_prob ){
                    *(state + ii) = 1;
                    break;
                }
            }
        }
    }
}

void d_sir::move_p(){
    double sigma = sqrt(2.0 * D * dt);
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,sigma);

    for (int ii = 0 ; ii < 2*N; ii++){
        double dx = distribution(generator);
        *(position + ii) += dx;
        if(position[ii] > L)
            *(position + ii) -= 2 * dx;
        if(position[ii] < 0)
            *(position + ii) += 2 * dx;
    }
}

// void d_sir::evolve(double t_max){
//     double sigma = sqrt(2.0 * D * dt);

//     for(double t=0.0 ; t<t_max ; t+= dt){

//     }
// }

void d_sir::show(){
    std::cout << "Position = ";
    for(int kk = 0; kk < 2*N; kk++)
        std::cout << *(position + kk) << "\t";
    std::cout << "\n";
    std::cout << "State = ";
    for(int kk = 0; kk < N; kk++)
        std::cout << *(state + kk) << "\t";
    std::cout << "\n";
    get_survey(S, I, R);
    std::cout << S << "\t" << I << "\t" << R << "\n";
}

class crono{
public:
    crono (d_sir & Diffusive);
    ~crono ();

    void end(d_sir & Diffusive);
    void update(d_sir & Diffusive);
private:
    double * time; int N;
};

crono::crono(d_sir & Diffusive){
    time = new double [Diffusive.N];
    for(int ii = 0; ii < N; ii++)
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
            *(time + kk) = -99;
            *(Diffusive.state + kk) = 2;
        }
    }
}

template <int N>
int dimension(double (&A)[N]){
    int size = sizeof(A)/sizeof(*(A)); 
    return size;
}

int main(){

    d_sir D(100, 0.011, 0.012);
    D.show();
    D.move_p();
    D.show();

    return 0;
}