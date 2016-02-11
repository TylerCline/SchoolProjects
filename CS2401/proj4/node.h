//************************************
//Node class for doubly linked list
//Tyler Cline
//Ohio University 2014
//************************************


#ifndef NODE_H
#define NODE_H
#include<iostream>

template<class T>
class node{
    public:
     node(T d = T(), node *i = NULL, node* j=NULL)
        {next = i; previous = j;}

     void set_nxt(node *l)
        {next = l;}

     void set_prev(node *k)
        {previous = k;}

     node* nxt()const
        {return next;}

     node* prev()const
        {return previous;}

     void set_data(T data)
        {datafield = data;}

     T data()const
        {return datafield;}

    private:
        T datafield;
        node *next;
        node *previous;
};

#endif
