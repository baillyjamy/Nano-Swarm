#ifndef SCRAP_HPP_
# define SCRAP_HPP_

# include <vector>
# include "vect.hpp"

class Logic;

class Scrap
{
private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;

  bool isSelected;

public:
  Scrap(Vect<2u, double> const &, Vect<2u, double> const &);
  bool update();
  Vect<2u, double> getPos() const;
  Vect<2u, double> getSpeed() const;
  void setCooldown(unsigned int);
  void tick(std::vector<Scrap *> &nearBots);
};

#endif
