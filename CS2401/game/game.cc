// File: game.cxx

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include <sstream>
#include "game.h"     // Provides definition of game class
#include "colors.h"
#include "piece.h"
using namespace std;

namespace main_savitch_14
{
    //*************************************************************************
    // STATIC MEMBER CONSTANTS
    // const int game::SEARCH_LEVELS;

    //*************************************************************************
    // PUBLIC MEMBER FUNCTIONS

    game::who game::play( )
    // The play function should not be overridden. It plays one round of the
    // game, with the human player moving first and the computer second.
    // The return value is the winner of the game (or NEUTRAL for a tie).
    {
	restart( );

	while (!is_game_over( ))
	{
	    display_status( );
	   // if (last_mover( ) == COMPUTER){
	   if(move_number%2==0){
          cout<<"Player 1(Black Pieces), Make a move"<<endl;
      // else
        //  cout<<"Player 2(White Pieces), Make a move"<<endl;
		  make_human_move( );}
	    else{

		  make_computer_move( );
		  cout<<"Computer move"<<endl;}
	}
	display_status( );
	return winning();
    }



    //*************************************************************************
    // OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)

    void game::display_message(const string& message) const
    {
	cout << message;

    }

    string game::get_user_move( ) const
    {
	string answer;

	display_message("Your move, please: ");
	getline(cin, answer);
	  return answer;
    }

    game::who game::winning( ) const
    {
	int value = evaluate( ); // Evaluate based on move that was just made.

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
    }



    //*************************************************************************
    // PRIVATE FUNCTIONS (these are the same for every game)

    int game::eval_with_lookahead(int look_ahead, int beat_this)
    // Evaluate a board position with lookahead.
    // --int look_aheads:  How deep the lookahead should go to evaluate the move.
    // --int beat_this: Value of another move that we?re considering. If the
    // current board position can't beat this, then cut it short.
    // The return value is large if the position is good for the player who just
    // moved.
    {
    	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
    	int best_value;        // Evaluation of best opponent move
    	game* future;          // Pointer to a future version of this game

        // Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
	    if (last_mover( ) == COMPUTER)
	            return evaluate( );
	    else
		return -evaluate( );
	}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves);
	 //assert(!moves.empty( ));
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(look_ahead-1, best_value);
	    delete future;
	    if (value > best_value)
	    {
		if (-value <= beat_this)
		    return INT_MIN + 1; // Alpha-beta pruning
		best_value = value;
	    }
	    moves.pop( );
    	}

    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_value;
    }

    void game::make_computer_move( )
    {
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;

	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));

	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	    delete future;
	    if (value >= best_value)
	    {
		best_value = value;
		best_move = moves.front( );
	    }
	    moves.pop( );
	}
    cout<<" Best Move "<<best_move;
	// Make the best move.
	make_move(best_move);
    }

    void game::make_human_move( )
    {
        string move;

	move = get_user_move( );
	while (!is_legal(move))
	{
	    display_message("Illegal move.\n");
	    move = get_user_move( );
        }
	make_move(move);
    }

//}
//******************************************
//othello class implementation
//
//
//******************************************
othello::othello()
{
    first_move=1;
}

void othello::restart( )
{ game::restart();
  for(int i = 0; i<8; i++)
  {
      for (int j = 0; j<8; j++)
      {
        board[i][j].set_space();
      }
  }

  char y_axis[8]={'a','b','c','d','e','f','g','h'};
  board[3][3].set_white();
  board[3][4].set_black();
  board[4][3].set_black();
  board[4][4].set_white();
  /*cout<<"    1  2  3  4  5  6  7  8"<<endl;
  for(int i = 0; i<8; i++)
  { cout<<y_axis[i]<<"  ";
      for (int j = 0; j<8; j++)
      {
        board[i][j].output_color();
      }
      cout<<endl;
  }*/
}

void othello::display_status()const
{
  char y_axis[8]={'a','b','c','d','e','f','g','h'};

  cout<<"    1  2  3  4  5  6  7  8"<<endl;
  for(int i = 0; i<8; i++)
  { cout<<y_axis[i]<<"  ";
      for (int j = 0; j<8; j++)
      {
        board[i][j].output_color();

      }
      cout<<endl;
  }
}

