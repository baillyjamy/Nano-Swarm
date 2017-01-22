#include <iostream>
#include "music.hpp"

Music Music::instance = Music();

Music::Music() : mainMusic(), explosionSound()
{
  if (!mainMusic.openFromFile("background_music.ogg"))
    {
      std::cerr << "Music not charged" << std::endl;
      exit(-1);
    }

  // if (!explosionSound.loadFromFile("sound.wav"))
  //   {
  //     std::cerr << "Sound buffer not charged: explosion" << std::endl;
  //     exit(-1);
  //   }
}

Music& Music::getInstance()
{
  return instance;
}

void Music::playMainMusic()
{
  mainMusic.setLoop(true);
  mainMusic.setVolume(40);
  mainMusic.play();
}

void Music::playExplosionSound()
{
  sf::Sound sound;
  sound.setBuffer(explosionSound);
  sound.setLoop(false);
  sound.setVolume(40);
  sound.play();
}
