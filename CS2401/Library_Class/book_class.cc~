//***************************************************
//Implementation file for book_class
//Tyler CLine   2014
//Ohio University
//***************************************************

#include <iostream>
#include <string>
#include "book_class.h"

using namespace std;

book::book()
{
  copyright_date=0;
  number_of_pages=0;

}


string book::get_title()
 {
  return(title);
 }

string book::get_author()
 {
  return(author);
 }

int  book::get_copyright_date()
 {
  return(copyright_date);
 }

int book::get_number_of_pages()
 {
  return(number_of_pages);
 }
void book::set_title(string& settitle)
 {
  cout << "Enter Book Title"<<endl;
	if(cin.peek()=='\n')cin.ignore();
        getline(cin, settitle);
  title=settitle;
 }

void book::set_author(string& setauthor)
 {
  cout <<"Enter book author"<<endl;
        getline(cin, setauthor);
  author=setauthor;
 }

void book::set_copyright_date(int& setcopyrightdate)
 {
  cout << "Enter the copyright date "<<endl;
        cin >> setcopyrightdate;
  copyright_date=setcopyrightdate;
 }

void book::set_number_of_pages(int& setnumberofpages)
 {
  cout << "Enter the number of pages "<<endl;
        cin >> setnumberofpages;
  number_of_pages=setnumberofpages;
 }

 
