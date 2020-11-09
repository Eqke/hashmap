
template<class Data>
class Node
{
private:
  Node<Data>* _nextPtr;
  Data _data;

public:
  Node<Data>* GetNextPtr() const
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
  void SetNextPtr(Node* nextPtr)
  {
    this->_nextPtr = nextPtr;
  }
  Node()
  {}
  Node(Data data)
  {
    SetNextPtr(nullptr);
    SetData(data);
  }
  Node(Data data, Node* nextPointer)
  {
    SetNextPtr(nextPointer);
    SetData(data);
  }
  ~Node()
  {}

};


template <class Data>
class List
{
private:
   Node<Data>* _first;
   Node<Data>* _last;
   void SetFirst(Node<Data>* firstPtr)
   {
     this->_first = firstPtr;
   }
   void SetLast(Node<Data>* lastPtr)
   {
     this->_last = lastPtr;
   }
public:
   Node<Data>* GetFirst() const
   {
     return this->_first;
   }
   Node<Data>* GetLast() const
   {
     return this->_last;
   }

   void PushBack(Node<Data>* node)
   {
     if (IsEmpty())
       {
         SetFirst(node);
         SetLast(node);
       }
     else
       {
         this->_last->SetNextPtr(node);
         SetLast(node);
       }
   }
   void PushFront(Node<Data>* node)
   {
     if (IsEmpty())
       {
         SetFirst(node);
         SetLast(node);
       }
     else
       {
         node->SetNextPtr(GetFirst());
         SetFirst(node);
       }
   }
   void PushBack(Data data)
   {
     Node<Data>* newNode = new Node<Data>;
     newNode->SetData(data);
     if (IsEmpty())
       {
         SetFirst(newNode);
         SetLast(newNode);
       }
     else
       {
         newNode->SetNextPtr(GetLast());
         SetLast(newNode);
       }
   }
   void PushFront(Data data)
   {
     Node<Data>* newNode = new Node<Data>(data);
     newNode->SetData(data);
     if (IsEmpty())
       {
         SetFirst(newNode);
         SetLast(newNode);
       }
     else
       {
         newNode->SetNextPtr(GetFirst());
         SetFirst(newNode);
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
     Node<Data>* nextNode, deleteNode;
     deleteNode = GetFirst();
//     do
//       {
//         nextNode = deleteNode->GetNextPtr();
//         deleteNode->SetNextPtr(nullptr);
//         delete deleteNode;
//         deleteNode = nextNode;
//       }while(nextNode!=nullptr);
     for(auto deleteNode:*this)
       {
         nextNode = deleteNode->GetNextPtr();
         deleteNode->SetNextPtr(nullptr);
         delete deleteNode;
       }
       }
   }


};
