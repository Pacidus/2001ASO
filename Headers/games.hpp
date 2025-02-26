/* on importe nos Lib*/
#include <SFML/Graphics.hpp>  //Permet de faire l'affichage
#include <SFML/Audio.hpp>     //Permet de faire l'audio
#include <iostream>           //Permet de gérer les input output (io)
#include <fstream>            //Permet de gérer des fichier (f)
#include <cmath>              //Importe quelques fonctions mathématiques
#include <cstdlib>            //Permet d'utiliser la fonction rand()
#include "Eigen/Dense"        //Permet d'utiliser des matrices
#include <sstream>            //string-stream
#include <unistd.h>           //usleeep

using namespace std;
using namespace sf;
using namespace Eigen;

/*============================================================================*/
                                /*Data*/
/*============================================================================*/
void Save(VectorXd& M, MatrixXd& S)
{
  ostringstream filename;
  filename << "./Sauvegardes/Sauvegarde.sav";
  ofstream fichier(filename.str().c_str());
  fichier << S.rows() << "," << S.cols() << endl;
  fichier << S << endl << M << endl;
  fichier.close();
}//Save

/*============================================================================*/

void Import(VectorXd& M, MatrixXd& S)
{
  int Ncol, Nlign;
  ostringstream filename;
  filename << "./Sauvegardes/Sauvegarde.sav";
  ifstream fichier(filename.str().c_str());
  fichier >> Ncol;
  fichier >> Nlign;
  for (int i = 0; i < Ncol; i++)
  {
    for (int j = 0; j < Nlign; j++)
    {
      fichier >> S(i,j);
    }//for j
  }//for i

  for (int j = 0; j < Nlign; j++)
  {
    fichier >> M(j);
  }//for j
  fichier.close();
}//Import

/*============================================================================*/
                        /*Écran de sélection*/
/*============================================================================*/

void SeTitle(RenderWindow& window, Text& Title)
{
  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;

  Title.setCharacterSize(SCRWIDTH/15);
  Title.setOutlineThickness(100);
  FloatRect textRect = Title.getLocalBounds();
  Title.setOrigin(textRect.left + textRect.width/2.0f,
                  textRect.top  + textRect.height/2.0f);
  Title.setPosition(SCRWIDTH/2.0f,SCRHEIGHT/2.0f);
  Title.setFillColor(Color(255,255,255,220));
  Title.setStyle(Text::Regular);
}//SeTitle

/*============================================================================*/

void SeText(RenderWindow& window, Text& Text)
{
  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;

  Text.setCharacterSize(SCRWIDTH/30);
  Text.setOutlineThickness(100);
  FloatRect textRect = Text.getLocalBounds();
  Text.setOrigin(textRect.left + textRect.width/2.0f,
                  textRect.top  + textRect.height/2.0f);
  Text.setPosition(SCRWIDTH/2.0f,SCRHEIGHT*3/4.0f);
  Text.setFillColor(Color::White);
  Text.setStyle(Text::Regular);
}//SeText

void EScreen(RenderWindow& window)
{

  Font Font1;
  Font1.loadFromFile("./Assets/EarthOrbiter/earthorbiterdeep3d.ttf");
  Font Font2;
  Font2.loadFromFile("./Assets/EarthOrbiter/earthorbiter.ttf");

  Text Title,text;
  Title.setFont(Font1);
  Title.setString("2001 a space odyssey");
  SeTitle(window, Title);

  text.setFont(Font2);
  text.setString("Press space to continue");
  SeText(window, text);
  double t = 0;

  while (window.isOpen())
  {
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
      return;
    }
    if (Keyboard::isKeyPressed(Keyboard::Space))
    {
      window.display();
      return;
    }

    window.clear(Color::Black);
    window.draw(Title);
    window.draw(text);
    window.display();
    text.setFillColor(Color(255,255,255,255*(cos(t)*cos(t))));
    t += 0.02;
  }
}

