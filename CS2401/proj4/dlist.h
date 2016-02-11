//*******************************
//Universal doubly linked list class
//Tyler CLine
//Ohio University 2014
//******************************

#ifndef DLIST_H
#define DLIST_H
#include"node.h"
#include"iterator.h"
#include<iostream>

template<class T>
class dlist{
 public:
     typedef node_iterator<T> iterator;
     dlist();
     ~dlist();
     dlist(const dlist<T>& other);
     void operator = (const dlist<T>& other);
     void front_insert(const T& item);
     void rear_insert(const T& item);
     void front_remove();
     void rear_remove();
     void show();
     void reverse_show();
     int size();
//iterator functions

     iterator begin(){return iterator(head);}
     iterator end(){return iterator(NULL);}
     iterator r_begin(){return iterator(tail);}
     iterator r_end(){return iterator(NULL);}

//iterator inserts+remove

     void insert_before(iterator it, T item);
     void insert_after(iterator it, T item);
     void remove(iterator it);

 private:
     node<T> *head;
     node<T> *tail;
};

#include"dlist.template"
#endif // D_LIST
