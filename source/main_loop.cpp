#include "main_loop.hpp"

MainLoop::MainLoop(Vect<2u, unsigned int> dim)
  : logic(Logic::getInstance()), display(dim, logic)
{
}

void MainLoop::tick()
{
  display.render();
  logic.tick();
}
