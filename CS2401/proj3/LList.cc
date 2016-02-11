//***************************
//Implementation for llist class
//Tyler Cline
//Ohio University 2014
//***************************

#include <iostream>
#include <string>
#include "course.h"
#include "LList.h"
#include "node.h"
using namespace std;

llist::llist()
{
 head = NULL;
}

llist::~llist()
{
    node *rmptr;
    while(head != NULL)
     {
      rmptr = head;
      head = head->link();
      delete rmptr;
     }
}

llist::llist(const llist& other)
{ node *cursor;
  cursor = other.head;

    while(cursor != NULL)
    {
     insert(cursor->data());
     cursor = cursor->link();
    }
}

void llist::insert(const course& a)
{
 node *ptr;
 ptr = new node(a, NULL);
}

void llist::operator = (const llist& other)
{
 if(this == &other)
    {return;}

 node *tmp;
    while(head != NULL)
     {
       tmp = head;
       head = head->link();
       delete tmp;
     }
    if(other.head == NULL)
        head = NULL;
    else
     {
      node *sptr, *dptr;
      head = new node(other.head->data());
      sptr = other.head->link();
      dptr = head;

        while(sptr != NULL)
         {
            dptr->set_link(new node (sptr->data()));
            dptr = dptr->link();
            sptr = sptr->link();
         }
     }
}

void llist::add_class()
{
 course class1;
 class1.input(cin);
 add_node(class1);
}

void llist::add_node(course  c)
{
    if(head == NULL)
     {
      head = new node(c, NULL);
     }

    else
     {node *cursor, *previous;
      if(c < head->data())
        {
         cursor = head;
         head = new node(c, cursor);
        }
      else
       {
          cursor = head;
          while(cursor->link() != NULL && cursor->data() < c)
         {
           previous = cursor;
           cursor = cursor->link();
         }
         if(cursor->data()<c)
         {
           node *tmp;
           tmp = cursor->link();
           cursor->set_link(new node(c, tmp));
         }
         else
           {
             node* tmp2;
             tmp2 = cursor;
             previous->set_link(new node(c, tmp2));
           }
      }
   }
}


void llist::show_all()
{
     for(node *tmp = head; tmp != NULL; tmp = tmp->link())
        cout << tmp->data() <<endl;
}


void llist::remove_course(string& target)
{ node *rmptr, *previous;

  if(head -> data().get_course_number() == target)
    {
      rmptr = head;
      head = head->link();
      delete rmptr;

    }
  else
    {
      rmptr = head;
      while(rmptr != NULL && rmptr->data().get_course_number() != target)
       {
          previous = rmptr;
          rmptr = rmptr->link();
       }
          if(rmptr != NULL)
           {
             previous->set_link(rmptr->link());
             delete rmptr;
           }

    }
 }


void llist::hours_taken()
{  double sum=0;
   for(node *tmp = head; tmp != NULL; tmp = tmp->link())
   {
       sum += tmp->data().get_hours();
   }
   cout<<sum;
}

void llist::gpa()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    double sum=0, total_hours=0;
    double average;
    node *tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->link())
      {
        sum = sum+ (tmp->data().get_hours() * tmp->data().get_number_grade());
        total_hours += tmp->data().get_hours();
      }
        average = sum / total_hours;
        cout << "GPA: "<< average << endl;
}


void llist::load_from_file(istream& fins)
 {
   course tmp;
   tmp.input(fins);
    while(!fins.eof())
     {add_node(tmp);
      tmp.input(fins);
     }
 }


void llist::save_to_file(ostream& out)
{

  for(node *tmp = head; tmp != NULL; tmp = tmp->link())
     out <<  tmp->data();

}

