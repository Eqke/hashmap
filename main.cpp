#include <iostream>
#include <vector>
#include <forward_list>
#include "list.h"

int main()
{
    List<int>* list = new List<int>;
    list->PushFront(6);
    list->PushBack(4);
    Unit<int>* unit = list->GetFirst();
    while(unit != nullptr)
      {
        std::cout << unit->GetData() << " ";
        unit = unit->GetNextPtr();
      }
    return 0;
}
