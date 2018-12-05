/* on importe nos Lib*/
#include <iostream>     //Permet de gérer les input output (io)
#include <fstream>      //Permet de gérer des fichier (f)
#include <cmath>        //Importe quelques fonctions mathématiques
#include <cstdlib>      //Permet d'utiliser la fonction rand()
#include "Eigen/Dense"  //Permet d'utiliser des matrices

using namespace std;
using namespace Eigen;

const double G = 6.674e-11;

double aGravity(double Mb,double Rab)
{
    return -G*Mb/(Rab*Rab);
}

void dP(MatrixXd& dS0, MatrixXd& S0)
{
  dS0.row(0) = S0.row(2);
  dS0.row(1) = S0.row(3);
}

void VectorP(VectorXd& P, VectorXd& S)
{
  P(0) = S(0);
  P(1) = S(1);
}

void dV(MatrixXd& dS0, MatrixXd& S0, VectorXd& M)
{
  int n = M.size();

  VectorXd Pa(2);
  VectorXd Pb(2);
  VectorXd dVi(2);
  VectorXd R(2);
  VectorXd Col(n);
  double Rab = 0;

  for (int i = 0; i < n; i++)
  {
    dVi(0) = 0;
    dVi(1) = 0;
    Col = S0.col(i);
    VectorP(Pa,Col);
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        Col = S0.col(j);
        VectorP(Pb,Col);
        R = Pa-Pb;
        Rab = R.norm();
        dVi +=  aGravity(M(j),Rab)*R.normalized();
      }
    }
    dS0(2,i) = dVi(0);
    dS0(3,i) = dVi(1);
  }
}

void deriv(MatrixXd& dS0,MatrixXd& S0, VectorXd& M)
{
  dP(dS0,S0);
  dV(dS0,S0,M);
}

void CenterOM(VectorXd& M, MatrixXd& S)
{
  double m = M.sum();
  int n = M.size();
  VectorXd SM(2);
  SM << 0,0;

  for (int i = 0; i < n; i++)
  {
    SM(0) += S(0,i)*M(i);
    SM(1) += S(1,i)*M(i);
  }
  SM = SM/m;
  for (int i = 0; i < n; i++)
  {
    S(0,i) -= SM(0);
    S(1,i) -= SM(1);
  }
}

void SpeedOM(VectorXd& M, MatrixXd& S)
{
  double m = M.sum();
  int n = M.size();
  VectorXd SM(2);
  SM << 0,0;

  for (int i = 0; i < n; i++)
  {
    SM(0) += S(2,i)*M(i);
    SM(1) += S(3,i)*M(i);
  }
  SM = SM/m;
  for (int i = 0; i < n; i++)
  {
    S(2,i) -= SM(0);
    S(3,i) -= SM(1);
  }
}
