using namespace cop4530;

//TB - Textbook
//mine - I wrote it
//-------------------------------------------------
//nested const_iterator class

template <typename T> //TB
List<T>::const_iterator::const_iterator() : current{ nullptr }
{}

template <typename T> //TB
const T & List<T>::const_iterator::operator*() const
{return retrieve( ); }

template <typename T> //prefix //TB
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
  current = current->next;
  return *this;
}

template <typename T> //postfix //TB
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  const_iterator old = *this;
  ++( *this );
  return old;
}

template <typename T> //prefix //TB
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
  current = current->prev;
  return *this;
}

template <typename T> //postfix //TB
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  const_iterator old = *this;
  --( *this );
  return old;
}

template <typename T> //TB
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{return current == rhs.current;}

template <typename T> //TB
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{return !( *this == rhs );}

template <typename T> //TB
T & List<T>::const_iterator::retrieve() const
{return current->data;}

template <typename T> //TB
List<T>::const_iterator::const_iterator(Node *p) : current{ p }
{}
//-------------------------------------------------
//nested iterator class

template <typename T> //TB
List<T>::iterator::iterator()
{}

template <typename T> //TB
T & List<T>::iterator::operator*()
{return const_iterator::retrieve( );}

template <typename T> //TB
const T & List<T>::iterator::operator*() const
{return const_iterator::operator*( );}

// increment/decrement operators
template <typename T> //prefix //TB
typename List<T>::iterator & List<T>::iterator::operator++()
{
  this->current = this->current->next;
  return *this;
}

template <typename T> //postfix //TB
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  iterator old = *this;
  ++( *this );
  return old;
}

template <typename T> //prefix
typename List<T>::iterator & List<T>::iterator::operator--()
{
  this->current = this->current->prev;
  return *this;
}

template <typename T> //postfix //TB
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  iterator old = *this;
  --( *this );
  return old;
}

template <typename T> //TB
List<T>::iterator::iterator(Node *p) : const_iterator{ p }
{}

//-------------------------------------------------
//List class

template <typename T> //TB
List<T>::List()
{init( );}

template <typename T> //TB
List<T>::List(const List &rhs)   // copy constructor
{
  init( );
  for( auto & x : rhs )
    push_back( x );
}

template <typename T> //TB
List<T>::List(List && rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }      // move constructor
{
  rhs.theSize = 0;
  rhs.head = nullptr;
  rhs.tail = nullptr;
}

// num elements with value of val
template <typename T> //mine
List<T>::List(int num, const T& val)
{
  init();
  for (int i = 0; i < num; i++)
    push_back(val);
}

// constructs with elements [start, end)
template <typename T> //mine //might not work bc early data might equal end
List<T>::List(const_iterator start, const_iterator end)
{
  init();
  while(start.current->data != end.current->data)
  {
    push_back(start.current->data);
    start++;
  }
}

// constructs with a copy of each of the elements in the initalizer_list
template <typename T> //mine
List<T>::List(std::initializer_list<T> iList)
{
  init();
  for(const auto& val: iList)
    push_back(val);
}


template <typename T> //TB
List<T>::~List() // destructor
{
  clear( );
  delete head;
  delete tail;
}

// copy assignment operator
template <typename T> //TB
const List<T>& List<T>::operator=(const List &rhs)
{
  List copy = rhs;
  std::swap( *this, copy );
  return *this;
}

// move assignment operator
template <typename T> //TB
List<T> & List<T>::operator=(List && rhs)
{
  std::swap( theSize, rhs.theSize );
  std::swap( head, rhs.head );
  std::swap( tail, rhs.tail );
  return *this;
}

// sets list to the elements of the initializer_list
template <typename T> //mine
List<T>& List<T>::operator= (std::initializer_list<T> iList)
{
  clear();
  for(const auto& val: iList)
    push_back(val);
  return *this;
}


// member functions
template <typename T> //TB
int List<T>::size() const       // number of elements
{return theSize;}

template <typename T> //TB
bool List<T>::empty() const     // check if list is empty
{return (size() == 0);}

template <typename T> //TB
void List<T>::clear()           // delete all elements
{
  while( !empty() )
    pop_front( );
}

