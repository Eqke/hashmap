#include "list.h"

template<class Data>
void List<Data>::SetFirst(Unit<Data>* firstPtr)
{
  this->_first = firstPtr;
}

template<class Data>
void List<Data>::SetLast(Unit<Data>* lastPtr)
{
  this->_last = lastPtr;
}

template<class Data>
Unit<Data>* List<Data>::GetFirst() const
{
  return this->_first;
}

template<class Data>
Unit<Data>* List<Data>::GetLast() const
{
  return this->_last;
}

template <class Data>
bool List<Data>::IsEmpty()
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

template<class Data>
void List<Data>::PushBack(Unit<Data>* unit)
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

template<class Data>
void List<Data>::PushFront(Unit<Data>* unit)
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
template<class Data>
void List<Data>::PushBack(Data data)
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

template<class Data>
void List<Data>::PushFront(Data data)
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
