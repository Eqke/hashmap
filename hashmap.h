#pragma once
#include <vector>
#include <forward_list>
#include <string.h>
#include <iostream>
#include <exception>

template<class data>
class HashMap
{
private:
  unsigned int _countElements;
  size_t _size;
  std::vector<std::forward_list<std::pair<char*,data>>> _lists;
  static constexpr size_t _defSize = 4;
  int HashFunction(char* key);
public:
  std::vector<std::forward_list<std::pair<char*,data>>*> GetHashMap() const;
  size_t GetSize() const;


  void SetCountElements(int countElements);
  void SetSize(int size);
  void SetList();

  HashMap();
  ~HashMap();
};
