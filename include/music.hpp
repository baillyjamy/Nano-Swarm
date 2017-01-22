#ifndef MUSIC_HPP_
# define MUSIC_HPP_

# include <SFML/Audio.hpp>

class Music
{
public:
  static Music& getInstance();

  void playMainMusic();
  sf::Sound *playExplosionSound();

private:
  Music();
  Music(Music const& other);

  static Music instance;

  sf::Music mainMusic;
  sf::SoundBuffer explosionSound;
};

#endif /* !MUSIC_HPP_ */
