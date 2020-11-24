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
///@private _count_elements Количество элементов
///@private _size Размер Hashmap
///@private _lists Сам контейнер, где будут находится данные
///@private _def_size Размер для дефолтного конструктора
///@private _growth_factor Фактор роста, который регулирует размерность HashMap
///@private _load_factor Фактор загруженности, показывает дейстительное отношение количества к размеру
/// (считается, что это среднее число элементов одну ячейку контейнера

template<class Key,
         class Data>
class HashMap
{
public:
  friend class iterator;
  ///итератор
  class iterator
  {
  private:
    HashMap<Key,Data>* _father;
    std::pair<const Key, Data>* _ptr;
    size_t _it_now;
    std::vector<std::string> _keys;
  public:
      ///дефолтный конструктор
      iterator() = default;
      ///конструктор с параметрами
      iterator(HashMap<Key,Data>* father,size_t position)
        :_father(father)
      {
        if (position != _father->last())
          {
          if (_father->_lists[position].empty())
            {
            _ptr = nullptr;
            }
          else
            {
            _ptr = &(*_father->_lists[position].begin());
            }
          _it_now = position;
          }
        else
          {
            _ptr = &(*_father->_lists[position].end());
            _it_now = position;
          }
      }
      ///оператор разыменования
      auto constexpr operator*()
      {
        if (_keys.empty())
          {
            _keys.push_back(_ptr->first);
          }
        return *_ptr;
      }
      ///оператор инкремента через инт
      auto constexpr operator++(int)
      {
          std::pair<const Key, Data>* ptr_other_key = nullptr;
          auto it_fl = _father->_lists[_it_now].begin();
          while (it_fl != _father->_lists[_it_now].end())
            {
              bool keyIs = false;
              for (size_t i = 0; i < _keys.size(); i++)
                {
                  if (_keys[i] == it_fl->first)
                    {
                      keyIs = true;
                      break;
                    }
                }
              if (!keyIs)
                {
                  _keys.push_back(it_fl->first);
                  ptr_other_key = &(*it_fl);
                  break;
                }
              it_fl++;
            }
          if (!ptr_other_key)
            {
            if (_it_now != _father->last())
              {
              do
                {
                _it_now++;
                }
              while(_father->_lists[_it_now].empty());
              _ptr = &(*_father->_lists[_it_now].begin());
              _keys.push_back(_ptr->first);
              }
            else
              {
                _ptr = &(*_father->_lists[_it_now].end());
              }
            }
          else
            {
              _ptr = ptr_other_key;
            }
          return *this;
      }
      ///оператор инкремента для автоопределение
      auto constexpr operator++()
      {
        if (_it_now != _father->last())
          {
          _it_now++;
          while(_father->_lists[_it_now].empty())
            {
              _it_now++;
            }
          _ptr = &(*_father->_lists[_it_now].begin());
          }
        else
          {
            _ptr = &(*_father->_lists[_it_now].end());
          }
          return *this;
      }
      ///оператор равенства
      constexpr bool operator==(const iterator& second) const
      {
          return _ptr == second._ptr;
      }
      ///оператор неравенства
      constexpr bool operator!=(const iterator& second) const
      {
          return _ptr != second._ptr;
      }
  };
private:
  iterator _iterator;
  size_t _count_elements;
  size_t _size;
  std::vector< std::forward_list< std::pair< const Key,Data > > > _lists;
  static constexpr size_t _def_size = 1000;
  static constexpr double _growth_factor = 0.66;
  double _load_factor;
  ///Функция рехеширования rework
//  void rehash()
//  {
//    std::pair<Key, Data> array[_count_elements];
//    size_t index = 0;
//    for (size_t index = 0; index < _size;index++)
//      {
//        if (!_lists[index].empty())
//          {
//            auto first = _lists[index].begin();
//            auto last = _lists[index].end();
//            if (first == last)
//              {
//              array[index] = std::make_pair(first->first,first->second);
//              index++;
//              }
//            else
//              {
//                do
//                  {
//                    array[index] = std::make_pair(first->first,first->second);
//                    index++;
//                    first++;
//                  }while(first!=last);
//              }
//          }
//        _lists[index].clear();
//        _lists.push_back(std::forward_list<std::pair<const Key,Data>>());
//      }
//    _size = _size * 2;
//    for (size_t i = 0; i < index; i++)
//      {
//        size_t hash = HashFunction(array[i].first) % _size;
//        _lists[hash].push_front(array[i]);
//      }
//  }

