#ifndef MAIN_LOOP_HPP
# define MAIIN_LOOP_HPP

#include "display.hpp"
#include "logic.hpp"

class MainLoop
{
private:
  Logic logic;
  Display display;
public:
  MainLoop(Vect<2u, unsigned int> dim)
    : display(dim, logic)
  {}

  void tick()
  {
    display.render();
    logic.tick();
  }
};

#endif // !MAIN_LOOP_HPP
