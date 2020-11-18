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
  public:
      HashMap<Key,Data>* _father;
      const std::pair<const Key, Data>* _ptr;
      size_t _it_now;
      iterator() = default;
      iterator(HashMap<Key,Data>& father,size_t position = 0)
        :_father(&father),
          _it_now(position),
          _ptr(nullptr)
      {
          if (_father->_lists[0].empty()){
              _ptr = nullptr;
          }
          else{
              _ptr = &(_father->_lists[0].begin());
          }
          _it_now = 0;
      }
      auto constexpr operator*()
      {
          return *_ptr;
      }
      auto constexpr operator++()
      {
          while(!*_father->_lists[_it_now].empty())
            {
              if (_it_now < _father->_size)
                {
                  _it_now++;
                }
            }
          _ptr = &(_father->_lists[_it_now].begin());
          return *this;
      }

      auto constexpr operator--()
      {
          while(!_father->_lists[_it_now].empty())
            {
              if (_it_now > 0)
                {
                  _it_now--;
                }
            }
          _ptr = &(_father->_lists[_it_now].begin());
          return *this;
      }

      constexpr bool operator==(iterator&& second)
      {
          return this->_ptr == second->_ptr;
      }
//      void first(){
//          ptr = &*parent.buckets[parent.first_pos]->begin();
//      };
//      void end(){
//          ptr = &*parent.buckets[parent.first_pos]->end();
//      };
//      void constexpr next(){
//          size_t counter = pos;
//          while(counter <= parent.last_pos){
//              if(!parent.buckets[counter]->empty()){
//                  auto current_bucket = parent.buckets[counter];
//                  auto forward_iterator = current_bucket->begin();
//                  size_t length = 0;
//                  for (auto elem:*current_bucket){
//                      length++;
//                  }

//                  if(length > 1 && ptr != &*current_bucket->end() ){
//                      while(&*forward_iterator!=ptr){
//                          forward_iterator++;
//                      }
//                      ptr = &*forward_iterator;
//                      return;
//                  }

//                  this->ptr = &(parent.buckets[counter]->front());
//                  pos = counter;
//                  return;
//              }
//              counter++;
//          }
//      }

//      void constexpr prev();
      };
private:
  iterator _iterator;
  unsigned int _count_elements;
  size_t _size;
  std::vector< std::forward_list< std::pair< const Key,Data > > > _lists;
  static constexpr size_t _def_size = 4;
  static constexpr double _growth_factor = 0.66;
  double _load_factor;

  ///Функция рехеширования
  void rehash()
  {
    std::pair<Key, Data> array[_count_elements];
    size_t index = 0;
    for (size_t index = 0; index < _size;index++)
      {
        if (!_lists[index].empty())
          {
            auto first = _lists[index].begin();
            auto last = _lists[index].end();
            if (first == last)
              {
              array[index] = std::make_pair(first->first,first->second);
              index++;
              }
            else
              {
                do
                  {
                    array[index] = std::make_pair(first->first,first->second);
                    index++;
                    first++;
                  }while(first!=last);
              }
          }
        _lists[index].clear();
        _lists.push_back(std::forward_list<std::pair<const Key,Data>>());
      }
    _size = _size * 2;
    for (size_t i = 0; i < index; i++)
      {
        size_t hash = HashFunction(array[i].first) % _size;
        _lists[hash].push_front(array[i]);
      }
  }
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
    this->_size = size;
    this->_count_elements = 0;
    this->_load_factor = static_cast<double>(_count_elements/_count_elements);
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

public:
  iterator& begin()
  {
   iterator it_begin(_lists[0].begin());
   return it_begin;
  }
  iterator& end()
  {
    iterator it_end(_lists[_size - 1] + 1);
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
  ///@return возвращает кол-во элементов в контайнере
  size_t size() const
  {
    return _count_elements;
  }
  ///@return возвращает максимальную вместительность контейнера
  size_t capacity() const
  {
    return _size;
  }
  ///Вставка элемента
  void insert(const Key key, Data data)
  {
    if (_load_factor >= _growth_factor)
      {
        rehash();
      }
    std::pair<const Key, Data> newData = std::make_pair(key, data);
    size_t hash = HashFunction(key);
    _lists[hash].push_front(newData);
    _count_elements++;
    _load_factor = static_cast<double>(_count_elements/_size);
  }
  ///находит элемент с конкретным ключом
  std::pair<const Key, Data>* Find(Key key)
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
  Data& operator[](const Key key)
  {
    std::pair<const Key, Data>* search_pair = Find(key);
    if (search_pair!=nullptr)
      {
        return search_pair->second;
      }
    else
      {
        insert(key, Data());
        search_pair = Find(key);
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
  Data& at(const Key key)
  {
    std::pair<const Key, Data>* search_pair = Find(key);
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
  void erase(const Key key)
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
        _load_factor = static_cast<double>(_count_elements/_size);
        }
      else
        {
          _lists[hash].erase_after(_lists[hash].before_begin());
          _count_elements--;
          _load_factor = static_cast<double>(_count_elements/_size);
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
  HashMap(const HashMap&& other) noexcept :
   HashMap(std::move(other))
  {
  }
  ~HashMap()
  {
    for (size_t index = 0; index < this->_size;index++)
      {
        _lists[index].clear();
      }
    _lists.clear();
  }
};
