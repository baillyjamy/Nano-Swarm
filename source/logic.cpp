#include <algorithm>
#include "logic.hpp"

Logic::Logic()
{
}

void Logic::tick()
{
  std::for_each(nanobots.begin(), nanobots.end(), [](NanoBot *n){
      n->update();
    });
}
