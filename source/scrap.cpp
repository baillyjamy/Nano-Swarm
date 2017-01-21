#include <iostream>
#include "scrap.hpp"
#include "logic.hpp"

Scrap::Scrap(Vect<2u, double> const &pos, Vect<2u, double> const &speed)
  : pos(pos), speed(speed), isSelected(false)
{
}

bool Scrap::update()
{
  return !(false);
}

Vect<2u, double> Scrap::getPos() const
{
  return pos;
}

Vect<2u, double> Scrap::getSpeed() const
{
  return speed;
}
