//********************************
//Main function for queens project
//Project 1: cs 3610
//Tyler Cline
//Ohio University
//********************************

#include <iostream>
#include "board.h"
using namespace std;

int main()
{
    board b;
    cout<<"Project 1 for 3610"<<endl;
    b.input();
    b.output();
    b.board_check();

    return 0;
}
