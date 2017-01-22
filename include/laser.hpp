#ifndef LASER_HPP_
# define LASER_HPP_

# include "vect.hpp"

struct Laser
{
  Vect<2u, double> start;
  Vect<2u, double> end;
  double power;
};

#endif
