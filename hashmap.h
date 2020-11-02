#pragma once
#include <vector>
#include <forward_list>
#include <exception>

template<class Key,
         class Data>
class HashMap
{
private:
  unsigned int _countElements;
  size_t _size;
  std::vector<std::forward_list<std::pair<char *,Data>>> _lists;
  static constexpr size_t _defSize = 4;

  size_t HashFunction(char* key);
  void SetCountElements(int countElements);
  void SetListConfigurations(int size);
  std::vector<std::forward_list<std::pair<char *,Data>>> GetHashMap() const;
  size_t GetSize() const;
//  void SetList(size_t size);
public:

  bool IsEmpty();
  size_t size();
  size_t max_size();






  HashMap();
  ~HashMap();
};
