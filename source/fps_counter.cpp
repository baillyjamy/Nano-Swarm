#include <ctime>
#include <iostream>
#include "fps_counter.hpp"

FPSCounter::FPSCounter()
  : last(time(nullptr)),
    frames(0)
{
}

void FPSCounter::tick()
{
  frames++;
  if (time(nullptr) - last >= 1)
    {
      std::cout << "FPS:" << frames << std::endl;
      frames = 0;
      last = time(nullptr);
    }
}
