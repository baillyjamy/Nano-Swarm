#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"
# include "remain.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
  std::vector<NanoBot *> toDelete;
  std::vector<Remain *> remains;
  std::vector<Remain *> remainsToDelete;
  Vect<2u, double> selectStart;
public:
  Logic();
  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  bool isInRange(NanoBot const &centre, NanoBot const &other, double const ray);
  bool isNear(NanoBot const &centre, NanoBot const &other);
  bool isTouch(NanoBot const &centre, NanoBot const &other);
  void kill(NanoBot *);
  void destroyRemain(Remain *);
  void select(Vect<2u, double> coord, NanoBot::Type type = NanoBot::UNKNOWN);
  void move(Vect<2u, double> coord);
  static const double rNear;
  static const double rCollision;
};

#endif
