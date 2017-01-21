#include <algorithm>
#include "logic.hpp"

const double Logic::rNear = 0.1;
const double Logic::rCollision = 0.01;

Logic::Logic()
{
}

void Logic::tick()
{
  std::for_each(nanobots.begin(), nanobots.end(), [](NanoBot *n){
      n->update();
    });
}

bool Logic::isInRange(NanoBot centre, NanoBot other, double const ray)
{
  double dx = centre.getPos()[0] - other.getPos()[0];
  double dy = centre.getPos()[1] - other.getPos()[1];

  if (dx * dx + dy * dy < ray)
    return (true);
  else
    return (false);
}

bool Logic::isNear(NanoBot centre, NanoBot other)
{
  return (isInRange(centre, other, rNear));
}

bool Logic::isTouch(NanoBot centre, NanoBot other)
{
  return (isInRange(centre, other, rCollision));
}
