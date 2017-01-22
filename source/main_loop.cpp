#include "main_loop.hpp"

MainLoop::MainLoop(Vect<2u, unsigned int> dim)
  : logic(Logic::getInstance()), display(dim, logic)
{
}

bool MainLoop::tick()
{
  display.render();
  return logic.tick();
}
