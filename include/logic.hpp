#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"
# include "scrap.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
  std::vector<NanoBot *> toDelete;
  std::vector<Scrap *> scraps;
  std::vector<Scrap *> scrapsToDelete;
  Vect<2u, double> selectStart;
public:
  static Logic& getInstance();

  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  bool isInRange(NanoBot const &centre, NanoBot const &other, double const ray);
  bool isNear(NanoBot const &centre, NanoBot const &other);
  bool isTouch(NanoBot const &centre, NanoBot const &other);
  void kill(NanoBot *);
  void selectNearBots(Vect<2u, double> coord, NanoBot::Type type = NanoBot::UNKNOWN);
  void selectRect(Vect<2u, double> pos, Vect<2u, double> size);
  void destroyScrap(Scrap *);
  void move(Vect<2u, double> coord);

  static constexpr double rNear = 0.05;
  static constexpr double rCollision = 0.01;

private:
  Logic();

  static Logic instance;

};

#endif
