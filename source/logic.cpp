#include <algorithm>
#include "logic.hpp"

const double Logic::rNear = 0.05;
const double Logic::rCollision = 0.01;

Logic::Logic()
{
  //line fight BOMBER vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05, (i / 10) * 0.05 + 0.4},
				   {-0.00 * (i % 10), 0}, true, NanoBot::BRUTE));
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 + 0.4},
				   {+0.001, 0}, false, NanoBot::BOMBER));
  //line fight BRUTE vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05, (i / 10) * 0.05 - 0.2},
				   {-0.001 * (i % 10), 0}, true, NanoBot::BRUTE));
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 - 0.2},
				   {+0.001, 0}, false, NanoBot::BRUTE));
  //line fight SHOOTER vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05, (i / 10) * 0.05 - 0.9},
				   {+0.001, 0}, true, NanoBot::SHOOTER));
  for (unsigned int i(0); i < 100; i++)
    nanoBots.push_back(new NanoBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 - 0.9},
				   {+0.001, 0}, false, NanoBot::BRUTE));
}

void Logic::tick()
{
  std::for_each(nanoBots.begin(), nanoBots.end(), [this](NanoBot *n){
      std::vector<NanoBot *> nearBots;
      std::for_each(nanoBots.begin(), nanoBots.end(), [this, n, &nearBots](NanoBot *m)
		    {
		      if (n != m && isNear(*n, *m))
			nearBots.push_back(m);
		    });
      n->tick(nearBots);
      if (n->update())
	n->action(nearBots, *this);
    });
  std::vector<NanoBot *>::iterator it(nanoBots.begin());
  while (it != nanoBots.end())
    {
      if (std::find(toDelete.begin(), toDelete.end(), *it) != toDelete.end())
	it = nanoBots.erase(it);
      else
	++it;
    }
}

void Logic::select(Vect<2u, double> coord, NanoBot::Type type)
{
  // TODO: select unit surrounding units. If type != UNKNOWN, select only units of that type.
  // set start pos to get relative move
  selectStart = coord;
}

void Logic::move(Vect<2u, double> coord)
{
  Vect<2u, double> move = coord - selectStart;
  // TODO: Each unit shouldn't move to the coord, but move rellativelly to it's offset to the original selected point.
}

std::vector<NanoBot *> const &Logic::getNanoBots() const
{
  return nanoBots;
}

bool Logic::isInRange(NanoBot const &centre, NanoBot const &other, double const ray)
{
  double dx = centre.getPos().x() - other.getPos().x();
  double dy = centre.getPos().y() - other.getPos().y();

  if (dx * dx + dy * dy < ray)
    return (true);
  else
    return (false);
}

bool Logic::isNear(NanoBot const &centre, NanoBot const &other)
{
  return (isInRange(centre, other, rNear));
}

bool Logic::isTouch(NanoBot const &centre, NanoBot const &other)
{
  return (isInRange(centre, other, rCollision));
}

void Logic::kill(NanoBot *n)
{
  toDelete.push_back(n);
  // nanoBots.erase(std::find(nanoBots.begin(), nanoBots.end(), n));
  // delete n;
}