template <typename T> //mine
void List<T>::reverse()         // reverse the order of the elements
{
  List<T> temp;
  iterator itr = end();
  itr--;
  for (int i = 0; i < theSize; i++) {
    temp.push_back(*itr);
    itr--;
  }
  *this = temp;
}

template <typename T> //TB
T& List<T>::front()             // reference to the first element
{return *begin( );}

template <typename T> //TB
const T& List<T>::front() const
{return *begin( );}

template <typename T> //TB
T& List<T>::back()              // reference to the last element
{return *--end( );}

template <typename T> //TB
const T& List<T>::back() const
{return *--end( );}

template <typename T> //TB
void List<T>::push_front(const T & val) // insert to the beginning
{insert( begin( ), val ); }

template <typename T> //TB
void List<T>::push_front(T && val)      // move version of insert
{insert( begin( ), std::move( val ) ); }

template <typename T> //TB
void List<T>::push_back(const T & val)  // insert to the end
{insert( end( ), val );}

template <typename T> //TB
void List<T>::push_back(T && val)       // move version of insert
{insert( end( ), std::move( val ) ); }

template <typename T> //TB
void List<T>::pop_front()               // delete first element
{erase( begin( ) ); }

template <typename T> //TB
void List<T>::pop_back()                // delete last element
{ erase( --end( ) ); }

template <typename T> //mine might work?
void List<T>::remove(const T &val)      // remove all elements with value = val
{
  iterator itr = begin();
  for (auto i = 0; i < theSize; i++) {
    if(itr.retrieve() == val)
      itr = erase(itr);
    else itr++;
  }
}

template <typename T> //mine
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
// remove all elements for which Predicate pred
// returns true. pred can take in a function object
{
  iterator itr = begin();
  int startSize = size();
  for (int i = 0; i < startSize; i++)
  {
    if(pred(itr.retrieve()))
      itr = erase(itr);
    else itr++;
  }
}


// print out all elements. ofc is deliminitor
template <typename T> //mine
void List<T>::print(std::ostream& os, char ofc) const
{
  const_iterator itr = begin();
  for (auto i = 0; i < theSize; i++) {
    os<<itr.current->data<<ofc;
    itr++;
  }
}

template <typename T> //TB
typename List<T>::iterator List<T>::begin()               // iterator to first element
{return iterator( head->next );}

template <typename T> //TB
typename List<T>::const_iterator List<T>::begin() const
{return const_iterator( head->next );}

template <typename T> //TB
typename List<T>::iterator List<T>::end()                 // end marker iterator
{return iterator( tail );}

template <typename T> //TB
typename List<T>::const_iterator List<T>::end() const
{return const_iterator( tail );}

template <typename T> //TB
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)  // insert val ahead of itr
{
  Node *p = itr.current;
  ++theSize;
  return iterator( p->prev = p->prev->next = new Node{ val, p->prev, p } );

}

template <typename T> //TB
typename List<T>::iterator List<T>::insert(iterator itr, T && val)      // move version of insert
{
  Node *p = itr.current;
  ++theSize;
  return iterator( p->prev = p->prev->next = new Node{ std::move( val ), p->prev, p } );
}

template <typename T> //TB
typename List<T>::iterator List<T>::erase(iterator itr)                 // erase one element
{
  Node *p = itr.current;
  iterator retVal( p->next );
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  --theSize;
  return retVal;
}

template <typename T> //TB
typename List<T>::iterator List<T>::erase(iterator start, iterator end) // erase [start, end)
{
  for( iterator itr = start; itr != end; )
      itr = erase( itr );
  return end;
}

template <typename T> //TB
void List<T>::init()
{
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}

// overloading comparison operators
template <typename T> //mine
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
  typename cop4530::List<T>::const_iterator lhsItr = lhs.begin();
  typename cop4530::List<T>::const_iterator rhsItr = rhs.begin();
  if (lhs.size() != rhs.size())
    return false;
  else
  {
    for (int i = 0; i < lhs.size(); i++)
    {
      if(*lhsItr != *rhsItr)
        return false;
      lhsItr++;
      rhsItr++;
    }
    return true;
  }
}

template <typename T> //mine
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{return !(lhs == rhs);}

// overloading output operator
template <typename T> //mine
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
  l.print(os);
  return os;
}
