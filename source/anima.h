#include <iostream>
#include "./diffusive_sir.h"

//  -----------------  Plot SIR curves

void plot_sir(d_sir & Dsir, crono & Cro, int & s, int & i, int & r, double t_max, double dt){
     double t=0;
     while(t < t_max){
        std::cout << t << "\t" << s << "\t" << i << "\t" << r << "\n";
        Dsir.get_survey(s, i, r);
        Cro.update(Dsir);
        Cro.end(Dsir);
        Dsir.move_p();
        t += dt;
    }
}

//  -----------------  Show distribution of populace and the state of each person

void StartAnimation(double a, double b){
    std::cout << "set terminal gif animate" << std::endl;
    std::cout << "set output './../data/sir_evolution.gif'" << std::endl;
    std::cout << "unset key" << std::endl;
    std::cout << "set xlabel 'x [m]'" << std::endl;
    std::cout << "set ylabel 'y [m]'" << std::endl;
    std::cout << "set title 'SIR Animation'" << std::endl;
    std::cout << "set border linewidth 1.5" << std::endl;
    std::cout << "set pointsize 1.5" << std::endl;
    std::cout << "set xrange["<< a <<":"<< b <<"]" << std::endl;
    std::cout << "set yrange["<< a <<":"<< b <<"]" << std::endl;
    // std::cout << "set term png" << std::endl;
    // std::cout << "set out './../data/final.png'" << std::endl;
}

void SetAnimation(d_sir & Dsir, int N){
    double * position = Dsir.Position();
    int * state = Dsir.State(); int m = 0;
    std::string colour[] = {"green", "red", "yellow"};

    while(m<3){
        for(int ii = 0, jj = 1; ii < N; ii++, jj++)
            if(state[ii] == m)
                std::cout << "set style line "<< jj <<" lc rgb '"<< colour[state[ii]] <<"' pt 7" << std::endl;
        m++;
    }
}

void StartPlot(int N){
    std::cout << "plot '-'  w p ls 1";
    for(int ii = 1; ii < N; ii++)
        std::cout << " , '-'  w p ls " << ii+1;
    std::cout << std::endl; 
}

void FinishPlot(){
    std::cout << std::endl;
}

void Draw(d_sir & Dsir, int N){
    double * position = Dsir.Position();
    int * state = Dsir.State(); int n = 0;

    while(n < N){
        for(int s = 0; s < 3; s++)
            if(state[n] == s)
                std::cout << position[n] << " " << position[n+N] << "\n" << "e" << std::endl;
        n++;
    }  
}

//  -----------------  Make gif

void plot_evolution(int N, double density, d_sir & Dsir, crono & Cro, int & s, int & i, int & r, double t_max, double dt){
    double t=0;

    StartAnimation(0, sqrt(N / density));
    // SetAnimation(Dsir, N);

    while(t < t_max){
        SetAnimation(Dsir, N);
        StartPlot(N);
        Draw(Dsir, N);

        Dsir.get_survey(s, i, r);
        Cro.update(Dsir);
        Cro.end(Dsir);
        Dsir.move_p();
        t += dt;

        FinishPlot();
    }
}