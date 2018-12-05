#include "Headers/Forces.hpp"
#include "Headers/RK4.hpp"
#include "Headers/games.hpp"

int main()
{
  int windowSizeX, windowSizeY;
  windowSizeX = VideoMode::getDesktopMode().width;
  windowSizeY = VideoMode::getDesktopMode().height;
  RenderWindow window(VideoMode(windowSizeX, windowSizeY),
                        "2001 a space odyssey",
                        Style::Fullscreen);
  window.setFramerateLimit(60);

  Music music;
  music.openFromFile("Assets/Musique/304COT.wav");
  music.setLoop(true);
  music.play();

  SoundBuffer buffer;
  buffer.loadFromFile("Assets/Musique/beep-up.wav");
  Sound sound;
  sound.setBuffer(buffer);
  sound.setVolume(50);

  int j;
  EScreen(window);
  sound.play();
  usleep(250000);
  window.clear(Color::Black);
  j = CScreen(window, sound);
  sound.play();
  if(j == 0) Game0(window);
  if(j == 1) Game1(window);
  if(j == 2) Game2(window);

  return 0;
}
