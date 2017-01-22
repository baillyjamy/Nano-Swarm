#ifndef MAIN_LOOP_HPP
# define MAIIN_LOOP_HPP

#include "display.hpp"
#include "logic.hpp"

#define WIDTH 1920
#define HEIGHT 1080

class MainLoop
{
private:
  Logic& logic;
  Display display;
public:
  MainLoop(Vect<2u, unsigned int> dim);

  bool tick();
};

#endif // !MAIN_LOOP_HPP
