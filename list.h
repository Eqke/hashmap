
template<class Data>
class Unit
{
private:
  Unit<Data>* _nextPtr;
  Data _data;

public:
  Unit<Data>* GetNextPtr() const
  {
    return this->_nextPtr;
  }
  Data GetData() const
  {
    return this->_data;
  }
  void SetData(Data data)
  {
    this->_data = data;
  }
  void SetNextPtr(Unit* nextPtr)
  {
    this->_nextPtr = nextPtr;
  }
  Unit()
  {}
  Unit(Data data)
  {
    SetNextPtr(nullptr);
    SetData(data);
  }
  Unit(Data data, Unit* nextPointer)
  {
    SetNextPtr(nextPointer);
    SetData(data);
  }
  ~Unit()
  {}

};


template <class Data>
class List
{
private:
   Unit<Data>* _first;
   Unit<Data>* _last;
   void SetFirst(Unit<Data>* firstPtr)
   {
     this->_first = firstPtr;
   }
   void SetLast(Unit<Data>* lastPtr)
   {
     this->_last = lastPtr;
   }
public:
   Unit<Data>* GetFirst() const
   {
     return this->_first;
   }
   Unit<Data>* GetLast() const
   {
     return this->_last;
   }

   void PushBack(Unit<Data>* unit)
   {
     if (IsEmpty())
       {
         SetFirst(unit);
         SetLast(unit);
       }
     else
       {
         this->_last->SetNextPtr(unit);
         SetLast(unit);
       }
   }
   void PushFront(Unit<Data>* unit)
   {
     if (IsEmpty())
       {
         SetFirst(unit);
         SetLast(unit);
       }
     else
       {
         unit->SetNextPtr(GetFirst());
         SetFirst(unit);
       }
   }
   void PushBack(Data data)
   {
     Unit<Data>* newUnit = new Unit<Data>;
     newUnit->SetData(data);
     if (IsEmpty())
       {
         SetFirst(newUnit);
         SetLast(newUnit);
       }
     else
       {
         newUnit->SetNextPtr(GetLast());
         SetLast(newUnit);
       }
   }
   void PushFront(Data data)
   {
     Unit<Data>* newUnit = new Unit<Data>(data);
     newUnit->SetData(data);
     if (IsEmpty())
       {
         SetFirst(newUnit);
         SetLast(newUnit);
       }
     else
       {
         newUnit->SetNextPtr(GetFirst());
         SetFirst(newUnit);
       }
   }
   bool IsEmpty()
   {
     if (this->_first == nullptr && this->_last == nullptr)
       {
         return true;
       }
     else
       {
         return false;
       }
   }
   List()
   {
     SetFirst(nullptr);
     SetLast(nullptr);
   }
   ~List()
   {
     if (!IsEmpty())
       {
     Unit<Data>* nextUnit, deleteUnit;
     deleteUnit = GetFirst();
//     do
//       {
//         nextUnit = deleteUnit->GetNextPtr();
//         deleteUnit->SetNextPtr(nullptr);
//         delete deleteUnit;
//         deleteUnit = nextUnit;
//       }while(nextUnit!=nullptr);
     for(auto deleteUnit:*this)
       {
         deleteUnit->SetNextPtr(nullptr);
         delete deleteUnit;
       }
       }
   }


};
