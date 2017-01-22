#ifndef NANOBOT_HPP_
# define NANOBOT_HPP_

# include <vector>
# include "vect.hpp"

class Logic;
class Light;
class Scrap;

class NanoBot
{
public:
  enum Type
    {
      WORKER = 0,
      BRUTE = 1,
      SHOOTER = 2,
      BOMBER = 3,
      UNKNOWN = 4,
    };

  static constexpr const Vect<3u, double> botColors[UNKNOWN] = {
    {0.0, 0.5, 0.5},
    {1.0, 0.25, 0.0},
    {0.25, 0.0, 1.0},
    {1.0, 1.0, 1.0},
  };

private:
  Vect<2u, double> pos;
  Vect<2u, double> speed;
  bool ally;
  Type type;
  unsigned int cooldown;
  bool selected;
  Light *light;
  Vect<2u, double> target;

public:
  NanoBot(Vect<2u, double> const &, Vect<2u, double> const &, bool isAlly, Type type, Light *light);
  bool update();
  Vect<2u, double> getPos() const;
  Vect<2u, double> getSpeed() const;
  bool isAlly() const;
  bool isSelected() const;
  void setSelection(bool selected);
  Type getType() const;
  void setCooldown(unsigned int);
  void tick(std::vector<NanoBot *> &nearBots);
  void action(std::vector<NanoBot *> &nearBots, std::vector<Scrap *> &nearScraps, Logic &logic);
  Light *getLight();
  void move(Vect<2u, double> target);

private:
  void workerAction(std::vector<Scrap *> &nearScraps, Logic &logic);
  void bruteAction(std::vector<NanoBot *> &nearBots, Logic &logic);
  void shooterAction(std::vector<NanoBot *> &nearBots, Logic &logic);
  void bomberAction(std::vector<NanoBot *> &nearBots, Logic &logic);
};

namespace WORKER
{
  constexpr double collectRange = 0.01;
  constexpr double cooldown = 180;
}

namespace BRUTE
{
  constexpr double attackRange = 0.01;
  constexpr double cooldown = 60;
}

namespace SHOOTER
{
  constexpr double attackRange = 0.05;
  constexpr double cooldown = 300;
}

namespace BOMBER
{
  constexpr double attackRange = 0.01;
  constexpr double explosionRange = 0.06;
}

#endif
