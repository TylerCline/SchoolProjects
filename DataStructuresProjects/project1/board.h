//******************************************
//Title: Header file for the board class
//Project 1: Cs3610
//Tyler Cline
//Ohio University
//******************************************

#include <iostream>

class board{
    public:
            board();
            void input();
            void output();
            bool is_legal(int x, int y);
            void board_check();

    private:
            int chess_board[8][8];

};