int CScreen(RenderWindow& window, Sound& sound)
{
  Font Font1;
  Font1.loadFromFile("./Assets/EarthOrbiter/earthorbiter.ttf");

  Text Prop[6];
  for (int i = 0; i < 6; i++)
  {
    Prop[i].setFont(Font1);
  }
  Prop[0].setString("Space mission mode");
  Prop[1].setString("Free mode");
  Prop[2].setString("Credits");
  Prop[3].setString(">  Space mission mode");
  Prop[4].setString(">  Free mode");
  Prop[5].setString(">  Credits");
  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;

  FloatRect textRect;

  for (int i = 0; i < 6; i++)
  {
    Prop[i].setCharacterSize(SCRWIDTH/30);
    Prop[i].setOutlineThickness(100);
    textRect = Prop[i].getLocalBounds();
    Prop[i].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top  + textRect.height/2.0f);
    Prop[i].setPosition(SCRWIDTH/2.0f,SCRHEIGHT*(1+i%3)/4.0f);
    Prop[i].setFillColor(Color::White);
    Prop[i].setStyle(Text::Regular);
  }

  int i[3] = {3,0,0};
  int j = 0;
  window.draw(Prop[0]);
  window.draw(Prop[1]);
  window.draw(Prop[2]);
  window.display();

  while (window.isOpen())
  {

    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
      return 4;
    }
    if (Keyboard::isKeyPressed(Keyboard::Space))
    {
        return j;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      sound.play();
      j = (3+(j+1)%3)%3;
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      sound.play();
      j = (3+(j-1)%3)%3;
    }


    window.clear(Color::Black);
    window.draw(Prop[0+i[j]]);
    window.draw(Prop[1+i[(1+j)%3]]);
    window.draw(Prop[2+i[(2+j)%3]]);
    window.display();
    usleep(200000);
  }
}



