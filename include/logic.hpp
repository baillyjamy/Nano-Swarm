#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"
# include "scrap.hpp"
# include "laser.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
  std::vector<NanoBot *> selectedBots;
  std::vector<NanoBot *> toDelete;
  std::vector<Scrap *> scraps;
  std::vector<Scrap *> scrapsToDelete;
  std::vector<Light *> explosions;
  std::vector<Laser *> lasers;
  Vect<2u, double> selectStart;
  std::vector<Light *> lights;
  unsigned int spawnDelay;
  unsigned int level;
public:
  static Logic& getInstance();

  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  std::vector<Scrap *> const &getScraps() const;
  std::vector<Laser *> const &getLasers() const;
  void kill(NanoBot *);
  void selectNearBots(Vect<2u, double> coord, NanoBot::Type type = NanoBot::UNKNOWN);
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
  std::vector<Light *> const &getLights() const;

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
