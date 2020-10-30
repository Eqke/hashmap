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
  unsigned int _size;
  std::vector<std::forward_list<data>* > _lists();
  const unsigned int _defSize = 4;
  key HashFunction(key);
public:
  int GetCountElements() const;
  std::vector<std::forward_list<std::pair<key,data>>*> GetList() const;
  int GetSize() const;


  void SetCountElements(int countElements);
  void SetSize(int size);

  HashMap();
  ~HashMap();
};
