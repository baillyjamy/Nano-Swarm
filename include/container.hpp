#ifndef CONTAINER_HPP_
# define CONTAINER_HPP_

# include <type_traits>

template<class U, class... T>
class Container
{
public:
  U u;
  Container<T...> others;

  constexpr Container(U u, T... others)
    : u(u), others(others...)
  {}

  Container()
    : u(), others()
  {}

  template<class Op>
  void applyOnEach(Op op)
  {
    op(u);
    others.applyOnEach(op);
  }

  template<class V, typename std::enable_if<std::is_same<U, V>::value>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (u);
  }

  template<class V, typename std::enable_if<std::is_same<U, V>::value>::type* = nullptr>
  inline V &at()
  {
    return (u);
  }

  template<class V, typename std::enable_if<!std::is_same<U, V>::value>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (others.template at<V>());
  }

  template<class V, typename std::enable_if<!std::is_same<U, V>::value>::type* = nullptr>
  inline V &at()
  {
    return (others.template at<V>());
  }

  /*
   * Specific accessors for when there same-type contents
   * Rank is decreased each type an object of the right type is met.
   */
  template<unsigned int Rank, class V, typename std::enable_if<std::is_same<U, V>::value && Rank>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (others.template at<Rank - 1, V>());
  }

  template<unsigned int Rank, class V, typename std::enable_if<std::is_same<U, V>::value && !Rank>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (u);
  }

  template<unsigned int Rank, class V, typename std::enable_if<!std::is_same<U, V>::value>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (others.template at<V>());
  }
};


template<class U>
class Container<U>
{
public:
  U u;

  constexpr Container(U u)
    : u(u)
  {}

  Container()
    : u()
  {}

  template<class Op>
  void applyOnEach(Op op)
  {
    op(u);
  }

  template<class V, typename std::enable_if<std::is_same<U, V>::value>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (u);
  }

  template<class V, typename std::enable_if<std::is_same<U, V>::value>::type* = nullptr>
  inline V &at()
  {
    return (u);
  }

  /*
   * Specific accessors for when there same-type contents
   */
  template<unsigned int Rank, class V, typename std::enable_if<std::is_same<U, V>::value && !Rank>::type* = nullptr>
  constexpr const inline V at() const
  {
    return (u);
  }
};

#endif // CONTAINER_HPP_