void Game0(RenderWindow& window, Music& music)
{
  SoundBuffer Trust;
  Trust.loadFromFile("Assets/Musique/11571.wav");
  Sound trust;
  trust.setBuffer(Trust);
  trust.setVolume(25);

  Music VC;
  VC.openFromFile("Assets/Musique/V>C.wav");

  int n = 10;
  MatrixXd S(4,n);
  VectorXd M(n);
  S <<     0,-0.3873787757899, 0.6998540556852, -0.1968869740070, -0.1967234562488,0.4353667901115, -3.0160407335029, -0.3669665115915, -6.4792676094521,0,
           0,-0.1626538422024,-0.1936811455555,  0.9633524690520, 0.9608958211479,-1.3525118186157, -4.4601934888848,-10.058353164307, -17.853439279374, 0,
           0, 0.0050800383277/86400, 0.0052886844117/86400, -0.0171450581201/86400,-0.0165327607659/86400 ,0.0138579583479/86400, 0.0061682687985/86400, 0.0052739191614/86400, 0.0036743237385/86400,0,
           0,-0.0247028303185/86400, 0.0194037752153/86400,-0.0035087020323/86400, -0.0034406819679/86400,0.0054827478504/86400,-0.0038751868420/86400, -0.0002276932226/86400, -0.0015284677821/86400, 0;

  S *= 1.49597870e11;
  S(0,9) = ((S(0,4)-S(0,3))/70)+S(0,3);
  S(1,9) = ((S(1,4)-S(1,3))/70)+S(1,3);
  S(2,9) = ((S(2,4)-S(2,3))*8)+S(2,3);
  S(3,9) = ((S(3,4)-S(3,3))*8)+S(3,3);
  M << 1.9891e30, 3.3011e23, 4.8685e24, 5.9736e24, 7.3477e22, 6.4185e23, 1.8986e27,5.6846e26,8.6810e25, 419.725;

  Save(M,S);
  Import(M,S);
  SpeedOM(M, S);
  CenterOM(M, S);

  Image image[n+1];
  image[0].loadFromFile("./Assets/Sprites/Sun.png");
  image[1].loadFromFile("./Assets/Sprites/Mercury.png");
  image[2].loadFromFile("./Assets/Sprites/Venus.png");
  image[3].loadFromFile("./Assets/Sprites/Earth.png");
  image[4].loadFromFile("./Assets/Sprites/Moon.png");
  image[5].loadFromFile("./Assets/Sprites/Mars.png");
  image[6].loadFromFile("./Assets/Sprites/Jupiter.png");
  image[7].loadFromFile("./Assets/Sprites/Saturn.png");
  image[8].loadFromFile("./Assets/Sprites/Neptune.png");
  image[9].loadFromFile("./Assets/Sprites/space-ship.png");
  image[10].loadFromFile("./Assets/Sprites/space-ship-t.png");

  Font Font2;
  Font2.loadFromFile("./Assets/EarthOrbiter/earthorbiter.ttf");

  Text text[n], vit, Prop, Carbu;
  double Acc = 0;
  double T = 3000;
  vit.setFont(Font2);
  Prop.setFont(Font2);
  Carbu.setFont(Font2);
  ostringstream speed;
  speed << "vitesse : " << endl << sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1)) << " m/s";
  ostringstream Acce;
  Acce << "Propulseur : " << endl << Acc << " m/s²";
  ostringstream Carb;
  Carb << "Carburant : " << endl << T << "Kg";
  for (int i = 0; i < n; i++)
  {
    text[i].setFont(Font2);
  }
  text[0].setString("Soleil");
  text[1].setString("Mercure");
  text[2].setString("Venus");
  text[3].setString("Terre");
  text[4].setString("Lune");
  text[5].setString("Mars");
  text[6].setString("Jupiter");
  text[7].setString("Saturne");
  text[8].setString("Uranus");
  text[9].setString("Vaisseau");
  vit.setString(speed.str().c_str());
  Prop.setString(Acce.str().c_str());
  Carbu.setString(Carb.str().c_str());
  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;
  vit.setPosition(6.5*SCRWIDTH/20,4*SCRHEIGHT/20);
  vit.setCharacterSize(SCRWIDTH/50);
  Prop.setPosition(6.5*SCRWIDTH/20,6*SCRHEIGHT/20);
  Prop.setCharacterSize(SCRWIDTH/50);
  Carbu.setPosition(6.5*SCRWIDTH/20,8*SCRHEIGHT/20);
  Carbu.setCharacterSize(SCRWIDTH/50);
  for (int i = 0; i < n; i++)
  {
    text[i].setCharacterSize(SCRWIDTH/500);
    text[i].setOutlineThickness(0);
    FloatRect textRect = text[i].getLocalBounds();
    text[i].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top  + textRect.height/2.0f);
    text[i].setFillColor(Color::White);
    text[i].setStyle(Text::Regular);
  }

  Texture Fire;
  Fire.loadFromImage(image[n]);

  Texture tex[n];
  Sprite sp[n*2];
  double rayon[n+1] = {6963.92*5, 24.397*5,	60.518*5, 63.710*5, 17.36*5,
                    33.895*5,699.11*5,582.32*5,253.62*5,20,60}; // rayon des corps en 1e4metres
  for (int i = 0; i < n; i++)
  {
    tex[i].loadFromImage(image[i]);

    sp[i].setTexture(tex[i]);

    sp[i].setScale(10*rayon[i]/sp[i].getLocalBounds().width,
                   10*rayon[i]/sp[i].getLocalBounds().width);

    sp[i].setOrigin(sp[i].getLocalBounds().width/2.f,
                    sp[i].getLocalBounds().width/2.f);

    sp[i+n].setTexture(tex[i]);

    sp[i+n].setScale(2*rayon[n]/sp[i+n].getLocalBounds().width,
                     2*rayon[n]/sp[i+n].getLocalBounds().width);

    sp[i+n].setOrigin(sp[i+n].getLocalBounds().width/2.f,
                      sp[i+n].getLocalBounds().width/2.f );
  }

  View view1(sf::Vector2f(0,0),sf::Vector2f(1900*2.5,1008*2.5));
  View view2(sf::Vector2f(0,0),sf::Vector2f(SCRWIDTH,SCRHEIGHT));
  View minimapView(sf::Vector2f(0,0),sf::Vector2f(19000,10080));
  minimapView.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));

  window.setView(view1);
  window.setView(minimapView);

  window.clear(Color::Black);
  double dt = .0001;
  int I_max = 10;
  double theta = 0;
  double x,y;
  SCRWIDTH = view2.getSize().x;
  SCRHEIGHT = view2.getSize().y;

  while (window.isOpen())
  {
    Event event;
    window.clear(Color::Black);
    while (window.pollEvent(event))
    {
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
        window.close();
      }
      if (Keyboard::isKeyPressed(Keyboard::Num1))
      {
        dt = 0.0001;
        I_max = 10;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num2))
      {
        dt = 0.0001;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num3))
      {
        dt = 0.001;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num4))
      {
        dt = 0.01;
        I_max = 100;
      }

      if (Keyboard::isKeyPressed(Keyboard::Num5))
      {
        dt = .1;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num6))
      {
        dt = .1;
        I_max = 1000;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num7))
      {
        dt = 1;
        I_max = 1000;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num8))
      {
        dt = 1;
        I_max = 10000;
      }
      if (Keyboard::isKeyPressed(Keyboard::A))
      {
        view1.zoom(0.5f);
      }
      if (Keyboard::isKeyPressed(Keyboard::Z))
      {
        view1.zoom(1.5f);
      }
      if (Keyboard::isKeyPressed(Keyboard::R))
      {
        x = S(2,n-1);
        y = S(3,n-1);
        theta = 360*atan(y/(sqrt(x*x+y*y)+x))/M_PI;
        sp[n-1].setRotation(180+theta);
      }
      if (Keyboard::isKeyPressed(Keyboard::Left))
      {
        sp[n-1].rotate(-4);
      }
      if (Keyboard::isKeyPressed(Keyboard::Down))
      {
        if(Acc > 0) Acc-=0.5;
      }
      if (Keyboard::isKeyPressed(Keyboard::Up))
      {
        if(Acc < 10) Acc+=0.5;
      }
      if (Keyboard::isKeyPressed(Keyboard::Right))
      {
        sp[n-1].rotate(4);
      }

      if (Keyboard::isKeyPressed(Keyboard::Space))
      {
        if(T > 0 and Acc != 0)
        {
          S(2,n-1)+=Acc*cos(2*M_PI*sp[n-1].getRotation()/360);
          S(3,n-1)+=Acc*sin(2*M_PI*sp[n-1].getRotation()/360);
          sp[n-1].setTexture(Fire);
          if (trust.getStatus() == Music::Stopped) trust.play();
          T -= Acc/20;
        }
        if(T < 0) T = 0;
      }
      else
      {
        sp[n-1].setTexture(tex[n-1]);
        trust.stop();
      }
    }

    view1.setCenter(S(0,9)*5e-4,S(1,9)*5e-4);

    for (int i = 0; i < n; i++)
    {
      window.setView(view1);
      sp[i].setPosition(S(0,i)*5e-4,S(1,i)*5e-4);
      window.draw(sp[i]);
      x = S(0,i)-S(0,n-1);
      y = S(1,i)-S(1,n-1);

      theta = 2*atan(y/(sqrt(x*x+y*y)+x));
      text[i].setCharacterSize(SCRWIDTH/50);
      text[i].setPosition((4*SCRWIDTH/10)*cos(theta),(4*SCRHEIGHT/10)*sin(theta));
      window.setView(view2);
      window.draw(text[i]);
    }

    window.setView(view2);
    speed.str("");
    if(sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1))> 299192458 and VC.getStatus() == Music::Stopped)
    {
      music.stop();
      VC.play();
    }
    if(sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1))< 299192458 and VC.getStatus() == Music::Stopped and music.getStatus() == Music::Stopped)
    {
      music.play();
    }
    speed << "vitesse : " << endl << sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1)) << " m/s";
    vit.setString(speed.str().c_str());
    Acce.str("");
    Acce << "Propulsseur : " << endl << Acc << " m/s²";
    Prop.setString(Acce.str().c_str());
    Carb.str("");
    Carb << "Carburant : " << endl << T << " Kg";
    Carbu.setString(Carb.str().c_str());
    window.draw(vit);
    window.draw(Prop);
    window.draw(Carbu);
    window.display();

    for(int i = 0; i < I_max; i++)
    {
      RK4(S, M, dt,deriv);
    }
  }
}


