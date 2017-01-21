#include <iostream>
#include "nanobot.hpp"
#include "logic.hpp"

NanoBot::NanoBot(Vect<2u, double> const &pos, Vect<2u, double> const &speed, bool isAlly, Type type)
  : pos(pos), speed(speed), ally(isAlly), type(type), cooldown(0), selected(false)
{
}

bool NanoBot::update()
{
  pos += speed;
  speed *= 0.999;
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

bool NanoBot::isSelected() const
{
  return selected;
}

void NanoBot::setSelection(bool selected)
{
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

  speed -= pos * 0.000001;
}

void NanoBot::action(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  // returns true if the nanobot died during his action
  switch (type)
    {
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

void NanoBot::bruteAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((*it)->isAlly() != ally)
	{
	  if ((pos - (*it)->pos).length() < BRUTE::attackRange)
	    {
	      std::cout << "ACTION!!" << std::endl;
	      cooldown = BRUTE::cooldown;
	      Type ennemy = (*it)->getType();
	      logic.kill(*it);
	      if (ennemy == BRUTE)
		{
		  logic.kill(this);
		  return;
		}
	    }
	}
    }
}

void NanoBot::shooterAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((*it)->isAlly() != ally)
	{
	  if ((pos - (*it)->pos).length() < SHOOTER::attackRange)
	    {
	      std::cout << "SHOOT!!" << std::endl;
	      cooldown = SHOOTER::cooldown;
	      logic.kill(*it);
	    }
	}
    }
}

void NanoBot::bomberAction(std::vector<NanoBot *> &nearBots, Logic &logic)
{
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {
      if ((pos - (*it)->pos).length() < BOMBER::attackRange)
	{
	  std::cout << "BOMBER!!" << std::endl;

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
