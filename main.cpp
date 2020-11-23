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
  auto node = map.begin();
  auto nodeEnd = map.end();
  auto ptrnode = *node;
//std::cout;
//  std::cout << map["green"] << "\n";
  for (size_t i = 0; i < map.capacity();i++)
    {
      std::cout << i << " ";
      map[i];
    }
//  map.erase("apple");
  for (size_t i = 0; i < map.capacity();i++)
    {
      std::cout << i << " ";
      map[i];
    }

  for (auto it = map.begin(); it != map.end(); it++)
    {
    std::cout << it.operator*().first << " ";
    }
  std::cout << "\n";
  for (auto it : map)
    {
    std::cout << it.first << " ";
    }
  std::cout << "\n";
  for (auto it = map.end(); it != map.begin(); it--)
    {
    std::cout << it.operator*().first << " ";
    }
//  std::vector<int> vec;
//  vec.push_back(5);
//  vec.push_back(2);
//  vec.push_back(8);
//  for (auto it = vec.end(); it != vec.begin(); it--)
//    {
//      std::cout << *it << " ";
//    }
//  std::forward_list<std::pair<int, int>> list1;
//  auto it_begin = list.begin();
//  auto it_end = list.end();
//std::cout << list.empty() << " " << list1.empty();

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

//  std::forward_list<int> list1;
//  std::forward_list<int> list2;
//  list1.push_front(1);
//  std::cout << list1.empty() << " " << list2.empty();
}