//Function to make count the total number of moves
//and flip the colors
void othello::make_move(const string& move)
{
    int x, y;

 if(is_legal(move))
 {
   x = (int)(toupper(move[0])-'A');
   y = (int)(move[1]-'1');

   //checks which player it is
   if(move_number % 2 == 0)
    {//cout<<"Player 1. "<<endl;
    board[x][y].set_black();

   //This checks to see what color the piece being played was
   //and then checks moves to the right and flips the pieces
   //to the opposite color until the same color is reached

   if(board[x][y].is_black() && board[x][y+1].is_white())
   {
       for(int j=y+1; board[x][j].is_white(); j++)
         board[x][j].flip();
   }
   //These two check to see if the piece is white of black
   //Then it sees if the piece to the left is of the opposite color
   //the integer value starts at the user piece and is set equal to
   //the left position of the user's piece. The pieces are flipped until
   //The same color is reached
   else if(board[x][y].is_black() && board[x][y-1].is_white())
   {
       for(int k=y-1; board[x][k].is_white(); k--)
           board[x][k].flip();
   }
   //these check to see if there is a piece of opposite color on top
   //of the piece that the player intends to play and flips the pieces
   //accordingly
   else if(board[x][y].is_black() && board[x-1][y].is_white())
   {
       for(int d=x-1; board[d][y].is_white(); d--)
           board[d][y].flip();
   }
   //checks to see if there is a piece below the player layed piece of
   //of the opposite color and flips until it gets to the same colored piece
   else if(board[x][y].is_black() && board[x+1][y].is_white())
   {
       for(int l=x+1; board[l][y].is_white(); l++)
            board[l][y].flip();
   }
 //first_move++;
 //This else statement is for every move after the first, where first move is greater than 1
// else if(first_move > 1){
    else if(board[x][y].is_black() && board[x+1][y+1].is_white())
   {   int t=x+1; int u=y+1;
       while(board[t][u].is_white())
       {
           board[t][u].flip();
           t++;
           u++;
       }
   }

   else if(board[x][y].is_black() && board[x+1][y-1].is_white())
   {   int t=x+1; int u=y-1;
       while(board[t][u].is_white())
       {
           board[t][u].flip();
           t++;
           u--;
       }
   }

   else if(board[x][y].is_black() && board[x-1][y+1].is_white())
   {   int t=x-1; int u=y+1;
       while(board[t][u].is_white())
       {
           board[t][u].flip();
           t--;
           u++;
       }
   }


   else if(board[x][y].is_black() && board[x-1][y-1].is_white())
   {   int t=x-1; int u=y-1;
       while(board[t][u].is_white())
       {
           board[t][u].flip();
           t--;
           u--;
       }
   }

   else
   {
      return;
      board[x][y].set_space();
   }
 }
 else  //This else checks to see if it is plyer 2
    {
      //cout<<"Player 2. White pieces"<<endl;
      board[x][y].set_white();

   //This checks to see what color the piece being played was
   //and then checks moves to the right and flips the pieces
   //to the opposite color until the same color is reached

    if(board[x][y].is_white() && board[x][y+1].is_black())
   {
       for(int j=y+1; board[x][j].is_black(); j++)
         board[x][j].flip();
   }
   //These two check to see if the piece is white of black
   //Then it sees if the piece to the left is of the opposite color
   //the integer value starts at the user piece and is set equal to
   //the left position of the user's piece. The pieces are flipped until
   //The same color is reached
   else if(board[x][y].is_white() && board[x][y-1].is_black())
   {
       for(int k=y-1; board[x][k].is_black(); k--)
           board[x][k].flip();
   }
   //these check to see if there is a piece of opposite color on top
   //of the piece that the player intends to play and flips the pieces
   //accordingly
   else if(board[x][y].is_white() && board[x-1][y].is_black())
   {
       for(int d=x-1; board[d][y].is_black(); d--)
           board[d][y].flip();
   }
   //checks to see if there is a piece below the player layed piece of
   //of the opposite color and flips until it gets to the same colored piece
   else if(board[x][y].is_white() && board[x+1][y].is_black())
   {
       for(int l=x+1; board[l][y].is_black(); l++)
            board[l][y].flip();
   }
 //first_move++;
 //This else statement is for every move after the first, where first move is greater than 1
// else if(first_move > 1){
    else if(board[x][y].is_white() && board[x+1][y+1].is_black())
   {   int t=x+1; int u=y+1;
       while(board[t][u].is_black())
       {
           board[t][u].flip();
           t++;
           u++;
       }
   }

   else if(board[x][y].is_white() && board[x+1][y-1].is_black())
   {   int t=x+1; int u=y-1;
       while(board[t][u].is_black())
       {
           board[t][u].flip();
           t++;
           u--;
       }
   }

   else if(board[x][y].is_white() && board[x-1][y+1].is_black())
   {   int t=x-1; int u=y+1;
       while(board[t][u].is_black())
       {
           board[t][u].flip();
           t--;
           u++;
       }
   }


   else if(board[x][y].is_white() && board[x-1][y-1].is_black())
   {   int t=x-1; int u=y-1;
       while(board[t][u].is_black())
       {
           board[t][u].flip();
           t--;
           u--;
       }
   }

   else
   {
      return;
      board[x][y].set_space();
   }
}

}
game::make_move(move); //increments the move_number
}


