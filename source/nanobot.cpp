#include <iostream>
#include "nanobot.hpp"
#include "logic.hpp"

NanoBot::NanoBot(Vect<2u, double> const &pos, Vect<2u, double> const &speed, bool isAlly, Type type)
  : pos(pos), speed(speed), ally(isAlly), type(type), cooldown(0)
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
  for (std::vector<NanoBot *>::iterator it(nearBots.begin()); it != nearBots.end(); ++it)
    {  
      if ((*it)->isAlly() != ally)
  	{
	  switch (type)
	    {
	    case BRUTE:
	      if ((pos - (*it)->pos).length() < 0.0002)
		{
		  std::cout << "ACTION!!" << std::endl;
		  cooldown = 100;
		  logic.kill(*it);
		}
	      break;
	    default:
	      break;
	    }
  	}
    }
}
