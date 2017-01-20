#ifndef LIGHT_HPP
# define LIGHT_HPP

# include "vect.hpp"

struct Light
{
  Vect<2u, float> center;
  Vect<4u, float> color;
  float radius;
};

#endif //!LIGHT_HPP
