/* on importe nos Lib*/
#include <iostream>     //Permet de gérer les input output (io)
#include <fstream>      //Permet de gérer des fichier (f)
#include <cmath>        //Importe quelques fonctions mathématiques
#include <cstdlib>      //Permet d'utiliser la fonction rand()
#include "Eigen/Dense"  //Permet d'utiliser des marices

using namespace std;
using namespace Eigen;

void Sum(MatrixXd& Som, MatrixXd& A, MatrixXd& B,double x)
{
  Som = A+B*x;
}

void RK4(MatrixXd& S0, VectorXd& M, double dt,void F(MatrixXd& ,MatrixXd& , VectorXd&))
{
  double Dt = dt,t = 0;
  int Nbc,Nbl, D;
  Nbc = S0.cols();
  Nbl = S0.rows();

  MatrixXd dS0(Nbl,Nbc);
  MatrixXd k1(Nbl,Nbc);
  MatrixXd k2(Nbl,Nbc);
  MatrixXd k3(Nbl,Nbc);
  MatrixXd k4(Nbl,Nbc);
  MatrixXd S(Nbl,Nbc);

  F(dS0, S0, M);
  D = rint(dS0.row(2).norm()+dS0.row(3).norm());
  dt = Dt/(1+D);

  while (t < Dt)
  {
    F(dS0, S0, M);
    t += dt;

    k1 = dS0*dt;
    Sum(S, S0, k1,1/2);
    F(dS0, S, M);
    k2 = dS0*dt;
    Sum(S, S0, k2,1/2);
    F(dS0, S, M);
    k3 = dS0*dt;
    Sum(S, S0, k3,1/2);
    F(dS0, S, M);
    k4 = dS0*dt;

    S0 += (k1+2*k2+2*k3+k4)/6;
  }
}
