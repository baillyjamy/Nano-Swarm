#include <iostream>
#include "nanobot.hpp"
#include "logic.hpp"
#include "light.hpp"

NanoBot::NanoBot(Vect<2u, double> const &pos, Vect<2u, double> const &speed, bool isAlly, Type type, Light *light)
  : pos(pos), speed(speed), ally(isAlly), type(type), cooldown(0), selected(false), light(light)
{
}

bool NanoBot::update()
{
  pos += speed;
  light->center = pos;
  light->color = !ally ? Vect<4u, float>{1.0, 0.5, 0.5, 1.0}
  : (selected ? Vect<4u, float>{1.0, 1.0, 0.5, 1.0}
  : Vect<4u, float>{0.5, 1.0, 0.5, 1.0});
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
      if ((*it)->isAlly() != ally && (pos - (*it)->pos).length() < BRUTE::attackRange)
	{
	  cooldown = BRUTE::cooldown;
	  Type ennemy = (*it)->getType();
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
