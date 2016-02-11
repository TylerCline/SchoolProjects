//***************************************
//Implementation file of the board class
//Project 1: cs 3610
//Tyler Cline
//Ohio University
//***************************************

#include <iostream>
#include "board.h"
using namespace std;

board::board()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j<8 ; j++)
        {
            chess_board[i][j] = 0;
        }
    }
}

void board::input()
{
   {
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8 ; j++)
        {
            cin >> chess_board[i][j];
        }
    }
}
}

void board::output()
{
    {
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8 ; j++)
        {
            cout << " " << chess_board[i][j];
        }
        cout<<endl;
    }
}
}
bool board::is_legal(int x, int y)
{
            if(chess_board[x][y] == 1 && chess_board[x][y+1] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Right Horizontally "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x][y-1] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Left Horizontally  "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x+1][y] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Down vertically "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x-1][y] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Up Vertically "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x+1][y+1] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Diagonally "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x-1][y-1] == 1)
               {   cout<<x<<", "<<y<<" has a conflicting queen Diagonally "<<endl;
                   return false;
               }

            else if(chess_board[x][y] == 1 && chess_board[x+1][y-1] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Diagonally "<<endl;
                    return false;
                }

            else if(chess_board[x][y] == 1 && chess_board[x-1][y+1] == 1)
                {   cout<<x<<", "<<y<<" has a conflicting queen Diagonally "<<endl;
                    return false;
                }

             if(chess_board[x][y] == 1)// && chess_board[x][y+1] == 0 && chess_board[x][y-1] == 0 && chess_board[x+1][y] == 0 && chess_board[x-1][y] == 0)// && chess_board[x][y+1] == 0)
                {
                  int i=y+1, j=y-1, k=x+1, l=x-1;
                  while(i < 8 && j>=0 && k < 8 && l >= 0)
                  {
                      if(chess_board[x][i] == 1)
                      {  cout<<x<<", "<<y<<" And has a conflicting queen Right Horizontally at "<<x<<", "<<i<<endl;
                         return false;
                      }

                      else if(chess_board[x][j] == 1)
                      {
                         cout<<x<<", "<<y<<" And has a conflicting queen left Horizontally at "<<x<<", "<<j<<endl;
                         return false;
                      }

                      else if(chess_board[k][y] == 1)
                         {cout<<x<<", "<<y<<" And has a conflicting queen down vertically at "<<k<<", "<<y<<endl;
                             return false;
                         }

                      else if(chess_board[l][y] == 1)
                         {cout<<x<<", "<<y<<" has a conflicting queen up vertically at "<<l<<", "<<y<<endl;
                             return false;
                         }

                      else if(chess_board[k][i] == 1)
                      {
                         cout<<x<<", "<<y<<" And has a conflicting queen Diagonally at "<<k<<", "<<i<<endl;
                         return false;
                      }
                      else if(chess_board[l][i] == 1)
                      {
                          cout<<x<<", "<<y<<" And has a conflicting queen Diagonally at "<<l<<", "<<i<<endl;
                          return false;
                      }
                      else if(chess_board[k][j] == 1)
                      {
                          cout<<x<<", "<<y<<" And has a conflicting queen Diagonally at "<<k<<", "<<j<<endl;
                          return false;
                      }
                      else if(chess_board[l][j] == 1)
                      {
                          cout<<x<<", "<<y<<" And has a conflicting queen Diagonally at "<<l<<", "<<j<<endl;
                          return false;
                      }
                      else
                      {
                          i++;
                          j--;
                          k++;
                          l--;
                      }
                  }
                  return true;
                }

            else
                return true;

}

void board::board_check()
{
   for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8 ; j++)
          {
            if(is_legal(i, j) == false)
               {cout<<"Output:"<<endl<<"No"<<endl;
                return;}
          }
    }
   cout<<"Output: "<<endl<<"Yes"<<endl;
}
