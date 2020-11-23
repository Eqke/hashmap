#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"
#include "hashmap.h"
#include <unordered_map>
#include <string>

int main()
{
  HashMap<std::string, int> map;
  map.insert("apple",1);
  map.insert("a",1);
  map.insert("red",2);
  map.insert("blue",3);
  map.insert("red",4);
  map.insert("apple",5);
  map.insert("green",6);
  map.insert("green",7);
  map.insert("purple",7);
  map.insert("fiolet",10);
  map.insert("fiolet",10);
  map.insert("level",10);
  for (auto it = map.begin(); it != map.end(); it++)
    {
    std::cout << it.operator*().first << " ";
    }
  std::cout << "\n";
  for (size_t i = 0; i < map.capacity(); i++)
    {
      std::cout << i << ": ";
      map[i];
    }
  std::cout << "welcome" << "\n";
}

