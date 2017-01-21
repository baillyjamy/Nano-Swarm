#ifndef NANOBOT_HPP_
# define NANOBOT_HPP_

# include "vect.hpp"

class NanoBot
{
private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;
  bool enemy;
public:
  NanoBot(Vect<2u, double> const &, Vect<2u, double> const &);
  void update();
  Vect<2u, double> getPos();
  Vect<2u, double> getSpeed();
  bool isEnemy();
};

#endif
