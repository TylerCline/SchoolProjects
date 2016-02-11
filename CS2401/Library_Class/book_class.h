//***********************************
//Header File Book class
//Tyler CLine   2014
//Ohio University
//***********************************

#include <iostream>
#include <string>
#ifndef BOOK_H
#define BOOK_H

class book
{
  public:

	book();

        std::string get_title();

	std::string get_author();

	int get_copyright_date();

        int get_number_of_pages();

                 // Accessor functions

	void set_title(std::string& settitle);

	void set_author(std::string& setauthor);

	void set_copyright_date(int& setcopyrightdate);

	void set_number_of_pages(int& setnumberofpages);
	        // mutator functions
  


  private:

	std::string title, author;

        int number_of_pages, copyright_date;
};

# endif
