#ifndef REMAIN_HPP_
# define REMAIN_HPP_

# include <vector>
# include "vect.hpp"

class Logic;

class Remain
{
private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;
  unsigned int cooldown;

  bool isSelected;

public:
  Remain(Vect<2u, double> const &, Vect<2u, double> const &);
  bool update();
  Vect<2u, double> getPos() const;
  Vect<2u, double> getSpeed() const;
  void setCooldown(unsigned int);
  void tick(std::vector<Remain *> &nearBots);
  void action(Logic &);
};

#endif
