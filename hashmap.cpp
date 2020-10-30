#include "hashmap.h"


template<class key, class data>
auto HashMap<key, data>::HashFunction(key)
{
	return key % this->_countElements;
}

template<class key, class data>
std::vector<std::forward_list<std::pair<key, data>>*> HashMap<key, data>::GetList() const
{
	return this->_lists;
}

template<class key, class data>
size_t HashMap<key, data>::GetSize() const
{
	return size_t();
}


