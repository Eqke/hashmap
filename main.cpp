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
  auto pair = map.insert(std::pair<std::string, int> ("red",2));
  std::cout << "status insert" << "\n";
  std::cout << pair.second << "\n";
  pair = map.insert(std::pair<std::string, int> ("red",4));
  std::cout << pair.second << "\n";
  auto it = pair.first;
  map.insert(std::pair<std::string, int> ("green",2));
  map.insert(std::pair<std::string, int> ("green",5));
  map.insert(std::pair<std::string, int> ("blue",2));
  map.insert(std::pair<std::string, int> ("fiolet",8));
  map.insert(std::pair<std::string, int> ("appl",4));
  std::cout << "key access" << "\n";
  std::cout << map["fiolet"] << " " << map.at("appl") << "\n";
  std::cout << "iterator 1 work" << "\n";
  for (auto&& [key, value] : map) {
        std::cout << key << " " << value << "\n";
    }
  std::cout << "delete status\n";
  std::cout << map.erase("green") << "\n";
  std::cout << "iterator 2 work" << "\n";
  for (auto it = map.begin(); it != map.end(); it++)
    {
      std::cout << it.operator*().first << " " << it.operator*().second << "\n";
    }
  auto find_eleme = map.find("fiolet");
  if (find_eleme != map.end())
    {
      std::cout << find_eleme.operator*().first << " " << find_eleme.operator*().second << "\n";
    }
}

