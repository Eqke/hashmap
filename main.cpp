#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"
#include "hashmap.h"
#include <unordered_map>

int main()
{
    HashMap<std::string, int> map;
    map.insert("apple",4);
    map.insert("red",2);
    map.insert("blue",3);
    map.insert("red",3);
    map.insert("apple",4);
    map.insert("green",4);
    map.insert("green",4);
    for (size_t i = 0; i < map.capacity();i++)
      {
        std::cout << i << " ";
        map[i];
      }
    map.erase("apple");
    for (size_t i = 0; i < map.capacity();i++)
      {
        std::cout << i << " ";
        map[i];
      }
//  std::unordered_map<std::string, int> map;

//  map.insert(std::make_pair<std::string, int>("red",5));
//  map.insert(std::make_pair<std::string, int>("red",3));
//  map.insert(std::make_pair<std::string, int>("red",4));
//  map.insert(std::make_pair<std::string, int>("blue",9));
//  map.insert(std::make_pair<std::string, int>("blue",10));
//  map.insert(std::make_pair<std::string, int>("green",7));
//  std::cout << map.end()->first << " " << map.end()->second;
}

