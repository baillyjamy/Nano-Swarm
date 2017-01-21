#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
public:
  Logic();
  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
  bool isInRange(NanoBot centre, NanoBot other, double const ray);
  bool isNear(NanoBot centre, NanoBot other);
  bool isTouch(NanoBot centre, NanoBot other);

  static const double rNear;
  static const double rCollision;
};

#endif
