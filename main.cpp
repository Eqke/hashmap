#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"
#include "hashmap.h"
#include <unordered_map>

int main()
{

  HashMap<std::string, int> map;
  map.Add("red",2);
  map.Add("red1",3);
  map.Add("red",4);
  map.Add("blue",1);
  std::cout << map["red"] << "\n";
  HashMap<std::string, int> mp = map;
  std::cout << map.Size() << " " << mp.Size();
  return 0;
}


