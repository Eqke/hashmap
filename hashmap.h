#pragma once
#include <vector>
#include <forward_list>
///
/// @Hashmap - класс hashmap
/// @key - ключ
/// @data - содержание/значение/данные
///
template<class key, class data>
class HashMap
{
private:
  unsigned int _countElements;
  size_t _size;
  std::vector<std::forward_list<std::pair<key,data>> > _lists;
  const size_t _defSize = 4;
  auto HashFunction(key);
public:
  std::vector<std::forward_list<std::pair<key,data>>*> GetList() const;
  size_t GetSize() const;


  void SetCountElements(unsigned int countElements);
  void SetSize(size_t size);

  HashMap();
  ~HashMap();
};
