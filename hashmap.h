#pragma once
#include <iostream>
#include <vector>
#include <forward_list>
#include <exception>
#include <string.h>
#include <set>
#include <algorithm>
#include <type_traits>


///
///@class Hashmap
///@param in Key Ключ
///@param in Data Значение
///@private _countElements Количество элементов
///@private _size Размер Hashmap
///@private _lists Сам контейнер, где будут находится данные
///@private _defSize Размер для дефолтного конструктора
///@private _growthFactor Фактор роста, который регулирует размерность HashMap
///@private _loadFactor Фактор загруженности, показывает дейстительное отношение количества к размеру
/// (считается, что это среднее число элементов одну ячейку контейнера

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
  ///Функция рехеширования
  void rehash()
  {
    std::pair<std::string, int> array[_countElements];
    size_t iterator = 0;
    for (size_t i = 0; i < this->_size;i++)
      {
        if (!_lists[i]->empty())
          {
            auto first = _lists[i]->begin();
            auto last = _lists[i]->end();
            if (first == last)
              {
              array[iterator] = *first;
              iterator++;
              }
            else
              {
                do
                  {
                    array[iterator] = *first;
                    iterator++;
                    first++;
                  }while(first!=last);
              }
          }
        _lists[i]->clear();
      }
    for (size_t i = 0; i<_size; i++)
      {
        std::forward_list<std::pair<Key,Data>>* nodes = new std::forward_list<std::pair<Key,Data>>;
        _lists.push_back(nodes);
      }
    _size = _size * 2;
    for (size_t i = 0; i < iterator; i++)
      {
        size_t hash = HashFunction(array[i].first) % _size;
        _lists[hash]->push_front(array[i]);
      }
  }
  ///Хэш функция на основе стандартной
  size_t HashFunction(Key key) const
  {
    return std::hash<Key>()(key) % _size;
  }
  ///подсчет элементов в листе
  size_t LengthList(size_t hash) const
  {
    size_t count = 0;
    for (auto node:*_lists[hash])
      {
        count++;
      }
    return count;
  }
  ///установка параметров HashMap
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
  ///геттер контайнера
  std::vector<std::forward_list<std::pair<std::string,Data>>*> GetHashMap() const
  {
    {
        return _lists;
    }
  }
  ///Возвращение размера
  size_t GetSize() const
  {
      return _size;
  }
  ///проверка на наличие ключа
  bool CheckKey(size_t hash) const
  {
    return !_lists[hash]->empty();
  }

public:

  ///провряет отсутствие элементов
  bool IsEmpty() const
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
  ///@return возвращает кол-во элементов в контайнере
  size_t Size() const
  {
    return _countElements;
  }
  ///@return возвращает максимально допстимое кол-во элементов в контейнере
  size_t Max_size() const
  {
    return _size;
  }
  ///Вставка элемента
  void insert(Key key, Data data)
  {
    if (_loadFactor >= _growthFactor)
      {
        rehash();
      }
    std::pair<Key, Data> newData = std::make_pair(key, data);
    size_t hash = HashFunction(key);
    _lists[hash]->push_front(newData);
    _countElements++;
    _loadFactor = (double)_countElements/_size;
  }
  ///находит элемент с конкретным ключом
  std::pair<Key, Data>* Find(Key key) const
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
  ///Представляет доступ к указаному жлементу по ключу
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
  ///кастомный оператор для вывода
  void operator[](size_t index)
  {
    if (!_lists[index]->empty())
    {
      auto first = _lists[index]->begin();
      auto last = _lists[index]->end();
      if (first == last)
        {
        std::cout << first->first;
        }
      else
        {
          do
            {
              std::cout << first->first << " ";
              first++;
            }while(first!=last);
        }
    }
    std::cout << "\n";
  }
  ///предоставляет доступ к указаному элементу с проверкой индекса
  Data& at(Key key) const
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
  ///удаление элементов по ключу
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
        _loadFactor = (double)_countElements/_size;
        }
      else
        {
          _lists[hash]->erase_after(_lists[hash]->before_begin());
          _countElements--;
          _loadFactor = (double)_countElements/_size;
        }
    }
  }
  ///операция приравнивания
  HashMap& operator=(const HashMap& other)
  {
    for (size_t i = 0; i < other.Size(); i++)
      {
        if (other.GetHashMap()[i].empty())
          {
            auto first = other.GetHashMap()[i]->begin();
            auto last = other.GetHashMap()[i]->end();
            if (first == last)
              {
                insert(first->first,first->second);
              }
            else
              {
                do
                  {
                    insert(first->first,first->second);
                    first++;
                  }while(first!=last);
              }
          }
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
        delete _lists[i];
      }
    _lists.clear();
    delete [] _lists;
  }
};
