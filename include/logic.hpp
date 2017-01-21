#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"
# include "scrap.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
  std::vector<NanoBot *> selectedBots;
  std::vector<NanoBot *> toDelete;
  std::vector<Scrap *> scraps;
  std::vector<Scrap *> scrapsToDelete;
  Vect<2u, double> selectStart;
  std::vector<Light *> lights;
public:
  static Logic& getInstance();

  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  std::vector<Scrap *> const &getScraps() const;
  void kill(NanoBot *);
  void selectNearBots(Vect<2u, double> coord, NanoBot::Type type = NanoBot::UNKNOWN);
  void selectRect(Vect<2u, double> pos, Vect<2u, double> size);
  void destroyScrap(Scrap *);
  void moveSelection(Vect<2u, double> coord);
  void createBot(Vect<2u, double> pos, Vect<2u, double> speed, bool ally, NanoBot::Type type);
  void addLight(Light *);
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

  static constexpr double rNear = 0.05;
  static constexpr double rCollision = 0.01;

private:
  Logic();

  static Logic instance;

};

#endif
