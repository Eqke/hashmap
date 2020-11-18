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
  map.insert("red",2);
  map.insert("blue",3);
  map.insert("red",4);
  map.insert("apple",5);
  map.insert("green",6);
  map.insert("green",7);
//  std::cout << map.at("appl") << "\n";
//  auto node = map.begin();
//  std::cout << map["green"] << "\n";
//  for (size_t i = 0; i < map.capacity();i++)
//    {
//      std::cout << i << " ";
//      map[i];
//    }
//  map.erase("apple");
//  for (auto it = map.begin(); it != map.end(); it++)
//    {

//    }
//  std::unordered_map<std::string, int> map;

//  map.insert(std::make_pair<std::string, int>("red",5));
//  map.insert(std::make_pair<std::string, int>("red",3));
//  map.insert(std::make_pair<std::string, int>("red",4));
//  map.insert(std::make_pair<std::string, int>("blue",9));
//  map.insert(std::make_pair<std::string, int>("blue",10));
//  map.insert(std::make_pair<std::string, int>("green",7));
//  auto node = map.begin();
//  for(auto node: map)
//    {
//      std::cout << node.first << " " << node.second << "\n";
//    }
}

