//***********************
//Lab 4
//Tyler Cline
//***********************

#include <iostream>

using namespace std;

class numbers{
     public:
             numbers();
             ~numbers();
             void insert(unsigned long large);
             void resize();
             void remove_last();
             void display();
             void operator =(const numbers& other);
         

      private:
              unsigned long *data;
              size_t used;
              size_t capacity;
};



numbers::numbers()
{ 
  used=0;
  capacity=5;
  data=new unsigned long[capacity];
}


void numbers::insert(unsigned long large)
{
  if(used == capacity)
   resize();
   
   data[used]=large;
   used++;
}
   
void numbers::resize()
{
   unsigned long *tmp;
   tmp=new unsigned long[capacity+5];
   copy(data, data+used, tmp);
   delete[]data;
   data=tmp;
   capacity+=5;
}

void numbers::remove_last()
{
 used--;
}

void numbers::display()
{
  for(int i=0; i<used; i++)
     {cout << data[i]<<" ";
      }
     cout<<endl;
}

void numbers::operator =(const numbers& other)
{ if(this==&other)
     return;
  delete[]data;
  used=other.used;
  capacity=other.capacity;
  data=new unsigned long[capacity];
  copy(other.data, other.data+used, data);
}

numbers::~numbers()
{
 delete []data;
}



