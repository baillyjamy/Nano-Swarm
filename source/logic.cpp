#include <algorithm>
#include "logic.hpp"

Logic::Logic()
{
  for (unsigned int i(0); i < 100; i++)
    {
      nanoBots.push_back(new NanoBot({(i % 10) * 0.02, (i / 10) * 0.02}, {0.01, 0.0001 * i}));
    }
}

void Logic::tick()
{
  std::for_each(nanoBots.begin(), nanoBots.end(), [](NanoBot *n){
      n->update();
    });
}

std::vector<NanoBot *> const &Logic::getNanoBots() const
{
  return nanoBots;
}
