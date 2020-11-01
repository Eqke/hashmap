#include "hashmap.h"

template<class Key, class Data>
size_t HashMap<Key, Data>::HashFunction(Key key)
{
  int sum = 0;
  for (auto character:key)
    {
        sum+=key[i];
    }
  return sum % this->_size;
}

template<class data>
std::vector<std::forward_list<std::pair<char*, data>>> HashMap<data>::GetHashMap() const
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
void HashMap<data>::SetListConfigurations(int size)
{
  if (size < 0)
    {
      throw ("size must be positive(more then zero)");
    }
  this->_size = size;
  this->_lists = std::vector<std::forward_list<std::pair<char*,data>>> (this->_size);
}

template<class data>
bool HashMap<data>::IsEmpty()
{
  if (this->_size == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

template<class data>
size_t HashMap<data>::size()
{
  return this->_countElements;
}

template<class data>
size_t HashMap<data>::max_size()
{
  return this->_size;
}


//template<class data>
//void HashMap<data>::SetList(size_t size)
//{
//  this->_lists = std::vector<std::forward_list<std::pair<char*,data>>> (size);
//}

template<class data>
HashMap<data>::HashMap()
{
  SetListConfigurations(_defSize);
  SetCountElements(0);
}

template<class data>
HashMap<data>::~HashMap()
{
  delete [] this->_lists;
}

