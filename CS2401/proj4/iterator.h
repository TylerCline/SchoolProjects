#ifndef ITERATOR_H
#define ITERATOR_H
#include"node.h"
#include<iostream>
template<class T>
class dlist;
template<class T>
class node_iterator{
  public:
      node_iterator(){ptr=NULL;}
      node_iterator(node<T> *init)
        { ptr = init;}

      bool operator !=(const node_iterator& other)
        {return (ptr!=other.ptr);}

      bool operator ==(const node_iterator& other)
        {return (ptr == other.ptr);}

      T operator *()
        {return (ptr->data());}

      node_iterator operator ++()
        {
         ptr = ptr->nxt();
         return *this;
        }
      node_iterator operator --()
         {
          ptr = ptr->prev();
          return *this;
         }


       node_iterator operator ++(int)
         {
          node_iterator original(*this);
          ptr = ptr->nxt();
          return original;
         }
       node_iterator operator --(int)
         {
          node_iterator original2(*this);
          ptr = ptr->prev();
          return original2;
         }

       friend class dlist<T>;

  private:
      node<T> *ptr;
};
#endif // ITERATOR_H

