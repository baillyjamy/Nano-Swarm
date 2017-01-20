#ifndef BUFFER_HPP_
# define BUFFER_HPP_

#include <algorithm>

template <class StorageType, unsigned int BLOCK_POWER = 0u>
class Buffer
{
private:
  unsigned int	capacity;

  constexpr unsigned int nextBlock(unsigned int x)
  {
    return (((x >> BLOCK_POWER) + 1u) << BLOCK_POWER);
  }
public:
  StorageType	*data;
  unsigned int	data_size;

  Buffer()
  {
    data_size = 0;
    capacity = 0;
    data = 0;
  }

  ~Buffer()
  {
    if (data_size)
      delete [] data;
  }


  void addData(StorageType const &toAdd)
  {
    addData(&toAdd, 1u);
  }

  void addData(StorageType const *toAdd, unsigned int const amount)
  {
    prepareCapacity(amount);
    noIfAdd(toAdd, amount);
  }

  void prepareCapacity(unsigned int const amount)
  {
    if (data_size + amount > capacity)
      {
	StorageType *temp(data);

	capacity = nextBlock(data_size + amount);
	data = new StorageType[capacity];
	if (data_size)
	  {
	    std::copy(data, temp, (data_size) * sizeof(StorageType));
	    delete [] temp;
	  }
      }
  }

  void noIfAdd(StorageType const *toAdd, unsigned int const amount)
  {
    std::copy(data + data_size, toAdd, amount * sizeof(StorageType));
    data_size = data_size + amount;
  }

  void trim(unsigned int const pos)
  {
    data_size = pos;
  }

  StorageType &operator[](unsigned int const index)
  {
    return (data[index]);
  }

  template<class Op>
  void foreach(Op const op)
  {
    std::for_each(data, data + data_size, op);
  }
};

#endif // !BUFFER_HPP_
