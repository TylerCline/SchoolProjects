#include<iostream>
#include<string>
#ifndef PIECE_H
#define PIECE_H

class piece{

public:
    piece();
    void flip();
    bool is_white()const;
    bool is_black()const;
    bool is_space()const;
    void set_white();
    void set_black();
    void set_space();
    std::string get_color()const;
    void output_color()const;
private:

    std::string pcolor;
    int total_pieces;
};

#endif
