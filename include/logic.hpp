#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <SFML/Audio.hpp>
# include <string>
# include <vector>
# include "nanobot.hpp"
# include "scrap.hpp"
# include "laser.hpp"
# include "score.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
  std::vector<NanoBot *> selectedBots;
  std::vector<Scrap *> scraps;
  std::vector<Scrap *> scrapsToDelete;
  std::vector<Light *> explosions;
  std::vector<Laser *> lasers;
  Vect<2u, double> selectStart;
  std::vector<Light *> lights;
  unsigned int spawnDelay;
  unsigned int level;
  bool endGame;
  Score score;
  unsigned int nbAlly;
  std::vector<sf::Sound *> explosionSounds;
public:
  static Logic& getInstance();

  bool tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  std::vector<Scrap *> const &getScraps() const;
  std::vector<Laser *> const &getLasers() const;
  std::vector<Light *> const &getLights() const;
  Score const& getScore() const;
  void kill(NanoBot *);
  void selectAllBots(Vect<4u, bool> keyPressed);
  void selectRect(Vect<2u, double> pos, Vect<2u, double> size, Vect<4u, bool> keyPressed);
  void refreshSelection(Vect<4u, bool> keyPressed);
  void destroyScrap(Scrap *);
  void moveSelection(Vect<2u, double> coord);
  NanoBot *createBot(Vect<2u, double> pos, Vect<2u, double> speed, bool ally, NanoBot::Type type);
  void addLight(Light *);
  void addExplosion(Light *);
  void addLaser(Laser *);
  void updateNanoBots();
  void updateScraps();
  void updateExplosions();
  void updateLasers();
  void spawnEnemies();
  void removeLight(Light *);
  bool checkEndGame();
  void deleteSounds();

  template <typename T>
  bool isInRange(T const &centre, NanoBot const &other, double const ray) {
    double dx = centre.getPos().x() - other.getPos().x();
    double dy = centre.getPos().y() - other.getPos().y();

    return dx * dx + dy * dy < ray;
  }

  template <typename T>
  bool isNear(T const &centre, NanoBot const &other) {
    return isInRange(centre, other, rNear);
  }

  template <typename T>
  bool isTouch(T const &centre, NanoBot const &other) {
    return isInRange(centre, other, rCollision);
  }

  static constexpr double const rNear = 0.05;
  static constexpr double const rCollision = 0.01;

private:
  Logic();

  static Logic instance;

};

#endif
