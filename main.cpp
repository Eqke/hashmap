#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"
#include "hashmap.h"
#include <unordered_map>

int main()
{
  HashMap<std::string, int> map;
  map.insert("red",2);
  map.insert("blue",3);
  map.insert("red",3);
  map.insert("green",4);
  map.insert("red",3);
  map.insert("green",4);
//  HashMap<int, int> map;
//  map.insert(3,2);
//  map.insert(2,3);
//  map.insert(5,3);
//  map.insert(6,4);
//  map.insert(7,3);
//  map.insert(2,4);
//  for (size_t i = 0; i < map.Max_size();i++)
//    {
//      map[i];
//    }
//  for (size_t i = 0; i < map.Max_size();i++)
//    {
//      map[i];
//    }
  //std::cout << std::is_arithmetic_v<std::string>;
  return 0;
}


