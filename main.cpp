#include <iostream>
#include<gsl/gsl_rng.h>
#include<cmath>
#include<fstream>

using namespace std;


int BKL(double n, double ra, double rd,  gsl_rng * g){

    ofstream plik;
    plik.open ("dane5.txt", fstream::app);

    cout << "ra: " << ra << ", rd: " << rd << "ra/rd: " << ra/rd << endl;

double t = 0;
double Theta = 0;
int NA = 10000;
int ND = 0;
int N = 10000;
double rA = NA *ra;
double rD = 0;
double R = rA + rD;


    for(int i=0; i<=n; i++){

        double u1 = gsl_rng_uniform(g);
        double q = R*u1; // losowanie z zakresu od zera do R

            if (q < rA) //ADSORBCJA
            {
                NA--;
                ND++;
                rA -= ra;
                rD += rd;
                R = rA + rD;
            }
            else //desorpcja - na odwrot wszystko
            {
                NA++;
                ND--;
                rA += ra;
                rD -= rd;
                R = rA + rD;
            }

            double u2 = gsl_rng_uniform(g);
            double Theta = ((double) ND/N);
            plik << t << " " << Theta << endl;
            t += -log(u2)/R; //uplyw czasu
    }

 plik.close();
}

int main()
{
    gsl_rng *t_gen = gsl_rng_alloc(gsl_rng_mt19937);
    BKL(30000,2,1, t_gen);
    BKL(30000,1,1, t_gen);
    BKL(30000,1,4, t_gen);

    return 0;
}