  ///Хэш функция на основе стандартной
  size_t HashFunction(const Key key) const
  {
    return std::hash<Key>()(key) % _size;
  }
  ///подсчет элементов в листе
  size_t LengthList(size_t hash) const
  {
    size_t count = 0;
    for (auto node:_lists[hash])
      {
        count++;
      }
    return count;
  }
  ///установка параметров HashMap
  void SetConfigurations(size_t size)
  {
    _iterator = iterator();
    if (size < 0)
      {
        throw std::runtime_error("size must be positive(more then zero)");
      }
    _size = size;
    _count_elements = 0;
    _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_count_elements);
    for (size_t index = 0; index < _size; index++)
      {
        _lists.push_back(std::forward_list<std::pair<const Key, Data>>());
      }
  }
  ///геттер контайнера
  std::vector<std::forward_list<std::pair<std::string,Data>>*> GetHashMap() const
  {
    return _lists;
  }
  ///Возвращение размера
  size_t GetSize() const
  {
    return _size;
  }
  ///проверка на наличие ключа
  bool CheckKey(size_t hash) const
  {
    return !_lists[hash].empty();
  }

  ///возвращает номер первого элемента
  size_t first()
  {
    size_t counter = 0;
    for (auto list:_lists)
      {
        if(!list.empty())
          {
            return counter;
          }
        counter++;
      }
  }

  ///возвращает номер последнего элемента
  size_t last()
  {
    size_t last_index = 0;
    for (size_t i = 0; i < _size ; i++)
      {
        if (!_lists[i].empty())
          {
            last_index = i;
          }
      }
    return last_index;
  }
public:
  ///итератор начала
  iterator begin()
  {
   iterator it_begin(this,first());
   return it_begin;
  }
  ///итератор конца
  iterator end()
  {
    iterator it_end(this,last());
    return it_end;
  }
  ///провряет отсутствие элементов
  bool empty() const
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
  ///@return возвращает максимальную вместительность контейнера
  size_t size() const
  {
    return _size;
  }
  ///@return возвращает кол-во элементов в контайнере
  size_t count(const Key& key) const
  {
    size_t count_with_key = 0;
    size_t hash = HashFunction(key);
    if (!_lists[hash].empty())
      {
        for (auto list:_lists[hash])
          {
            if (list.first == key)
              {
                count_with_key++;
              }
          }
      }
    return count_with_key;
  }
  ///Вставка элемента
  void insert(std::pair<const Key, Data>&& node)
  {
//    if (_load_factor >= _growth_factor)
//      {
//        rehash();
//      }
    size_t hash = HashFunction(node.first);
    _lists[hash].push_front(node);
    _count_elements++;
    _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
  }
  ///находит элемент с конкретным ключом
  std::pair<const Key, Data>* find(const Key& key)
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
  Data& operator[](Key&& key)
  {
    std::pair<const Key, Data>* search_pair = find(key);
    if (search_pair!=nullptr)
      {
        return search_pair->second;
      }
    else
      {
        insert(key, Data());
        search_pair = find(key);
        return search_pair->second;
      }
  }
  ///кастомный оператор для вывода
  void operator[](size_t index)
  {
    if (!_lists[index].empty())
    {
      auto first = _lists[index].begin();
      auto last = _lists[index].end();
//      std::cout << " (" << _lists[index].empty() << ") ";
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
  Data& at(const Key& key)
  {
    std::pair<const Key, Data>* search_pair = find(key);
    if(search_pair != nullptr)
      {
        return search_pair->second;
      }
    else
      {
        throw std::out_of_range("out of range");
      }
  }
  ///удаление элементов по ключу
  void erase(const Key& key)
  {
    const size_t hash = HashFunction(key);
    if (CheckKey(hash))
      {
      if (LengthList(hash) > 1)
        {
        auto before = _lists[hash].before_begin();
        auto node = _lists[hash].begin();
        while(node != _lists[hash].end())
          {
            if (node->first == key)
              {
                node++;
                _lists[hash].erase_after(before);
                _count_elements--;
              }
            else
              {
                before = node;
                node++;
              }
          }
        _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
        }
      else
        {
          _lists[hash].erase_after(_lists[hash].before_begin());
          _count_elements--;
          _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
        }
    }
  }
  ///операция приравнивания с семантикой копирования
  HashMap& operator=(const HashMap& other) = default;

  ///операция приравнивания с семантикой перемещения
  HashMap& operator=(HashMap&& other) = default;

  HashMap()
  {
    SetConfigurations(_def_size);
  }

  HashMap(size_t size)
  {
    SetConfigurations(size);
  }
  ///конструктор копирования
  HashMap(const HashMap& other):
    _size(other._size),
    _count_elements(other._count_elements),
    _lists(other._lists),
    _load_factor(other._load_factor)
  {
  }
  ///конструктор перемещения
  HashMap(HashMap&& other) = default;

  ~HashMap() = default;

};
