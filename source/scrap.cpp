#include <iostream>
#include <algorithm>
#include "scrap.hpp"
#include "logic.hpp"

Scrap::Scrap(Vect<2u, double> const &pos, Vect<2u, double> const &speed, NanoBot::Type type)
  : pos(pos), speed(speed), type(type), isSelected(false)
{
}

void Scrap::update(std::vector<NanoBot *> const &near)
{
  pos += speed;
  speed -= pos * 0.00001;
  speed *= 0.99;
  std::for_each(near.begin(), near.end(), [this](NanoBot *n)
		{
		  speed += (n->getPos() - pos) * 0.001;
		});
}

Vect<2u, double> Scrap::getPos() const
{
  return pos;
}

Vect<2u, double> Scrap::getSpeed() const
{
  return speed;
}

NanoBot::Type Scrap::getType() const
{
  return type;
}
