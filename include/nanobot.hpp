#ifndef NANOBOT_HPP_
# define NANOBOT_HPP_

# include <vector>
# include "vect.hpp"

class Logic;

class NanoBot
{
public:
  enum Type
    {
      WORKER,
      BRUTE,
      SHOOTER,
      BOMBER,
      UNKNOWN,
    };
private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;
  bool ally;
  Type type;
  unsigned int cooldown;

  bool isSelected;

public:
  NanoBot(Vect<2u, double> const &, Vect<2u, double> const &, bool isAlly, Type type);
  bool update();
  Vect<2u, double> getPos() const;
  Vect<2u, double> getSpeed() const;
  bool isAlly() const;
  Type getType() const;
  void setCooldown(unsigned int);
  void tick(std::vector<NanoBot *> &nearBots);
  void action(std::vector<NanoBot *> &nearBots, Logic &);

private:
  // returns true if the nanobot died during his action
  void bruteAction(std::vector<NanoBot *> &nearBots, Logic &logic);
  void shooterAction(std::vector<NanoBot *> &nearBots, Logic &logic);
  void bomberAction(std::vector<NanoBot *> &nearBots, Logic &logic);
};

namespace BRUTE
{
  constexpr double attackRange = 0.0002;
  constexpr double cooldown = 100;
}

namespace SHOOTER
{
  constexpr double attackRange = 0.05;
  constexpr double cooldown = 300;
}

namespace BOMBER
{
  constexpr double attackRange = 0.0002;
  constexpr double explosionRange = 0.003;
}

#endif
