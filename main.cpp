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
  map.insert(std::pair<std::string, int> ("apple",1));
  map.insert(std::pair<std::string, int> ("a",1));
  map.insert(std::pair<std::string, int> ("red",2));
  map.insert(std::pair<std::string, int> ("blue",3));
  map.insert(std::pair<std::string, int> ("red",4));
  map.insert(std::pair<std::string, int> ("apple",5));
  map.insert(std::pair<std::string, int> ("green",6));
  map.insert(std::pair<std::string, int> ("green",7));
  map.insert(std::pair<std::string, int> ("purple",7));
  map.insert(std::pair<std::string, int> ("fiolet",10));
  map.insert(std::pair<std::string, int> ("fiolet",10));
  map.insert(std::pair<std::string, int> ("level",10));
  for (auto it = map.begin(); it != map.end(); it++)
    {
    std::cout << it.operator*().first << " ";
    }
  std::cout << "\n" << map.count("fiolet") << "\n";
  map.erase("fiolet");
  for (auto it = map.begin(); it != map.end(); it++)
    {
    std::cout << it.operator*().first << " ";
    }
  std::cout << "\n" << map.count("fiolet") << "\n";
//  std::cout << "\n";
//  for (size_t i = 0; i < map.size(); i++)
//    {
//      std::cout << i << ": ";
//      map[i];
//    }
//  std::cout << "welcome" << "\n";
//    for (auto&& [key, value] : map) {
//        std::cout << key << " " << value << "\n";
//    }
}

