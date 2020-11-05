#pragma once
#include <iostream>
#include <vector>
#include <forward_list>
#include <exception>
#include <string.h>
#include <set>
#include <algorithm>
//add requiers



template<class Key,
         class Data>
class HashMap
{
private:
  unsigned int _countElements;
  size_t _size;
  std::vector< std::forward_list< std::pair< Key,Data > >* >* _lists;
  static constexpr size_t _defSize = 4;

  size_t HashFunction(std::string key)
  {
    size_t sum = 0;
    for (size_t i= 0; i<key.size(); i++)
      {
          sum += key[i];
      }
    return sum % this->_size;
  }

  void SetConfigurations(size_t size)
  {
    if (size < 0)
      {
        throw std::runtime_error("size must be positive(more then zero)");
      }
    this->_size = size;
    this->_countElements = 0;
    for (size_t i = 0; i < this->_size; i++)
      {
        std::forward_list<std::pair<Key,Data>>* unit = new std::forward_list<std::pair<Key,Data>>;
        this->_lists.push_back(unit);
      }
  }

  std::vector<std::forward_list<std::pair<std::string,Data>>*> GetHashMap() const
  {
    {
        return this->_lists;
    }
  }

  size_t GetSize() const
  {
      return this->_size;
  }

  bool CheckKey(size_t hash)
  {
    return !this->_lists[hash]->empty();
  }

public:

  bool IsEmpty()
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

  size_t Size()
  {
    return this->_countElements;
  }

  size_t Max_size()
  {
    return this->_size;
  }

  void Insert(std::string key, Data data)
  {
    std::pair<std::string, Data> newData = make_pair(key, data);
    size_t hash = HashFunction(key);
    this->_lists[hash]->push_front(newData);
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
        auto node = this->_lists[hash]->begin();
        do
          {
            if (node->first == key)
              {
                return &(*node);
              }
            node++;
          }while(node != this->_lists[hash]->end());
      }
  }

  Data& operator[](std::string key)
  {
    std::pair<std::string, Data>* searchPair = Find(key);
    if (searchPair!=nullptr)
      {
        return searchPair->second;
      }
    else
      {
        size_t hash = HashFunction(key);
        this->_lists[hash]->push_front(make_pair(key,Data()));
      }
  }
  auto operator[](size_t index)
  {
    return this->_lists[index];
  }

  Data& at(std::string key)
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

//  void erase(const std::string& key)
//  {

//  }


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
        auto node = this->_lists[i].begin();
        do
          {
            auto saveNode = node + 1;
            delete node;
            node = saveNode;
          }while(node != this->_lists[i].end());
        delete this->_lists[i];
      }
  }
};
