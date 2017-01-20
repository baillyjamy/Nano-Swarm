#ifndef MULTI_TYPE_LIST_HPP
# define MULTI_TYPE_LIST_HPP

#include <vector>
#include "container.hpp"

template<class... Types>
class MultiTypeList
  : public Container<std::vector<Types...>>
{
};

#endif // !MULTI_TYPE_LIST_HPP
