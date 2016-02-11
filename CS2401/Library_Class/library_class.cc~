//*************************************
//Implementation File for library_class
//Tyler Cline	2014
//Ohio University
//*************************************

#include "library_class.h"
#include "book_class.h"
#include <iostream>
#include <string>
using namespace std;

library::library()
{
 used=0;
}


void library::insert_book(book& book1)
{   string str1, str2;
    int i1, i2;

 if( used < CAPACITY ){

     array[used].set_title(str1);
     array[used].set_author(str2);
     array[used].set_copyright_date(i1);
     array[used].set_number_of_pages(i2);
      used++;}
 else
   cout<<endl<<"Library is full"<<endl<<endl;

}
// function to add a book to the collection of books


void library::total_pages(ostream& pages_out)
{
 int sum = 0;
 book b1;

 pages_out << "All pages " << endl;

 for (int i=0; i < used; i++)
    {
     sum = sum + array[i].get_number_of_pages();
    }


 cout<< "The total number of pages for all books is " << sum<<endl<<endl;
}

//function to output the total number of pages in the collection

//ostream& operator << (ostream& c_out, library& b1)
//{
//    {c_out << b1.array[]};
//    return c_out;

//}
void library::show_all_books(ostream& books_out)
{
  for (int i=0; i < used; i++)
    {
     books_out << array[i].get_title()<<endl;
     books_out << array[i].get_author()<<endl;
     books_out << array[i].get_copyright_date()<<endl;
     books_out << array[i].get_number_of_pages()<<endl<<endl;
    }
}
// Function to show every book in the collection


void library::sort_by_title()
{
 bool done=false;
 book tmp;

 while(!done)
   { done=true;
       for(int i=0; i < used-1; i++)
        {  if(array[i].get_title() > array[i+1].get_title())
             { done=false;
              tmp=array[i];
              array[i]=array[i+1];
              array[i+1]=tmp;
             }
        }
   }
}
//Function to sort through the books by author


void library::sort_by_date()
{
 bool done=false;
 book tmp;

 while(!done)
   { done=true;
       for(int i=0; i < used-1; i++)
        {  if(array[i].get_copyright_date() > array[i+1].get_copyright_date())
             {done=false;
              tmp=array[i];
              array[i]=array[i+1];
              array[i+1]=tmp;
             }
        }
   }
}
//Function to sort through the books by copyright date

void library::searchtitle(ostream& tout)
{
string target1;
cout<<"Search for a title--> ";
if(cin.peek()=='\n')cin.ignore();
getline(cin, target1);

 for(int i=0; i<used; i++)
      { if (target1 == array[i].get_title())
           {tout << "Title: "<< array[i].get_title() << endl;
            tout << "Author: "<< array[i].get_author() << endl;
            tout << "Copyright-Date: " << array[i].get_copyright_date()<<endl;
            tout << "Number of Pages: "<< array[i].get_number_of_pages()<<endl;
           }

        else
             tout << "No titles with that name "<<endl;
          
      }
}
//Function to search for a particular title depending on user input

void library::output_by_author(ostream& author_out)
{
 string target1;
 bool b=false;
 cout<<"Search for an author--> ";
 if(cin.peek()=='\n')cin.ignore();
 getline(cin, target1);

 for(int i=0; i<used; i++)
      {
           if (target1 == array[i].get_author())
             author_out << "Title: "<< array[i].get_title() << endl;
             
      }
}
void library::remove_element()
{
 string target1;
 int j;
 cout<<"Type in a title to remove--> ";
 if(cin.peek()=='\n')cin.ignore();
 getline(cin, target1);

 for(int i=0; i<used; i++)
      { if (target1 == array[i].get_title())
          j=i;
        while(j < used)
         {  array[j]=array[j+1];
            j++;
         }
      }
}

//void library::load_from_file(istream& ins){

//  ins >> array[CAPACITY];
// while(!(ins.eof())
//  {for(int i=1; i<CAPACITY; i++)
//   {ins >> array[CAPACITY];}
//    i++;
//  }
//}

void library::save_to_file(ostream& outs){
    for(int i=0;i < used; i++){
        outs<< array[i].get_title()<<endl;
        outs<< array[i].get_author()<<endl;
        outs<< array[i].get_copyright_date()<<endl;
        outs<< array[i].get_number_of_pages()<<endl<<endl;}
}









