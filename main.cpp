#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"
#include "hashmap.h"
#include <unordered_map>

int main()
{
//  HashMap<std::string, int> map;
//  map.insert("red",2);
//  map.insert("blue",3);
//  map.insert("red",3);
//  map.insert("appl",4);
//  map.insert("green",4);
//  map.insert("green",4);
//  for (size_t i = 0; i < map.Max_size();i++)
//    {
//      std::cout << i << " ";
//      map[i];
//    }
//  HashMap<std::string, int> map1 = map;
//  for (size_t i = 0; i < map.Max_size();i++)
//    {
//      std::cout << i << " ";
//      map1[i];
//    }
  std::unordered_map<std::string, int> map2;
  map2.insert(std::pair<std::string, int> ("2",3));
  std::cout << map2.size() << " " << map2.max_size();
}

