#ifndef BIND_HPP
# define BIND_HPP

#include "container.hpp"

template<class... T>
class Bind
{
private:
  
  class Binder
  {
  public:
    template<class U>
    void operator()(U u)
    {
      u.bind();
    }
  };

  class Unbinder
  {
  public:
    template<class U>
    void operator()(U u)
    {
      u.unbind();
    }
  };

public:
  Container<T...> data;
  unsigned int *count;

  template<class... U>
  Bind(U... u)
    : data(u...), count(new unsigned int(1))
  {
    data.applyOnEach(Binder());
  }

  Bind(Bind<T...> const &b)
    : data(b.data), count(b.count)
  {
    ++*count;
  }

  ~Bind()
  {
    if (!--*count)
      {
	data.applyOnEach(Unbinder());
	delete count;
      }
  }

  Bind<T...> &operator=(Bind<T> b)
  {
    std::swap(data, b.data);
    std::swap(count, b.count);
    return *this;
  }
  
};

#endif
