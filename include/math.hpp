#ifndef MATH_HPP
# define MATH_HPP

namespace math
{
  template<class T>
  constexpr Vect<2u, T> complexProduct(Vect<2u, T> a, Vect<2u, T> b)
  {
    return Vect<2u, T>{a[0] * b[0] - a[1] * b[1], a[0] * b[1] + a[1] * b[0]};
  }
};

#endif // !MATH_HPP
