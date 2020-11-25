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
  std::cout << pair.second << "\n";
  pair = map.insert(std::pair<std::string, int> ("red",4));
  std::cout << pair.second << "\n";
  map.insert(std::pair<std::string, int> ("green",2));
  map.insert(std::pair<std::string, int> ("green",5));
  map.insert(std::pair<std::string, int> ("blue",2));
  map.insert(std::pair<std::string, int> ("fiolet",2));
  for (auto it = map.begin(); it != map.end(); it++)
    {
      std::cout << it.operator*().first << " " << it.operator*().second << "\n";
    }
  std::cout << map.count("red") << " " << map.count("purple") << "\n";
  map.erase("blue");
  map.erase("re");
  for (auto it = map.begin(); it != map.end(); it++)
    {
      std::cout << it.operator*().first << " " << it.operator*().second << "\n";
    }
  //::cout << map.find("red").operator*().second << "\n";
//  std::cout << map.find("r").operator*().second << "\n";
  std::cout << map["green"] << "\n";
//  map.insert(std::make_pair<std::string, int> ("apple",1));
//  map.insert(std::pair<std::string, int> ("a",1));
//  map.insert(std::pair<std::string, int> ("red",2));
//  map.insert(std::pair<std::string, int> ("blue",3));
//  map.insert(std::pair<std::string, int> ("red",4));
//  map.insert(std::pair<std::string, int> ("apple",5));
//  map.insert(std::pair<std::string, int> ("green",6));
//  map.insert(std::pair<std::string, int> ("green",7));
//  map.insert(std::pair<std::string, int> ("purple",7));
//  map.insert(std::pair<std::string, int> ("fiolet",10));
//  map.insert(std::pair<std::string, int> ("fiolet",10));
//  map.insert(std::pair<std::string, int> ("level",10));
//  std::cout << map.erase("green");
//  for (auto it = map.begin(); it != map.end(); it++)
//    {
//    std::cout << it.operator*().first << " ";
//    }
//   std::cout << map["green"] << "\n";
//  std::cout << "\n" << map.count("fiolet") << "\n";
//    map.erase("fiolet");
//  for (auto it = map.begin(); it != map.end(); it++)
//    {
//    std::cout << it.operator*().first << " ";
//    }
//  std::cout << "\n" << map.count("fiolet") << "\n";
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
//  auto find = map.find("appl");
//  if(find != map.end())
//    {
//  std::cout << find.operator*().first << "";
//    }
//  std::unordered_map<std::string, int> map1;
//  auto it = map1.begin();
//  auto it_end = map1.end();
//  auto pair1 = map1.insert(std::pair<std::string, int> ("r",2));
//  std::cout << pair1.second << "\n";
//  pair1 = map1.insert(std::pair<std::string, int> ("r",5));
//  std::cout << pair1.second << "\n";
//  std::cout << map1["r"] << "\n";
}

