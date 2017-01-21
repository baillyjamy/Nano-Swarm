#include <iostream>
#include "nanobot.hpp"
#include "logic.hpp"
#include "light.hpp"

constexpr const Vect<3u, double> NanoBot::botColors[NanoBot::UNKNOWN];

NanoBot::NanoBot(Vect<2u, double> const &pos, Vect<2u, double> const &speed, bool isAlly, Type type, Light *light)
  : pos(pos), speed(speed), ally(isAlly), type(type), cooldown(0), selected(false), light(light), target(pos)
{
}

bool NanoBot::update()
{
  constexpr double const maxAccel = 0.001;

  Vect<2u, double> delta(target - pos);

  if (delta.scalar(delta) > maxAccel)
    {
      if (delta.scalar(delta) > maxAccel * maxAccel)
	{
	  delta = delta.normalized() * maxAccel;
	}
      speed += delta;
    }


  // speed += pos * 0.005;

  pos += speed;
  light->center = pos;
  light->color = !ally ? Vect<4u, float>{1.0, 0.5, 0.5, 1.0}
  : (selected ? Vect<4u, float>{1.0, 1.0, 0.5, 1.0}
  : Vect<4u, float>{0.5, 1.0, 0.5, 1.0});
  speed *= 0.9;
  return !(cooldown -= !!cooldown);
}

Vect<2u, double> NanoBot::getPos() const
{
  return pos;
}

Vect<2u, double> NanoBot::getSpeed() const
{
  return speed;
}

void NanoBot::move(Vect<2u, double> target)
{
  this->target = target;
}

bool NanoBot::isSelected() const
{
  return selected;
}

void NanoBot::setSelection(bool selected)
{
  if (ally)
    this->selected = selected;
}

bool NanoBot::isAlly() const
{
  return ally;
}

NanoBot::Type NanoBot::getType() const
{
  return type;
}

void NanoBot::setCooldown(unsigned int delay)
{
  cooldown = delay;
}

void NanoBot::tick(std::vector<NanoBot *> &nearBots)
{
  (void)nearBots;
  // Code to seperate nanobots that does not work
  // Vect<2u, double> dir{0.0, 0.0};

  // for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
  //   {
  //     if ((*it)->isAlly() == ally && (*it)->getType() == type)
  // 	{
  // 	  Vect<2u, double> posDelta(pos - (*it)->pos);
  // 	  Vect<2u, double> speedDelta(speed - (*it)->speed);
  // 	  double coef = posDelta.scalar(posDelta) - 0.01;

  // 	  coef = coef > 0.01 ? 1 / coef : coef;
  // 	  //	  if (coef < 0.0001)
  // 	  dir -= posDelta * coef;
  // 	}
  //   }
  // if (dir.length() > 0.0001 * 0.0001)
  //   dir = dir.normalized() * 0.0001;
  // speed += dir;

  //  speed -= pos * 0.000001;

  Vect<2u, double> dir{0.0, 0.0};

  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((*it)->isAlly() == ally && (*it)->getType() == type)
  	{
  	  Vect<2u, double> posDelta(pos - (*it)->pos);
  	  Vect<2u, double> speedDelta(speed - (*it)->speed);
  	  double coef = posDelta.scalar(posDelta) - 0.01;

  	  coef = coef > 0.01 ? 1 / coef : coef;
  	  //	  if (coef < 0.0001)
  	  dir += speedDelta * 0.005;
	  dir += posDelta * 0.0001;
  	}
    }

  constexpr double const maxAccel = 0.002;

  if (dir.length() > maxAccel * maxAccel)
    dir = dir.normalized() * maxAccel;
  speed += dir;

   speed -= pos * 0.000001;
}

void NanoBot::action(std::vector<NanoBot *> &nearBots, std::vector<Scrap *> &nearScraps, Logic &logic)
{
  // returns true if the nanobot died during his action
  switch (type)
    {
    case WORKER:
      workerAction(nearScraps, logic);
      break;
    case BRUTE:
      bruteAction(nearBots, logic);
      break;
    case SHOOTER:
      shooterAction(nearBots, logic);
      break;
    case BOMBER:
      bomberAction(nearBots, logic);
      break;
    default:
      break;
    }
}

void NanoBot::workerAction(std::vector<Scrap *> &nearScraps, Logic &logic)
{
  Scrap *firstWorker = nullptr;
  Scrap *firstBrute = nullptr;
  Scrap *firstShooter = nullptr;
  Scrap *firstBomber = nullptr;

  for (std::vector<Scrap *>::iterator it(nearScraps.begin()); it != nearScraps.end(); ++it)
    {
      if ((pos - (*it)->getPos()).length() < WORKER::collectRange)
	{
	  switch ((*it)->getType())
	    {
	    case WORKER:
	      if (firstWorker != nullptr)
		{
		  logic.createBot(pos,
			    {0, 0},
			    true,
			    NanoBot::WORKER);
		  logic.destroyScrap(firstWorker);
		  logic.destroyScrap((*it));
		  firstWorker = nullptr;
		}
	      else
		firstWorker = *it;
	      break;
	    case BRUTE:
	      if (firstBrute != nullptr)
		{
		  logic.createBot(pos,
				  {0, 0},
				  true,
				  NanoBot::BRUTE);
		  logic.destroyScrap(firstBrute);
		  logic.destroyScrap((*it));
		  firstBrute = nullptr;
		}
	      else
		firstBrute = *it;
	      break;
	    case SHOOTER:
	      if (firstShooter != nullptr)
		{
		  logic.createBot(pos,
				  {0, 0},
				  true,
				  NanoBot::SHOOTER);
		  logic.destroyScrap(firstShooter);
		  logic.destroyScrap((*it));
		  firstShooter = nullptr;
		}
	      else
		firstShooter = *it;
	      break;
	    case BOMBER:
	      if (firstBomber != nullptr)
		{
		  logic.createBot(pos,
				  {0, 0},
				  true,
				  NanoBot::BOMBER);
		  logic.destroyScrap(firstBomber);
		  logic.destroyScrap((*it));
		  firstBomber = nullptr;
		}
	      else
		firstBomber = *it;
	      break;
	    default:
	      break;
	    }
	}
    }
}

void NanoBot::bruteAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((*it)->isAlly() != ally && (pos - (*it)->pos).length() < BRUTE::attackRange)
	{
	  cooldown = BRUTE::cooldown;
	  logic.kill(*it);
	}
    }
}

void NanoBot::shooterAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((*it)->isAlly() != ally && (pos - (*it)->pos).length() < SHOOTER::attackRange)
	{
	  cooldown = SHOOTER::cooldown;
	  logic.kill(*it);
	}
    }
}

void NanoBot::bomberAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((pos - (*it)->pos).length() < BOMBER::attackRange)
	{
	  // kill every nanobot in range
	  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
	    {
	      if ((pos - (*it)->pos).length() < BOMBER::explosionRange)
		logic.kill(*it);
	    }

	  // kill himself
	  logic.kill(this);
	  return;
	}
    }
}

Light *NanoBot::getLight()
{
  return light;
}
