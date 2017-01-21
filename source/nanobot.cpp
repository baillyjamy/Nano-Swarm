#include "nanobot.hpp"

NanoBot::NanoBot(Vect<2u, double> const &pos, Vect<2u, double> const &speed)
  : pos(pos), speed(speed)
{
}

void NanoBot::update()
{
  pos += speed;
}

Vect<2u, double> NanoBot::getPos()
{
  return pos;
}

Vect<2u, double> NanoBot::getSpeed()
{
  return speed;
}

bool NanoBot::isEnemy()
{
  return enemy;
}
