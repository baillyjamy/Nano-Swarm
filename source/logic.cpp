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
	      NanoBot::BRUTE);
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
      std::vector<Scrap *> nearScraps;
      std::for_each(scraps.begin(), scraps.end(), [this, n, &nearScraps](Scrap *o)
		    {
		      if (isNear(*o, *n))
			nearScraps.push_back(o);
		    });
      if (n->update())
	n->action(nearBots, nearScraps, *this);
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

void Logic::selectRect(Vect<2u, double> start, Vect<2u, double> end, Vect<4u, bool> keyPressed)
{
  selectedBots.clear();
  std::for_each(nanoBots.begin(), nanoBots.end(), [this, start, end, keyPressed](NanoBot *bot){
      if (bot->isAlly())
	{
	  if (bot->getPos().x() >= start.x() && bot->getPos().x() <= end.x() &&
	      bot->getPos().y() >= start.y() && bot->getPos().y() <= end.y() &&
	      (keyPressed == Vect<4u, bool>(false, false, false, false) || keyPressed[bot->getType()]))
	    {
	      bot->setSelection(true);
	      selectedBots.push_back(bot);
	      // std::cout << "selected" << std::endl;
	    }
	  else
	    {
	      bot->setSelection(false);
	    }
	}
    });
}

void Logic::refreshSelection(Vect<4u, bool> keyPressed)
{
  std::vector<NanoBot *>::iterator it = selectedBots.begin();
  while (it != selectedBots.end())
    {
      if (keyPressed != Vect<4u, bool>(false, false, false, false) && !keyPressed[(*it)->getType()])
	{
	  (*it)->setSelection(false);
	  it = selectedBots.erase(it);
	}
      else
	{
	  it++;
	}
    }
}

void Logic::selectNearBots(Vect<2u, double> coord, NanoBot::Type type)
{
  // TODO: select unit surrounding units. If type != UNKNOWN, select only units of that type.
  // set start pos to get relative move
  selectStart = coord;
}

void Logic::moveSelection(Vect<2u, double> target)
{
  if (selectedBots.empty())
    return;

  Vect<2u, double> averagePos(0, 0);

  std::for_each(selectedBots.begin(), selectedBots.end(), [&averagePos](NanoBot *bot) {
      averagePos += bot->getPos();
    });
  averagePos /= selectedBots.size();

  std::for_each(selectedBots.begin(), selectedBots.end(), [target, &averagePos](NanoBot *bot) {
      Vect<2u, double> offset(bot->getPos() - averagePos);
      bot->move(offset / 2 + target);
      // bot->move(target);
    });
}

std::vector<NanoBot *> const &Logic::getNanoBots() const
{
  return nanoBots;
}

std::vector<Scrap *> const &Logic::getScraps() const
{
  return scraps;
}

void Logic::kill(NanoBot *n)
{
  removeLight(n->getLight());
  toDelete.push_back(n);
  // remove if selected
  std::vector<NanoBot *>::iterator it = std::find(selectedBots.begin(), selectedBots.end(), n);
  if (it != selectedBots.end())
    selectedBots.erase(it);
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
