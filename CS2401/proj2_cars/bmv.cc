//*******************************
//Implementation for BMV class
//Tyler Cline
//Ohio University 2014
//*******************************
#include<iostream>
#include"vehicle.h"
#include"bmv.h"
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

//constructor
bmv::bmv()
{
    capacity = 5;
    used = 0;
    current_item = 0;
    ptr = new vehicle[capacity];
}

//Destructor
bmv::~bmv()
{
    delete[] ptr;
}

//copy constructor
bmv::bmv(const bmv& other)
{
    used = other.used;
    capacity = other.capacity;
    current_item = other.current_item;
    ptr = new vehicle[capacity];
    copy(other.ptr, other.ptr+used, ptr);
}

//Function to read in from a file
/*void bmv::load_from_file(istream& ins)
{
  vehicle tmp;
  ins >> tmp;

  while(!ins.eof())
    ins >> tmp;
    used++;
}*/

//Function to save to a file
void bmv::save_to_file(ostream& out)
{
  vehicle tmp;

  for(int i=0; i<used; i++)
     out << tmp;

}

void bmv::start()
{
 current_item=0;
}

bool bmv::is_item()
{
 return current_item<used;
}

void bmv::advance()
{
  if(is_item())
    current_item++;
}

vehicle& bmv::current()
{
  return ptr[current_item];
}

//Function to insert a vehicle in a part of the array before the index
void bmv::insert(vehicle& car)
{
    if (used == capacity)
      {
         resize();
      }
        if(!is_item())
          {
            current_item=0;
          }
        for(int i=used; i>current_item; i++)
          {
            ptr[i]=ptr[i-1];
          }
       ptr[current_item]=car;
       used++;

}

//function to attach an item to the array after the selected index
void bmv::attach(vehicle& cars)
{
   if(used == capacity)
     {
       resize();
     }
   if(!is_item())
     {
       ptr[used]=cars;
       used++;
     }
   else
     {
       for(int i=used; i > current_item+1; i--)
       {
           ptr[i]=ptr[i-1];
       }
       ptr[current_item+1]=cars;
       current_item++;
     }
}

//Function to output an item depending on license plate number entered
void bmv::show_item(string& license_num)
{
   for(int i=0; i<used; i++)
      { if (license_num == ptr[i].get_tag())
           {cout << "Owner: "<< ptr[i].owner() << endl;
            cout << "Tag: "<< ptr[i].get_tag() << endl;
            cout << "Year: " << ptr[i].get_year()<<endl;
            cout << "Make: "<< ptr[i].get_make()<<endl;
            cout << "Model: "<<ptr[i].get_model()<<endl;
           }

        else
            cout << "No cars with that tag "<<endl;

      }
}


//Function to remove the current item from the array
void bmv::remove_current()
{
  if(is_item())
  {
      for(int i = current_item; i < used; i++)
         {
          ptr[i] = ptr[i+1];
         }
      used--;
  }
}

//Function to find a random car
void bmv::random_car()
{ size_t tmp;
  tmp=rand()%used;
  cout<< ptr[tmp];
}

//Function to add more space to the array
void bmv::resize()
{
   vehicle *tmp;
   tmp=new vehicle[capacity+5];
   copy(ptr, ptr+used, tmp);
   delete[]ptr;
   ptr=tmp;
   capacity+=5;
}

size_t bmv::size()
{
    return(used);
}


