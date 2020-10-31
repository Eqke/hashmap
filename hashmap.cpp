#include "hashmap.h"

template<class data>
int HashMap<data>::HashFunction(char* key)
{
  int sum = 0;
  for (size_t i = 0; i < sizeof(key); i++)
    {
        sum+=key[i];
    }
  return sum % this->_size;
}

template<class data>
std::vector<std::forward_list<std::pair<char*, data>>*> HashMap<data>::GetHashMap() const
{
	return this->_lists;
}

template<class data>
size_t HashMap<data>::GetSize() const
{
	return this->_size;
}

template<class data>
void HashMap<data>::SetCountElements(int countElements)
{
  if (countElements < 0)
    {
      throw ("count must be positive(more then zero)");
    }
  this->_countElements = countElements;
}

template<class data>
void HashMap<data>::SetSize(int size)
{
  if (size < 0)
    {
      throw ("size must be positive(more then zero)");
    }
  this->_size = size;
}

template<class data>
HashMap<data>::HashMap()
{
  SetSize(_defSize);
  SetCountElements(0);

}

