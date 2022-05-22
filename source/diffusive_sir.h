#ifndef _DIFFUSIVE_H
#define _DIFFUSIVE_H

// #include <iostream>
#include <cmath>
#include <random>

// template <class T>
class diffusive_sir
{
public:
  diffusive_sir (int N, double infected, double density);
  ~diffusive_sir ();

  void initial_position(int N);
  void infect(int infected);

  void get_indices_by_health(int N);

  double distance();

  void check_infected(int *susceptible, int *infected);
  void add_infected_time();
  void check_recovered();

  void evolve(double t_max);


private:
  double D = 100; // m²/day
  double dt = 0.01; // day
  double recovery_time = 14.0; // days
  double infected_distance = 2.0; // m
  double infected_prob = 0.2;

private:
  int n; double L;
  double dens ;
  double *particle;
  double *health_time;

public:
  int *S; int *I; int *R;
  int *sick;

};

// template <class T>
diffusive_sir::diffusive_sir(int N, double infected, double density){
  n = N;
  dens = density;
  L = std::sqrt(n / dens);
  double infectt = infected;
  double particle[3*n] = {0.0};

  initial_position(int n, double L);
  infect(int (n * infectt));

}
// template <class T>
diffusive_sir::~diffusive_sir (){
  if (particle != nullptr){
    delete [] particle;
  }
}

void diffusive_sir::initial_position(int N, double L){
  n = N;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(0.0, 1.0);

  for (int ii = 0 ; ii < 2*n; ++ii){
    *(particle + ii) = L * distr(eng);
  }
}

void diffusive_sir::infect(int infected){
  n = N;
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_int_distribution<> distrib(0, n);

  for (int ii = 0; ii < infected; ++ii){
    bool flag = True ;
    while (flag) {
      p = distrib(gen);
      if ( *(particle + 2*n + p) != 0 ){
        *(particle + 2*n +p) = 1;
        flag = False;
      }
    }
  }
}

void diffusive_sir::get_indices_by_health(int N){
  n = N;

  for (int ii = 0; ii < n ; ++ii){
    if (*(particle + 2*n +ii) == 0){ *(S + ii) = ii }
    if (*(particle + 2*n +ii) == 1){ *(I + ii) = ii ;  *(sick + ii) = ii;}
    else { *(R + ii) = ii ; *(sick + ii) = ii;}
  }
}

double diffusive_sir::distance(int N; int d_s, int d_i){
  n = N;
  double x = *(particle + ii) + *(particle + kk);
  double y = *(particle + n + ii) + *(particle + n + kk);
  norm = sqrt(x*x + y*y);
  return norm;
}

void diffusive_sir::check_infected(int N, int *susceptible, int *infected){
  n = N
  S = susceptible;
  I = infected;
  int size_S = sizeof(S)/sizeof(S[0]);
  int size_I = sizeof(I)/sizeof(I[0]);

  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(0.0, 1.0);

  for (int ii = 0; ii < size_S; ++ii){
    int d_s = *(S + ii)
    for (int kk = 0; kk < size_I; ++kk){
      int d_i = *(I + kk)
      double norm = distance(n, d_s, d_i);
      double prop = distr(eng);

      if (norm <= infected_distance && prop <= infected_prob){
        *(particle + 2*n + ii) = 1;
        *(health_time + ii) = 0.0;
        break
      }
    }
  }

}

void diffusive_sir::add_infected_time(){
  
}

#endif
