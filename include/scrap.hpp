#ifndef SCRAP_HPP_
# define SCRAP_HPP_

# include <vector>
# include "vect.hpp"
# include "nanobot.hpp"

class Logic;

class Scrap
{
private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;

  NanoBot::Type type;
  bool isSelected;

public:
  Scrap(Vect<2u, double> const &, Vect<2u, double> const &, NanoBot::Type type);
  bool update();
  Vect<2u, double> getPos() const;
  Vect<2u, double> getSpeed() const;
  NanoBot::Type getType() const;
  void setCooldown(unsigned int);
  void tick(std::vector<Scrap *> &nearBots);
};

#endif
