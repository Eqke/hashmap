#include "hashmap.h"

//template<class Key, class Data>
//size_t HashMap<Key, Data>::HashFunction(char* key)
//{
//  int sum = 0;
//  for (size_t i= 0; i<size(key); i++)
//    {
//        sum += key[i];
//    }
//  return sum % this->_size;
//}

//template<class Key, class Data>
//std::vector<std::forward_list<std::pair<char*, Data>>> HashMap<Key, Data>::GetHashMap() const
//{
//    return this->_lists;
//}

//template<class Key, class Data>
//size_t HashMap<Key, Data>::GetSize() const
//{
//    return this->_size;
//}

//template<class Key, class Data>
//void HashMap<Key, Data>::SetCountElements(int countElements)
//{
//  if (countElements < 0)
//    {
//      throw ("count must be positive(more then zero)");
//    }
//  this->_countElements = countElements;
//}

//template<class Key, class Data>
//void HashMap<Key, Data>::SetListConfigurations(int size)
//{
//  if (size < 0)
//    {
//      throw ("size must be positive(more then zero)");
//    }
//  this->_size = size;
//  this->_lists = std::vector<std::forward_list<std::pair<char*,Data>>> (this->_size);
//}

//template<class Key, class Data>
//bool HashMap<Key, Data>::IsEmpty()
//{
//  if (this->_size == 0)
//    {
//      return true;
//    }
//  else
//    {
//      return false;
//    }
//}

//template<class Key, class Data>
//size_t HashMap<Key, Data>::size()
//{
//  return this->_countElements;
//}

//template<class Key, class Data>
//size_t HashMap<Key, Data>::max_size()
//{
//  return this->_size;
//}


//template<class Key, class Data>
//void HashMap<Key, Data>::SetList(size_t size)
//{
//  this->_lists = std::vector<std::forward_list<std::pair<char*,data>>> (size);
//}

//template<class Key, class Data>
//HashMap<Key, Data>::HashMap()
//{
//  SetListConfigurations(_defSize);
//  SetCountElements(0);
//}

//template<class Key, class Data>
//HashMap<Key, Data>::~HashMap()
//{
//  delete [] this->_lists;
//}

