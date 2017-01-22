#include <algorithm>
#include <iostream>
#include <cmath>
#include "logic.hpp"
#include "light.hpp"

Logic Logic::instance = Logic();

Logic::Logic()
{
  spawnDelay = 0;
  level = 0;
  //line fight BOMBER vs BRUTE
  for (unsigned int i(0); i < 20; i++)
    createBot({(i % 10) * 0.05 - 0.12, (i / 10) * 0.05 + 0.4},
	      {0, 0},
	      true,
	      NanoBot::BRUTE);
  for (unsigned int i(0); i < 20; i++)
    createBot({(i % 10) * 0.05 - 0.12, (i / 10) * 0.05},
	      {0, 0},
	      true,
	      NanoBot::WORKER);
  for (unsigned int i(0); i < 20; i++)
    createBot({(i % 10) * 0.05 - 0.12, (i / 10) * 0.05 - 0.9},
	      {0, 0},
	      true,
	      NanoBot::SHOOTER);
}

NanoBot *Logic::createBot(Vect<2u, double> pos, Vect<2u, double> speed, bool ally, NanoBot::Type type)
{
  Light *l = new Light(Light{{0.0f, 0.0f},
	{!ally ? Vect<4u, float>{0.5f, 0.5f, 0.5f, 1.0f} :
	  (Vect<4u, float>{1.0f, 1.0f, 1.0f, 1.0f})},
	  0.05f});
  addLight(l);
  NanoBot *n = new NanoBot(pos, speed, ally, type, l);

  nanoBots.push_back(n);
  return n;
}

Logic& Logic::getInstance()
{
  return instance;
}

void Logic::updateNanoBots()
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
	  addExplosion(new Light{(*it)->getPos(), {5.0, 5.0, 1.0, 1.0}, 0.1});
	  scraps.push_back(new Scrap((*it)->getPos(), (*it)->getSpeed(), (*it)->getType()));
	  it = nanoBots.erase(it);
	}
      else
	++it;
    }
}

void Logic::updateScraps()
{
  std::for_each(scraps.begin(), scraps.end(), [this](Scrap *r){
      std::vector<NanoBot *> nearBots;
      std::for_each(nanoBots.begin(), nanoBots.end(), [this, r, &nearBots](NanoBot *m)
		    {
		      if (m->getType() == NanoBot::WORKER && isNear(*r, *m))
			nearBots.push_back(m);
		    });
      r->update(nearBots);
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

void Logic::spawnEnemies()
{
  Vect<2u, double> spawnCenter(sin(level * level), cos(level * level));

  spawnCenter *= 2.0;
  for (unsigned int i(0); i < (10 + level) / 3; i++)
    createBot(Vect<2u, double>{(i % 5) * 0.05, (i / 5) * 0.05} + spawnCenter,
	      {0, 0},
	      false,
	      static_cast<NanoBot::Type>(level % NanoBot::Type::UNKNOWN))
      ->move(Vect<2u, double>{sin(level) * 0.9, cos(level * level * level) * 0.9}
	     + Vect<2u, double>{(i % 5) * 0.05, (i / 5) * 0.05});
}

void Logic::tick()
{
  if (spawnDelay == 0)
    {
      ++level;
      spawnEnemies();
      spawnDelay = 15000 / (level + 50);
    }
  else
    --spawnDelay;
  updateNanoBots();
  updateScraps();
  updateExplosions();
  updateLasers();
}

void Logic::updateExplosions()
{
  std::vector<Light *>::iterator it(explosions.begin());
  while (it != explosions.end())
    {
      (*it)->color[3] -= 0.2;
      (*it)->radius += 0.05;
      if ((*it)->color[3] <= 0)
	{
	  removeLight(*it);
	  it = explosions.erase(it);
	}
      else
	++it;
    }
}

void Logic::addExplosion(Light *l)
{
  explosions.push_back(l);
  lights.push_back(l);
}


void Logic::updateLasers()
{
  std::vector<Laser *>::iterator it(lasers.begin());

  while (it != lasers.end())
    {
      (*it)->power -= 0.1;
      if ((*it)->power <= 0)
	{
	  delete *it;
	  it = lasers.erase(it);
	}
      else
	++it;
    }
}

void Logic::addLaser(Laser *l)
{
  lasers.push_back(l);
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
	    }
	  else
	    bot->setSelection(false);
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
	it++;
    }
}

void Logic::selectAllBots(Vect<4u, bool> keyPressed)
{
  // clear selection
  std::for_each(selectedBots.begin(), selectedBots.end(), [] (NanoBot *bot) {
      bot->setSelection(false);
    });
  selectedBots.clear();

  std::for_each(nanoBots.begin(), nanoBots.end(), [this, keyPressed] (NanoBot *bot){
      if (bot->isAlly() && (keyPressed == Vect<4u, bool>(false, false, false, false) ||
			    keyPressed[bot->getType()]))
	{
	  bot->setSelection(true);
	  selectedBots.push_back(bot);
	}
    });
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

std::vector<Laser *> const &Logic::getLasers() const
{
  return lasers;
}