//Function that implements the rules of the game
bool othello::is_legal(const string& move)
{ int x, y;
  x = (int)(toupper(move[0])-'A');
  y = (int)(move[1]-'1');

if(x<8 && x>=0 && y<8 && y>=0)
{ if(move_number % 2 == 0)
 {
   board[x][y].set_black();

   if(board[x][y].is_black() && board[x][y+1].is_white())
        /*{ int i;
            for(i=y+1; board[x][i].is_white(); i++);
              if(board[x][i].is_black())*/
                   return true;
       // }


   else if(board[x][y].is_black() && board[x][y-1].is_white())
       /*{ int i;
            for(i=y-1; board[x][i].is_white(); i--);
              if(board[x][i].is_black())*/
                   return true;
       //}
   //The above if statements check to see if what color the piece is
   //being played then checks to see what the color is next
   //to the piece that is intended to be played. if there is anything
   //to the left or right a true is returned

   else if(board[x][y].is_black() && board[x-1][y].is_white())
        /*{ int i;
            for(i=x-1; board[i][y].is_white(); i--);
              if(board[i][y].is_black())*/
                   return true;
       // }

   else if(board[x][y].is_black() && board[x+1][y].is_white())
       /* { int i;
            for(i=x+1; board[i][y].is_white(); i++);
              if(board[i][y].is_black())*/
                   return true;
       // }
   //These four if statements check to see if there is anything
   //of the opposite color on top or bottom of the piece
   //intended to be played and returns true if the move is
   //legal


   else if(board[x][y].is_black() && board[x+1][y+1].is_white())
         /*{int i=0; int j=0;
           while(board[i][j].is_white())
           {
               i++; j++;
           }
            if(board[i][j].is_black())*/
                return true;
        // }
   else if(board[x][y].is_black() && board[x+1][y-1].is_white())
         /*{int i=0; int j=0;
           while(board[i][j].is_white())
           {
               i++; j--;
           }
            if(board[i][j].is_black())*/
                return true;
         //}
   else if(board[x][y].is_black() && board[x-1][y+1].is_white())
         /*{int i=0; int j=0;
           while(board[i][j].is_white())
           {
               i--; j++;
           }
            if(board[i][j].is_black())*/
                return true;
         //}
   else if(board[x][y].is_black() && board[x-1][y-1].is_white())
         /*{int i=0; int j=0;
           while(board[i][j].is_white())
           {
               i--; j--;
           }
            if(board[i][j].is_black())*/
                return true;
         //}
   else
   {
      board[x][y].set_space();
      return false;
   }
}

else
{
    board[x][y].set_white();

   if(board[x][y].is_white() && board[x][y+1].is_black())
       /* { int i;
            for(i=y+1; board[x][i].is_black(); i++);
             if(board[x][i].is_white())*/
                   return true;
        //}

   else if(board[x][y].is_white() && board[x][y-1].is_black())
         /*{ int i;
            for(i=y-1; board[x][i].is_black(); i--);
             if(board[x][i].is_white())*/
                   return true;
        //}
   //The above if statements check to see if what color the piece is
   //being played then checks to see what the color is next
   //to the piece that is intended to be played. if there is anything
   //to the left or right a true is returned

   else if(board[x][y].is_white() && board[x-1][y].is_black())
       /* { int i;
            for(i=x-1; board[i][y].is_black(); i--);
             if(board[i][y].is_white())*/
                   return true;
       // }

   else if(board[x][y].is_white() && board[x+1][y].is_black())
       /* { int i;
            for(i=x+1; board[i][y].is_black(); i++);
             if(board[i][y].is_white())*/
                   return true;
      //  }
   //These four if statements check to see if there is anything
   //of the opposite color on top or bottom of the piece
   //intended to be played and returns true if the move is
   //legal


   else if(board[x][y].is_white() && board[x+1][y+1].is_black())
        /* {int i, j;
           while(board[i][j].is_black())
           {
               i++; j++;
           }
            if(board[i][j].is_white())*/
                return true;
        // }
   else if(board[x][y].is_white() && board[x+1][y-1].is_black())
        /* {int i, j;
           while(board[i][j].is_black())
           {
               i++; j--;
           }
            if(board[i][j].is_white())*/
                return true;
        // }
   else if(board[x][y].is_white() && board[x-1][y+1].is_black())
        /* {int i, j;
           while(board[i][j].is_black())
           {
               i--; j++;
           }
            if(board[i][j].is_white())*/
                return true;
         //}
   else if(board[x][y].is_white() && board[x-1][y-1].is_black())
        /* {int i, j;
           while(board[i][j].is_black())
           {
               i--; j--;
           }
            if(board[i][j].is_white())*/
                return true;
        // }
   else
   {
      board[x][y].set_space();
      return false;
   }
}
}


else
{
      return false;
}
}