void Game1(RenderWindow& window, Music& music)
{
  SoundBuffer Trust;
  Trust.loadFromFile("Assets/Musique/11571.wav");
  Sound trust;
  trust.setBuffer(Trust);
  trust.setVolume(25);

  Music VC;
  VC.openFromFile("Assets/Musique/V>C.wav");

  int n = 10;
  MatrixXd S(4,n);
  VectorXd M(n);
  S <<     0,-0.3873787757899, 0.6998540556852, -0.1968869740070, -0.1967234562488,0.4353667901115, -3.0160407335029, -0.3669665115915, -6.4792676094521,0,
           0,-0.1626538422024,-0.1936811455555,  0.9633524690520, 0.9608958211479,-1.3525118186157, -4.4601934888848,-10.058353164307, -17.853439279374, 0,
           0, 0.0050800383277/86400, 0.0052886844117/86400, -0.0171450581201/86400,-0.0165327607659/86400 ,0.0138579583479/86400, 0.0061682687985/86400, 0.0052739191614/86400, 0.0036743237385/86400,0,
           0,-0.0247028303185/86400, 0.0194037752153/86400,-0.0035087020323/86400, -0.0034406819679/86400,0.0054827478504/86400,-0.0038751868420/86400, -0.0002276932226/86400, -0.0015284677821/86400, 0;

  S *= 1.49597870e11;
  S(0,9) = ((S(0,4)-S(0,3))/70)+S(0,3);
  S(1,9) = ((S(1,4)-S(1,3))/70)+S(1,3);
  S(2,9) = ((S(2,4)-S(2,3))*8)+S(2,3);
  S(3,9) = ((S(3,4)-S(3,3))*8)+S(3,3);
  M << 1.9891e30, 3.3011e23, 4.8685e24, 5.9736e24, 7.3477e22, 6.4185e23, 1.8986e27,5.6846e26,8.6810e25, 419.725;

  Save(M,S);
  Import(M,S);
  SpeedOM(M, S);
  CenterOM(M, S);

  Image image[n+1];
  image[0].loadFromFile("./Assets/Sprites/Sun.png");
  image[1].loadFromFile("./Assets/Sprites/Mercury.png");
  image[2].loadFromFile("./Assets/Sprites/Venus.png");
  image[3].loadFromFile("./Assets/Sprites/Earth.png");
  image[4].loadFromFile("./Assets/Sprites/Moon.png");
  image[5].loadFromFile("./Assets/Sprites/Mars.png");
  image[6].loadFromFile("./Assets/Sprites/Jupiter.png");
  image[7].loadFromFile("./Assets/Sprites/Saturn.png");
  image[8].loadFromFile("./Assets/Sprites/Neptune.png");
  image[9].loadFromFile("./Assets/Sprites/space-ship.png");
  image[10].loadFromFile("./Assets/Sprites/space-ship-t.png");

  Font Font2;
  Font2.loadFromFile("./Assets/EarthOrbiter/earthorbiter.ttf");

  Text text[n], vit, Prop;
  double Acc = 0;
  vit.setFont(Font2);
  Prop.setFont(Font2);
  ostringstream speed;
  speed << "vitesse : " << endl << sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1)) << " m/s";
  ostringstream Acce;
  Acce << "Propulseur : " << endl << Acc << " m/s²";
  for (int i = 0; i < n; i++)
  {
    text[i].setFont(Font2);
  }
  text[0].setString("Soleil");
  text[1].setString("Mercure");
  text[2].setString("Venus");
  text[3].setString("Terre");
  text[4].setString("Lune");
  text[5].setString("Mars");
  text[6].setString("Jupiter");
  text[7].setString("Saturne");
  text[8].setString("Uranus");
  text[9].setString("Vaisseau");
  vit.setString(speed.str().c_str());
  Prop.setString(Acce.str().c_str());
  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;
  vit.setPosition(6.5*SCRWIDTH/20,6*SCRHEIGHT/20);
  vit.setCharacterSize(SCRWIDTH/50);
  Prop.setPosition(6.5*SCRWIDTH/20,8*SCRHEIGHT/20);
  Prop.setCharacterSize(SCRWIDTH/50);
  for (int i = 0; i < n; i++)
  {
    text[i].setCharacterSize(SCRWIDTH/500);
    text[i].setOutlineThickness(0);
    FloatRect textRect = text[i].getLocalBounds();
    text[i].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top  + textRect.height/2.0f);
    text[i].setFillColor(Color::White);
    text[i].setStyle(Text::Regular);
  }

  Texture Fire;
  Fire.loadFromImage(image[n]);

  Texture tex[n];
  Sprite sp[n*2];
  double rayon[n+1] = {6963.92*5, 24.397*5,	60.518*5, 63.710*5, 17.36*5,
                    33.895*5,699.11*5,582.32*5,253.62*5,20,60}; // rayon des corps en 1e4metres
  for (int i = 0; i < n; i++)
  {
    tex[i].loadFromImage(image[i]);

    sp[i].setTexture(tex[i]);

    sp[i].setScale(10*rayon[i]/sp[i].getLocalBounds().width,
                   10*rayon[i]/sp[i].getLocalBounds().width);

    sp[i].setOrigin(sp[i].getLocalBounds().width/2.f,
                    sp[i].getLocalBounds().width/2.f);

    sp[i+n].setTexture(tex[i]);

    sp[i+n].setScale(2*rayon[n]/sp[i+n].getLocalBounds().width,
                     2*rayon[n]/sp[i+n].getLocalBounds().width);

    sp[i+n].setOrigin(sp[i+n].getLocalBounds().width/2.f,
                      sp[i+n].getLocalBounds().width/2.f );
  }

  View view1(sf::Vector2f(0,0),sf::Vector2f(1900*2.5,1008*2.5));
  View view2(sf::Vector2f(0,0),sf::Vector2f(SCRWIDTH,SCRHEIGHT));
  View minimapView(sf::Vector2f(0,0),sf::Vector2f(19000,10080));
  minimapView.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));

  window.setView(view1);
  window.setView(minimapView);

  window.clear(Color::Black);
  double dt = .0001;
  int I_max = 10;
  double theta = 0;
  double x,y;
  SCRWIDTH = view2.getSize().x;
  SCRHEIGHT = view2.getSize().y;

  while (window.isOpen())
  {
    Event event;
    window.clear(Color::Black);
    while (window.pollEvent(event))
    {
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
        window.close();
      }
      if (Keyboard::isKeyPressed(Keyboard::Num1))
      {
        dt = 0.0001;
        I_max = 10;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num2))
      {
        dt = 0.0001;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num3))
      {
        dt = 0.001;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num4))
      {
        dt = 0.01;
        I_max = 100;
      }

      if (Keyboard::isKeyPressed(Keyboard::Num5))
      {
        dt = .1;
        I_max = 100;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num6))
      {
        dt = .1;
        I_max = 1000;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num7))
      {
        dt = 1;
        I_max = 1000;
      }
      if (Keyboard::isKeyPressed(Keyboard::Num8))
      {
        dt = 1;
        I_max = 10000;
      }
      if (Keyboard::isKeyPressed(Keyboard::A))
      {
        view1.zoom(0.5f);
      }
      if (Keyboard::isKeyPressed(Keyboard::Z))
      {
        view1.zoom(1.5f);
      }
      if (Keyboard::isKeyPressed(Keyboard::R))
      {
        x = S(2,n-1);
        y = S(3,n-1);
        theta = 360*atan(y/(sqrt(x*x+y*y)+x))/M_PI;
        sp[n-1].setRotation(180+theta);
      }
      if (Keyboard::isKeyPressed(Keyboard::Left))
      {
        sp[n-1].rotate(-4);
      }
      if (Keyboard::isKeyPressed(Keyboard::Down))
      {
        if(Acc > 1) Acc=-1+Acc/1.01;
      }
      if (Keyboard::isKeyPressed(Keyboard::Up))
      {
        Acc=1.01+1.01*Acc;
      }
      if (Keyboard::isKeyPressed(Keyboard::Right))
      {
        sp[n-1].rotate(4);
      }

      if (Keyboard::isKeyPressed(Keyboard::Space))
      {
        if(Acc > 0)
        {
          S(2,n-1)+=Acc*cos(2*M_PI*sp[n-1].getRotation()/360);
          S(3,n-1)+=Acc*sin(2*M_PI*sp[n-1].getRotation()/360);
          sp[n-1].setTexture(Fire);
          if (trust.getStatus() == Music::Stopped) trust.play();
        }
      }
      else
      {
        sp[n-1].setTexture(tex[n-1]);
        trust.stop();
      }
    }

    view1.setCenter(S(0,9)*5e-4,S(1,9)*5e-4);

    for (int i = 0; i < n; i++)
    {
      window.setView(view1);
      sp[i].setPosition(S(0,i)*5e-4,S(1,i)*5e-4);
      window.draw(sp[i]);
      x = S(0,i)-S(0,n-1);
      y = S(1,i)-S(1,n-1);

      theta = 2*atan(y/(sqrt(x*x+y*y)+x));
      text[i].setCharacterSize(SCRWIDTH/50);
      text[i].setPosition((4*SCRWIDTH/10)*cos(theta),(4*SCRHEIGHT/10)*sin(theta));
      window.setView(view2);
      window.draw(text[i]);
    }

    window.setView(view2);
    speed.str("");
    if(sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1))> 299192458 and VC.getStatus() == Music::Stopped)
    {
      music.stop();
      VC.play();
    }
    if(sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1))< 299192458 and VC.getStatus() == Music::Stopped and music.getStatus() == Music::Stopped)
    {
      music.play();
    }
    speed << "vitesse : " << endl << sqrt(S(2,n-1)*S(2,n-1)+S(3,n-1)*S(3,n-1)) << " m/s";
    vit.setString(speed.str().c_str());
    Acce.str("");
    Acce << "Propulsseur : " << endl << Acc << " m/s²";
    Prop.setString(Acce.str().c_str());

    window.draw(vit);
    window.draw(Prop);
    window.display();

    for(int i = 0; i < I_max; i++)
    {
      RK4(S, M, dt,deriv);
    }
  }
}

