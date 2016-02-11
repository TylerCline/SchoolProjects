//***********************************************************
//Libray Class header file
//Tyler CLine  2014
//Ohio University
//**********************************************************

#include <iostream>
#include <cstdlib>
#include <string>
#include "book_class.h"
#ifndef LIBRARY_H
#define LIBRARY_H

class library

{
public:

 	static const std::size_t CAPACITY=300;

 	library();

 	void insert_book(book& book1);

 	void total_pages(std::ostream& pages_out);

 	void show_all_books(std::ostream& books_out);

 	void sort_by_title();

	void sort_by_date();

 	void searchtitle(std::ostream& tout);

 	void output_by_author(std::ostream& author_out);

 	void remove_element ();

        void load_from_file(std::istream& ins);

	void save_to_file(std::ostream& outs);

	friend std::ostream& operator << (std::ostream& c_out, book& b1);

private:
	book array[CAPACITY];
	std::size_t used;
};
# endif