void othello::victory()
{ int black = 0; int white = 0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
    {
         if(board[i][j].is_black())
            black++;
         else if(board[i][j].is_white())
            white++;
    }
    if(black < white)
        cout<<endl<<"YOU LOSE. A valiant effort, but to no avail. "<<endl<<"My skill cannot be matched"<<endl;
    else if(black > white)
        cout<<endl<<"PLAYER 1 HAS ACHIEVED SUPREME VICTORY. "<<endl<<"                  ....you have defeated me this time, but I shall return"<<endl;
    else
        cout<<endl<<"TIE. It seems that you have matched my intellect"<<endl<<endl;
}

 void othello::compute_moves(std::queue<std::string>& moves)
 { int i, j; ostringstream a;
    string move;

      for(i=1; i<6; i++)
       {for(j=0; j<=7; j++)
         {
          if(board[i][j].is_space())
          {
          /*char x = i + 'A';
          int y = j + 1;
          a << x << y;
          move = a.str();*/
          move = "  ";
          move[0] = i + 'A';
          move[1] = j + '1';

         if(is_legal(move))
           {
            moves.push(move);
           }
           /*a.str("");
           a.clear();*/
          }

        //cout<<move<<endl;
      }
    }

 }
 int othello::evaluate( ) const
 {
  int black = 0; int white = 0; int sum =0;
    for(int i=0; i<8; i++)
       {for(int j=0; j<8; j++)
        {
         if(board[i][j].is_black())
            black--;
         else if(board[i][j].is_white())
            white++;
        }
    }
    return (sum = white + black);
 }
 game* othello::clone( ) const
 {
     return new othello(*this);
 }

bool othello::is_game_over() const
      { int x, y, sum;
       for(x=0; x<8; x++){
        for(y=0; x<8; x++){
                 sum++;}}

          if(sum == 50)
             return true;
          else
            return false;
      }
}





