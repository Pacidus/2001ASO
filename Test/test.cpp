#include "../Headers/Forces.hpp"
#include "../Headers/RK4.hpp"
#include "../Headers/games.hpp"

int main()
{
  int n = 2;
  MatrixXd S(4,n);
  VectorXd M(n);

  S <<     0, -3.0160407335029,
           0, -4.4601934888848,
           0, 0.0061682687985/86400,
           0,-0.0038751868420/86400;

  S *= 1.49597870e11;

  M << 1.9891e30, 1.8986e30;

  SpeedOM(M, S);
  CenterOM(M, S);

  ofstream fichier1("SolarSystemPos.dat");
  ofstream fichier2("SolarSystemVit.dat");

  double t_max = 100*24*365.25;
  double dt = 1;
  double icr= dt/3600;
  int T = 0;

  for (double t = 0; t < t_max; t += icr)
  {
    RK4(S, M, dt,deriv);
    if(T%86400 == 0){
      fichier1 << (S.row(0)) <<" " <<(S.row(1)) << endl;
      fichier2 << (S.row(2)) <<" " <<(S.row(3)) << endl;
      T = 0;
      }
    T++;
  }
  return 0;
}
