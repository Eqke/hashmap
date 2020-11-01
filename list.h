#include "unit.h"
template <class Data>
class List
{
private:
   Unit<Data>* _first;
   Unit<Data>* _last;
   void SetFirst(Unit<Data>*);
   void SetLast(Unit<Data>*);
public:
   Unit<Data>* GetFirst() const;
   Unit<Data>* GetLast() const;

   void PushBack(Unit<Data>* unit);
   void PushFront(Unit<Data>* unit);
   void PushBack(Data data);
   void PushFront(Data data);
   bool IsEmpty();

   List();
   ~List();


};
