#pragma once
#include <iostream>
#include <vector>
#include <forward_list>
#include <exception>
#include <string.h>
#include <set>
#include <algorithm>
#include <type_traits>
//add requiers
//template <class T>
//concept name = std::is_arithmetic<T>::value;

template<class Key,
         class Data>
class HashMap
{
private:
  unsigned int _countElements;
  size_t _size;
  std::vector< std::forward_list< std::pair< Key,Data > >* > _lists;
  static constexpr size_t _defSize = 4;
  static constexpr double _growthFactor = 0.66;
  double _loadFactor;

  size_t HashFunction(Key key)
  {
    size_t hash = 0;
    if (std::is_arithmetic_v<Key>)
      {
        for (size_t i= 0; i<key.size(); i++)
        {
          hash += key[i];
        }
        return hash % this->_size;
      }
    else
      {
        size_t k = 24;
        hash += abs(key * k - k) % _size;
        return hash;
      }
  }


  size_t LengthList(size_t hash)
  {
    size_t count = 0;
    for (auto node:*_lists[hash])
      {
        count++;
      }
    return count;
  }

  void SetConfigurations(size_t size)
  {
    if (size < 0)
      {
        throw std::runtime_error("size must be positive(more then zero)");
      }
    this->_size = size;
    this->_countElements = 0;
    this->_loadFactor = this->_countElements / this->_size;
    for (size_t i = 0; i < this->_size; i++)
      {
        std::forward_list<std::pair<Key,Data>>* nodes = new std::forward_list<std::pair<Key,Data>>;
        _lists.push_back(nodes);
      }
  }

  std::vector<std::forward_list<std::pair<std::string,Data>>*> GetHashMap() const
  {
    {
        return _lists;
    }
  }

  size_t GetSize() const
  {
      return _size;
  }

  bool CheckKey(size_t hash)
  {
    return !_lists[hash]->empty();
  }

public:

  bool IsEmpty()
  {
    if (_size == 0)
      {
        return true;
      }
    else
      {
        return false;
      }
  }

  size_t Size()
  {
    return _countElements;
  }

  size_t Max_size()
  {
    return _size;
  }

  void insert(Key key, Data data)
  {
    std::pair<Key, Data> newData = std::make_pair(key, data);
    size_t hash = HashFunction(key);
    _lists[hash]->push_front(newData);
    _countElements++;
  }

  std::pair<Key, Data>* Find(Key key)
  {
    if (!CheckKey(HashFunction(key)))
      {
        return nullptr;
      }
    else
      {
        size_t hash = HashFunction(key);
        auto node = _lists[hash].begin();
        do
          {
            if (node->first == key)
              {
                return &(*node);
              }
            node++;
          }while(node != _lists[hash].end());
      }
  }

  Data& operator[](Key key)
  {
    std::pair<std::string, Data>* searchPair = Find(key);
    if (searchPair!=nullptr)
      {
        return searchPair->second;
      }
    else
      {
        size_t hash = HashFunction(key);
        _lists[hash].push_front(make_pair(key,Data()));
      }
  }

//  void operator[](size_t index)
//  {
//    if (!_lists[index]->empty())
//    {
//      auto first = _lists[index]->begin();
//      auto last = _lists[index]->end();
//      if (first == last)
//        {
//        std::cout << first->first;
//        }
//      else
//        {
//          do
//            {
//              std::cout << first->first << " ";
//              first++;
//            }while(first!=last);
//        }
//    }
//    std::cout << "\n";
//  }

  Data& at(Key key)
  {
    std::pair<std::string, Data>* searchPair = Find(key);
    if(searchPair != nullptr)
      {
        return searchPair->second;
      }
    else
      {
        throw std::out_of_range("out of range");
      }
  }

  void erase(const Key key)
  {
    const size_t hash = HashFunction(key);
    if (CheckKey(hash))
      {
      if (LengthList(hash) > 1)
        {
        std::forward_list<std::pair<Key, Data>>* list = _lists[hash];
        auto before = list->before_begin();
        auto node = list->begin();
        while(node != list->end())
          {
            if (node->first == key)
              {
                node++;
                list->erase_after(before);
                _countElements--;
              }
            else
              {
                node++;
                before++;
              }
          }
          }
      else
        {
          _lists[hash]->erase_after(_lists[hash]->before_begin());
          _countElements--;
        }
    }
  }




//  const Data& at(const Key& key)
//  {
//    std::pair<std::string, Data>* searchPair = Find(key);
//    if(searchPair != nullptr)
//      {
//        return searchPair->second;
//      }
//    else
//      {
//        throw std::out_of_range("out of range");
//      }
//  }

  HashMap& operator=(const HashMap& other)
  {
    for(size_t i = 0; i < this->_lists.size(); i++)
      {
        other._lists[i].splice_after(other._lists[i].begin(),this->_lists[i]);
      }
    return *this;
  }

  HashMap()
  {
    SetConfigurations(_defSize);
  }

  HashMap(size_t size)
  {
    SetConfigurations(size);
  }

  ~HashMap()
  {
    for (size_t i = 0; i < this->_size;i++)
      {
        _lists[i]->clear();
      }
    _lists.clear();
  }
};
