//*************************************************************
//Main function for library and book class
//Tyler Cline  2014
//Ohio University
//*************************************************************

#include "book_class.h"
#include "library_class.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int main()
{
 ifstream fin;
 library collection;
 book tmp_book;
 string s1;


fin.open("library.dat");
   if(fin.fail())
    {cout<<"Input file failed to open. \n";
         return -1;}
  //collection.load_from_file(fin);
  fin.close();

char choice;
while (choice!= 'q' && choice!='Q'){
cout<<"Choose an Option(Type the Number)"<<endl<<endl;
cout<<"a-->Add a book to your collection "<<endl;
cout<<"b-->Output the total number of pages in your collection "<<endl;
cout<<"c-->Output all books in your collection "<<endl;
cout<<"d-->Sort Your collection by title"<<endl;
cout<<"e-->Sort your collection by copyright date "<<endl;
cout<<"f-->Search for a title"<<endl;
cout<<"g-->Output all books by the same author"<<endl;
cout<<"h-->Remove a book from your collection "<<endl;
cout<<"q-->Quit"<<endl<<endl<<"-->";
cin >> choice;


switch(choice)
{
  case 'a':
      collection.insert_book(tmp_book);
  break;

 case 'b':
      collection.total_pages(cout);
  break;

 case 'c':
      collection.show_all_books(cout);
  break;

 case 'd':
      collection.sort_by_title();
  break;

 case 'e':
      collection.sort_by_date();
  break;

 case 'f':
      collection.searchtitle(cout);
  break;

 case 'g':
      collection.output_by_author(cout);
  break;

 case 'h':
      collection.remove_element();
  break;

 default:
      cout<<endl<<endl;
}

}

  ofstream fout("library.dat");
  collection.save_to_file(fout);
  fout.close();

return(0);
}
