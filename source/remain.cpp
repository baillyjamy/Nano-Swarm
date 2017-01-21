#include <iostream>
#include "remain.hpp"
#include "logic.hpp"

Remain::Remain(Vect<2u, double> const &pos, Vect<2u, double> const &speed)
  : pos(pos), speed(speed), cooldown(0), isSelected(false)
{
}

bool Remain::update()
{
  return !(cooldown -= !!cooldown);
}

Vect<2u, double> Remain::getPos() const
{
  return pos;
}

Vect<2u, double> Remain::getSpeed() const
{
  return speed;
}

void Remain::setCooldown(unsigned int delay)
{
  cooldown = delay;
}

void Remain::action(Logic &logic)
{
  cooldown = 1000;
  logic.destroyRemain(this);
}
