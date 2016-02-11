//The implementation file for the piece class
//If the piece is white it is integer value 0
//if the piece is black it is the integer value 1
#include<iostream>
#include"piece.h"
#include"colors.h"
using namespace std;

piece::piece(){

total_pieces = 64;
pcolor = "|_|";
}

void piece::set_space()
{
    pcolor = "|_|";
}

string piece::get_color()const
{
    return pcolor;
}

void piece::flip()
{
 if(is_white())
     pcolor = "|@|";
 else if(is_black())
     pcolor = "|O|";
}

bool piece::is_white()const
{
   return (pcolor == "|O|");
}

bool piece::is_black()const
{
   return (pcolor == "|@|");
}

void piece::set_white()
{
 pcolor = "|O|";
}

void piece::set_black()
{
 pcolor = "|@|";
}

bool piece::is_space()const
{
    return (pcolor == "|_|");
}

void piece::output_color()const
{
    if(pcolor == "|_|")
        cout<<B_GREEN<<BLACK<<pcolor;
    else if(pcolor == "|@|")
        cout<<B_GREEN<<BLACK<<pcolor;
    else
        cout<<B_GREEN<<WHITE<<pcolor;

        cout<<B_BLACK<<WHITE;
}

