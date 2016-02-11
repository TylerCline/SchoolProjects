#include<iostream>
#include"piece.h"
#include<string>
#include"game.h"
using namespace std;

int main()
{string intended_move;
cout<<endl<<endl<<"welcome to othello!"<<endl;
cout<<endl<<"Player 1 has the black pieces"<<endl;
cout<<"Enter a value on the grid(c4, c3, etc.) to choose your move "<<endl;
// main_savitch_14::game g;
 main_savitch_14::othello o;

o.play();
/*char ans;
while(ans != 'N' || ans != 'n')
{
cout<<"Make a move "<<endl<<"->";
cin>>intended_move;
o.make_move(intended_move);
o.display_status();
cout<<"Would you like to continue? "<<endl;
cout<<"Press n to quit "<<endl;
cout<<"Press r to restart"<<endl;
cout<<"Press any other key to keep going"<<endl;
cin>>ans;
if(ans == 'n' || ans == 'N')
    return 0;
if(ans=='r')
    o.restart();
}*/
o.victory();
return 0;
}

