#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "nanobot.hpp"

class Logic
{
private:
  std::vector<NanoBot *> nanoBots;
public:
  Logic();
  void tick();
  std::vector<NanoBot *> const &getNanoBots() const;
};

#endif