void Game2(RenderWindow& window,Music& music)
{
  Music WC;
  WC.openFromFile("Assets/Musique/WCend.wav");
  WC.setLoop(true);
  music.stop();
  WC.play();
  Font Font1;
  Font1.loadFromFile("./Assets/EarthOrbiter/earthorbiter.ttf");

  Text Prop[10];
  for (int i = 0; i < 10; i++)
  {
    Prop[i].setFont(Font1);
  }
  Prop[0].setString("Cree par : Francois Puel & Yohan Duarte");
  Prop[1].setString("Prochainement, une nouvelle version \n avec des musiques libres de droits");
  Prop[2].setString("===Commandes du jeu===");
  Prop[3].setString("Fleche droite & gauche : angle du vaisseau \n Fleches haut & bas : puissance du propulseur");
  Prop[4].setString("Chiffres de 1 a 8 : vitesse de la simulation \n");
  Prop[5].setString(" A & Z : le zoom \n R : le vaisseau s'oriente dans \n le sens contraire à sa vitesse");
  Prop[6].setString("Remerciements :");
  Prop[7].setString("CurieOsity (toujours), Les insomnies, \n L'UE de physique numerique de L3");
  Prop[8].setString("l'oeuvre de Stanley Kubrick et d'Arthur C. Clarke \n Chrono Triger le meilleur RPG sur super NES");
  Prop[9].setString("Les memes pour les easter eggs");

  int SCRWIDTH, SCRHEIGHT;
  SCRWIDTH = window.getSize().x;
  SCRHEIGHT = window.getSize().y;

  FloatRect textRect;

  for (int i = 0; i < 10; i++)
  {
    Prop[i].setCharacterSize(SCRWIDTH/30);
    Prop[i].setOutlineThickness(100);
    textRect = Prop[i].getLocalBounds();
    Prop[i].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top  + textRect.height/2.0f);
    Prop[i].setPosition(SCRWIDTH/2.0f,SCRHEIGHT*(1+i)/4.0f);
    Prop[i].setFillColor(Color::White);
    Prop[i].setStyle(Text::Regular);
  }
  int j = 0;
  while (window.isOpen())
  {
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
      return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      if(j < 0) j++;
    }
    if (Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      j = (j-1)%8;
    }


    window.clear(Color::Black);
    for (int i = 0; i < 10; i++)
    {
      Prop[i].setPosition(SCRWIDTH/2.0f,SCRHEIGHT*(1+j+i)/4.0f);
      window.draw(Prop[i]);
    }
    window.display();
    usleep(200000);
  }
}
