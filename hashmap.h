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
///@param in key_type Ключ
///@param in data_type Значение
///@private _count_elements Количество элементов
///@private _size Размер Hashmap
///@private _lists Сам контейнер, где будут находится данные
///@private _def_size Размер для дефолтного конструктора
///@private _growth_factor Фактор роста, который регулирует размерность HashMap
///@private _load_factor Фактор загруженности, показывает дейстительное отношение количества к размеру
/// (считается, что это среднее число элементов одну ячейку контейнера

template<class key_type,
         class data_type>
class HashMap
{
public:
  friend class iterator;
  ///итератор
  class iterator
  {
  private:
    HashMap<key_type,data_type>* _father;
    std::pair<const key_type, data_type>* _ptr;
    size_t _it_now;
    std::vector<key_type> _keys;
  public:
      ///дефолтный конструктор
      iterator() = default;
      ///конструктор с параметрами
      iterator(HashMap<key_type,data_type>* father,size_t position, bool isEnd)
        :_father(father)
      {
        if (_father->_count_elements == 0)
          {
            if (isEnd)
              {
                _ptr = &(*_father->_lists[position].end());
                _it_now = position;
              }
            else
              {
                _ptr = &(*_father->_lists[position].begin());
                _it_now = position;
              }
          }
        else if ((position == _father->last()) && (position == _father->first()))
          {
            if (isEnd)
              {
                _ptr = &(*_father->_lists[position].end());
                _it_now = position;
              }
            else
              {
                _ptr = &(*_father->_lists[position].begin());
                _it_now = position;
              }
          }
        else if (position != _father->last())
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
        else if (position == _father->last())
          {
            _ptr = &(*_father->_lists[position].end());
            _it_now = position;
          }
      }
      iterator(std::pair<const key_type, data_type>* ptr,size_t position, HashMap<key_type,data_type>* father)
        :_father(father),
        _it_now(position),
        _ptr(ptr)
      {}

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
          std::pair<const key_type, data_type>* ptr_other_key = nullptr;
          auto it_fl = _father->_lists[_it_now].begin();
          while (it_fl != _father->_lists[_it_now].end())
            {
              bool keyIs = false;
              for (size_t i = 0; i < _keys.size(); i++)
                {
                  if (std::equal_to(_keys[i], it_fl->first))
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
        std::pair<const key_type, data_type>* ptr_other_key = nullptr;
        auto it_fl = _father->_lists[_it_now].begin();
        while (it_fl != _father->_lists[_it_now].end())
          {
            bool keyIs = false;
            for (size_t i = 0; i < _keys.size(); i++)
              {
                if (std::equal_to(_keys[i], it_fl->first))
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
  std::vector< std::forward_list< std::pair< const key_type,data_type > > > _lists;
  static constexpr size_t _def_size = 1000;
  static constexpr double _growth_factor = 0.66;
  double _load_factor;
  ///Функция рехеширования rework
  void rehash()
  {
    std::pair<const key_type, data_type> array[_count_elements];
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
        _lists.push_back(std::forward_list<std::pair<const key_type,data_type>>());
      }
    _size = _size * 2;
    for (size_t i = 0; i < index; i++)
      {
        size_t hash = hash_function(array[i].first);
        _lists[hash].push_front(array[i]);
      }
  }

  ///Хэш функция на основе стандартной
  size_t hash_function(const key_type key) const
  {
    return std::hash<key_type>()(key) % _size;
  }
  ///установка параметров HashMap
  void set_configurations(size_t size)
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
        _lists.push_back(std::forward_list<std::pair<const key_type, data_type>>());
      }
  }
  ///геттер контайнера
  std::vector<std::forward_list<std::pair<std::string,data_type>>*> GetHashMap() const
  {
    return _lists;
  }
  ///Возвращение размера
  size_t GetSize() const
  {
    return _size;
  }
  ///проверка на наличие ключа
  bool key_exist(size_t hash) const
  {
    return !_lists[hash].empty();
  }

  ///возвращает номер первого элемента
  size_t first()
  {
    size_t counter = 0;
    if (_count_elements != 0)
      {
      for (auto list:_lists)
        {
          if(!list.empty())
            {
              return counter;
            }
          counter++;
        }
      }
        return counter;
  }

  ///возвращает номер последнего элемента
  size_t last()
  {
    size_t last_index = 0;
    if (_count_elements != 0)
      {
      for (size_t i = 0; i < _size ; i++)
        {
          if (!_lists[i].empty())
            {
              last_index = i;
            }
        }
      return last_index;
      }
    return _size - 1;
  }
public:
  ///итератор начала
  iterator begin()
  {
    iterator it_begin(this,first(),false);
    return it_begin;
  }
  ///итератор конца
  iterator end()
  {
    iterator it_end(this,last(),true);
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
  size_t count(const key_type& key) const
  {
    size_t count_with_key = 0;
    size_t hash = hash_function(key);
    if (!_lists[hash].empty())
      {
        for (auto list:_lists[hash])
          {
            if (std::equal_to(list.first, key))
              {
                count_with_key++;
              }
          }
      }
    return count_with_key;
  }
  ///Вставка элемента
  std::pair<iterator, bool> insert (const std::pair<const key_type, data_type>& newd)
  {
//    if (_load_factor >= _growth_factor)
//      {
//        rehash();
//      }
    bool isCreated = false;
    size_t hash = hash_function(newd.first);
    if (!_lists[hash].empty())
      {
        auto it = _lists[hash].begin();
        while(it != _lists[hash].end())
          {
            if (std::equal_to(it->first, newd.first))
              {
                isCreated = true;
                it->second = newd.second;
                iterator returned_it(&(*it),hash,this);
                return std::make_pair(returned_it, !isCreated);
              }
            it++;
          }
        if (!isCreated)
          {
            _lists[hash].push_front(newd);
            _count_elements++;
            _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
            auto returned_it = find(newd.first);
            return std::make_pair(returned_it, !isCreated);
          }
      }
    else
      {
        _lists[hash].push_front(newd);
        _count_elements++;
        _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
        auto returned_it = find(newd.first);
        return std::make_pair(returned_it, !isCreated);
      }
  }
  ///находит элемент с конкретным ключом
  iterator find(const key_type& key)
  {
    size_t hash = hash_function(key);
    if (!key_exist(hash))
      {
        return end();
      }
    else
      {
        auto it = _lists[hash].begin();
        while (it != _lists[hash].end())
          {
            if (std::equal_to(it->first, key))
              {
                iterator returned_it(&(*it),hash,this);
                return returned_it;
              }
            it++;
          }
        return end();
      }
  }
  ///Представляет доступ к указаному жлементу по ключу ????
//  data_type& operator[](const key_type& key)
//  {
//    iterator search_it = find(key);
//    if (search_it!=end())
//      {
//        return search_it.operator*().second;
//      }
//    else
//      {
//        insert(std::pair<key_type, data_type> (key, data_type()));
//        search_it = find(key);
//        return search_it.operator*().second;
//      }
//  }
  data_type& operator[](const key_type& key)
  {
    size_t hash = hash_function(key);
    if (_lists[hash].empty())
    {
      insert(std::pair<key_type, data_type>(key, data_type()));
      return _lists[hash].begin()->second;
    }
    else
    {
        auto it = _lists[hash].begin();
        while (it != _lists[hash].end())
          {
            if (std::equal_to(it->first,key))
              {
                return it->second;
              }
            it++;
          }
        insert(std::pair<key_type, data_type>(key, data_type()));
        return _lists[hash].begin()->second;
    }
  }

  const data_type& operator[](const key_type& key) const
  {
    size_t hash = hash_function(key);
    if (_lists[hash].empty())
    {
      throw std::out_of_range("map hasn't element with this key");
    }
    else
    {
        auto it = _lists[hash].begin();
        while (it != _lists[hash].end())
          {
            if (std::equal_to(it->first, key))
              {
                return const_cast<const data_type&>(it->second);
              }
            it++;
          }
        throw std::out_of_range("map hasn't element with this key");
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
  data_type& at(const key_type& key)
  {
    size_t hash = hash_function(key);
    if (_lists[hash].empty())
    {
      throw std::out_of_range("out of range");
    }
    else
    {
        auto it = _lists[hash].begin();
        while (it != _lists[hash].end())
          {
            if (std::equal_to(it->first, key))
              {
                return it->second;
              }
            it++;
          }
        insert(std::pair<key_type, data_type>(key, data_type()));
        return _lists[hash].begin()->second;
    }
  }
  ///удаление элементов по ключу
  size_t erase(const key_type& key)
  {
    const size_t hash = hash_function(key);
    if (key_exist(hash))
    {
      size_t counter = 0;
      auto it = _lists[hash].begin();
      auto before_it = _lists[hash].before_begin();
      while (it != _lists[hash].end())
        {
          if (std::equal_to(it->first, key))
            {
              it++;
              _lists[hash].erase_after(before_it);
              _count_elements--;
              counter++;
            }
          else
            {
              before_it = it;
              it++;
            }
        }
      _load_factor = static_cast<double>(_count_elements)/static_cast<double>(_size);
      return counter;
    }
    else
    {
       return 0;
    }
  }
  ///операция приравнивания с семантикой копирования
  HashMap& operator=(const HashMap& other) = default;

  ///операция приравнивания с семантикой перемещения
  HashMap& operator=(HashMap&& other) = default;

  HashMap()
  {
    set_configurations(_def_size);
  }

  HashMap(size_t size)
  {
    set_configurations(size);
  }
  ///конструктор копирования
  HashMap(const HashMap& other):
    _size(other._size),
    _count_elements(other._count_elements),
    _lists(other._lists),
    _load_factor(other._load_factor)
  {}
  ///конструктор перемещения
  HashMap(HashMap&& other) = default;

  ~HashMap() = default;

};
