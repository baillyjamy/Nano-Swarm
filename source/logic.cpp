#include <algorithm>
#include <iostream>
#include "logic.hpp"
#include "light.hpp"

Logic Logic::instance = Logic();

Logic::Logic()
{
  //line fight BOMBER vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05, (i / 10) * 0.05 + 0.4},
			  {-0.00 * (i % 10), 0},
			  true,
			  NanoBot::BRUTE);
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 + 0.4},
			  {+0.001, 0},
			  false,
			  NanoBot::BOMBER);
  //line fight BRUTE vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05, (i / 10) * 0.05 - 0.2},
			  {-0.001 * (i % 10), 0},
			  true,
			  NanoBot::BRUTE);
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 - 0.2},
			  {+0.001, 0},
			  false,
			  NanoBot::BRUTE);
  //line fight SHOOTER vs BRUTE
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05, (i / 10) * 0.05 - 0.9},
			  {+0.001, 0},
			  true,
			  NanoBot::SHOOTER);
  for (unsigned int i(0); i < 100; i++)
    createBot({(i % 10) * 0.05 - 0.5, (i / 10) * 0.05 - 0.9},
			  {+0.001, 0},
			  false,
			  NanoBot::BRUTE);
}

void Logic::createBot(Vect<2u, double> pos, Vect<2u, double> speed, bool ally, NanoBot::Type type)
{
  Light *l = new Light(Light{{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0.05f});
  addLight(l);
  nanoBots.push_back(new NanoBot(pos,
				 speed,
				 ally,
				 type,
				 l));
}

Logic& Logic::getInstance()
{
  return instance;
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
	{
	  scraps.push_back(new Scrap((*it)->getPos(), (*it)->getSpeed(), (*it)->getType()));
	  it = nanoBots.erase(it);
	}
      else
	++it;
    }

  std::for_each(scraps.begin(), scraps.end(), [this](Scrap *r){
      r->update();
    });
  std::vector<Scrap *>::iterator it_r(scraps.begin());
  while (it_r != scraps.end())
    {
      if (std::find(scrapsToDelete.begin(), scrapsToDelete.end(), *it_r) != scrapsToDelete.end())
	it_r = scraps.erase(it_r);
      else
	++it_r;
    }
}

void Logic::selectRect(Vect<2u, double> start, Vect<2u, double> end)
{
  std::for_each(nanoBots.begin(), nanoBots.end(), [this, start, end](NanoBot *bot)
		{
		  if (bot->isAlly())
		    {
		      if (bot->getPos().x() >= start.x() && bot->getPos().x() <= end.x() &&
			  bot->getPos().y() >= start.y() && bot->getPos().y() <= end.y())
			{
			  bot->setSelection(true);
			}
		      else
			{
			  bot->setSelection(false);
			}
		      return;
		    }
		});
}

void Logic::selectNearBots(Vect<2u, double> coord, NanoBot::Type type)
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
  removeLight(n->getLight());
  toDelete.push_back(n);
}

void Logic::destroyScrap(Scrap *r)
{
  scrapsToDelete.push_back(r);
}


void Logic::addLight(Light *l)
{
  lights.push_back(l);
}

void Logic::removeLight(Light *l)
{
  std::vector<Light *>::iterator pos = std::find(lights.begin(), lights.end(), l);

  if (pos != lights.end())
    lights.erase(pos);
}

std::vector<Light *> const &Logic::getLights() const
{
  return lights;
}
