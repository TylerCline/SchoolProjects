//************************************
//Linked List Projects
//Tyler Cline
//Ohio University 2014
//************************************
#include<iostream>
#include<string>
#include "course.h"
#include "node.h"
#ifndef LLIST_H
#define LLIST_H


class llist{
      public:
          llist();
          ~llist();
          llist(const llist& other);
          void operator = (const llist& other);
          void add_class();
          void add_node(course c);
          void show_all();
          void insert(const course& a);
          void remove_course(std::string& target);
          void hours_taken();
          void gpa();
          void save_to_file(std::ostream& out);
          void load_from_file(std::istream& fins);



      private:
           node *head;
};
#endif
