#include <iostream>
#include "music.hpp"

Music Music::instance = Music();

Music::Music() : mainMusic(), explosionSound()
{
  if (!mainMusic.openFromFile("sound/background_music.ogg"))
    {
      std::cerr << "Music not charged" << std::endl;
      exit(-1);
    }

  if (!explosionSound.loadFromFile("sound/explosion.wav"))
    {
      std::cerr << "Sound buffer not charged: explosion" << std::endl;
      exit(-1);
    }
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

sf::Sound *Music::playExplosionSound()
{
  sf::Sound * sound = new sf::Sound();
  sound->setBuffer(explosionSound);
  sound->setLoop(false);
  sound->setVolume(40);
  sound->play();
  return sound;
}
