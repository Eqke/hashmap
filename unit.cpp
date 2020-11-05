#include "unit.h"

template <class Data>
void Unit<Data>::SetData(Data data)
{
  this->_data = data;
}

template <class Data>
void Unit<Data>::SetNextPtr(Unit* nextPtr)
{
  this->_nextPtr = nextPtr;
}
template<class Data>
Unit<Data>* Unit<Data>::GetNextPtr() const
{
  return this->_nextPtr;
}

template<class Data>
Data Unit<Data>::GetData() const
{
  return this->_data;
}

template<class Data>
Unit<Data>::Unit(Data data)
{
  SetNextPtr(nullptr);
  SetData(data);
}

template<class Data>
Unit<Data>::Unit(Data data, Unit* nextPointer)
{
  SetNextPtr(nextPointer);
  SetData(data);
}

