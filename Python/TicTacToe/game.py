#//*******************************************************************
#//
#//  Program:     homework 3
#//
#//  Author:      Tyler Cline
#//  Email:       tc670611@ohio.edu
#//
#//  Description: This program allows you to play 2 player tic tac toe
#//
#//  Date:        1-31-15
#//
#//*******************************************************************
from string import rstrip
from binhex import LINELEN
from sys import exit
import sys
import math
import main

n = 0

#//******************************************************************
#//
#//  Function:   print_board
#//
#//  Purpose:    Redraws the entire tic tac toe board once moves have been made
#//
#//  Parameters: board1 - the tic tac toe board
#//
#//
#// Member/Global Variables: none
#//
#// Pre Conditions: the new board is passed into the function
#//
#// Post Conditions: the new board is printed to the screen
#//
#//******************************************************************
def print_board(board1):
    print '\n'
    j = 0
    while j < math.sqrt(len(board1)):
        sys.stdout.write(' ' + board1[int(j*math.sqrt(len(board1)))] + ' | ')
        i = 0
        while i < ((math.sqrt(len(board1)))-2):
            sys.stdout.write(board1[int(i + 1 + j*math.sqrt(len(board1)))] + ' | ')
            i += 1
        print board1[int((math.sqrt(len(board1)) - 1)+ (j*math.sqrt(len(board1))))]
        h = 0
        if( j != (math.sqrt(len(board1))-1)):
            while h < math.sqrt(len(board1))*4 - 2:
                sys.stdout.write('-')
                h += 1
            print '-'
        j +=1
    print '\n'
            
        

#//******************************************************************
#//
#//  Function:   print_help
#//
#//  Purpose:    Prints out a reference with all of the numbers for the user
#//
#//  Parameters: none
#//
#//
#// Member/Global Variables: board2 - the reference list
#//
#// Pre Conditions: A new list of 16 numbers is made
#//
#// Post Conditions: the reference board is printed to the screen
#//
#//******************************************************************
def print_help(length):
    board2 = []
    i = 0
    while i < length:
        board2.append(str(i))
        i += 1
    print '\n'
    j = 0
    while j < math.sqrt(len(board2)):
        sys.stdout.write(' ' + board2[int(j*math.sqrt(len(board2)))] + ' | ')
        i = 0
        while i < ((math.sqrt(len(board2)))-2):
            sys.stdout.write(board2[int(i + 1 + j*math.sqrt(len(board2)))] + ' | ')
            i += 1
        print board2[int((math.sqrt(len(board2)) - 1)+ (j*math.sqrt(len(board2))))]
        h = 0
        if( j != (math.sqrt(len(board2))-1)):
            while h < math.sqrt(len(board2))*4 - 2:
                sys.stdout.write('-')
                h += 1
            print '-'
        j +=1
    print '\n'
    print "---------------------------------"
#//******************************************************************
#//
#//  Function:   is_game_over
#//
#//  Purpose:    This function is a boolean that returns true if someone
#//              has successfully aligned 4 X's or O's in a row
#//
#//  Parameters: board1 - the game board
#//
#//
#// Member/Global Variables: none
#//
#// Pre Conditions: the current game board is passed in
#//
#// Post Conditions: The board is evaluated and returns a true if
#//                  there is a winner
#//
#//******************************************************************

def who_won(board1):
    index = int(math.sqrt(len(board1)))
    length = len(board1)
    var = 0
    var2 = index
    board2 = board1[index-1::index-1]
    board2[len(board2)-1]
    board3 = []
    for i in range(len(board2)-1):
        board3.append(board2[i])
    if board1[0::index + 1] == ["O"]*index or board1[0::(index + 1)] == ['X']*index:
        return True
    elif board3 == ["O"]*index or board3 == ['X']*index:
        return True
    else:
        for k in range(length):
            if var > (length - index):
                for i in range(length):
                    if i == index:
                        return None
                    else:
                        if board1[i::index] == ['O']*index or board1[i::index] == ["X"]*index:
                            return True
            else:
                if board1[var:var2] == ['O']*index or board1[var:var2] == ['X']*index:
                    return True
                else:
                    var = var + index
                    var2 = var2 + index
                    
#//******************************************************************
#//
#//  Function:   play
#//
#//  Purpose:    This function contains all other function calls to play
#//              the entire game. While it is not game over, both players
#//              can choose to restart the game, save it, or continue playing
#//
#//  Parameters:  none
#//
#//
#// Member/Global Variables: board - the game board to start out with
#//                          count - keeps track of whose turn it is
#//                          ans - the user's input
#//                          player1 - what player 1 wants his name to be
#//                          player2 - what player 2 wants his name to be
#//
#// Pre Conditions: the current game board is passed in
#//
#// Post Conditions: the board is passed into other functions that play the game
#//
#//******************************************************************

def play(player1_wins, player2_wins):
    board = []
    n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3 ->")
    while not n.isdigit():
        n = raw_input("enter the correct value please")
    n = int(n)*int(n)
    i = 0
    while i < n:
        board.append('_')
        i += 1
    counter = 0
    player1 = choose_player1_name()
    player2 = choose_player2_name()
    play_next_move(board, counter, player1, player2, player1_wins, player2_wins)
    counter = counter+1
    restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
    restart = restart.lower()
    if restart == "y":
        counter = 0
        while i < n:
            board.append('_')
            i += 1
        play_next_move(board, counter, player1, player2, player1_wins, player2_wins)
    else:
        main.start()

#//******************************************************************
#//
#//  Function:   is_legal
#//
#//  Purpose:    To evaluate the board and see if the move passed in is legal for player 1
#//
#//  Parameters:  board1 - the game board
#/                an - the players answer
#//
#// Member/Global Variables: none
#//
#// Pre Conditions: the player turn, answer and board are passed in
#//
#// Post Conditions: the answer, board position are evaluated and true is returned
#//                  if the piece can be placed
#//
#//******************************************************************

def is_legal1(an, board1):
    board2 = []
    i = 0
    while  i < len(board1):
        board2.append(i)
        i+=1
    if an not in str(board2):
        return False
    elif board1[int(an)] == "_":
        return True
    else:
        return False

#//******************************************************************
#//
#//  Function:   no_more_spots
#//
#//  Purpose:    This checks the entire board to see how many spots
#//              are taken up by an x or an o and says "DRAW" if no
#//              all 16 spots are taken up
#//
#//  Parameters:  board1 - the current state of the game board
#//               play1 - player1 name
#//               play2 - player 2 name
#//               player1_wins - number of wins player 1 has
#//               player2_wins - number of wins player 2 has
#//               count - whatever turn it is
#//
#// Member/Global Variables: j - the count variable to see if spots are taken
#//
#//
#// Pre Conditions: the players, turn, and board are passed in
#//
#// Post Conditions: the board is evaluated, if the board meets the criteria for a draw
#//                  "DRAW" is printed to the screen and the players are asked if they want to play again
#//
#//******************************************************************
def no_more_spots(board1, count, play1, play2, player1_wins, player2_wins):
    j = 0
    for i in range(len(board1)):
        if board1[i] == 'X' or board1[i] == 'O':
            j = j+1
    if j == len(board1):
        print"DRAW"
        print play1, "wins:",player1_wins,"     ", play2, "wins:", player2_wins, "\n"
        restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
        restart = restart.lower()
        if restart == "y":
            i = 0
            board2 = []
            n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3) ->")
            while not n.isdigit():
                n = raw_input("enter the correct value please")
            n = int(n)*int(n)
            count = 0
            while i < n:
                board2.append('_')
                i+=1
            play_next_move(board2, count, play1, play2, player1_wins, player2_wins)
        else:
            player1_wins = 0
            player2_wins = 0
            main.start(player1_wins, player2_wins)

#//******************************************************************
#//
#//  Function:   choose player1 name
#//
#//  Purpose:    allows for player 1 to choose a name
#//
#//  Parameters:  none
#//
#// Member/Global Variables: player 1 - variable storing player 1's name
#//
#//
#// Pre Conditions:
#//
#// Post Conditions: the player types in his name and that is returned
#//
#//******************************************************************
def choose_player1_name():
        player1 = raw_input("Player 1, choose a name-> ")
        return player1


#//******************************************************************
#//
#//  Function:   choose player2 name
#//
#//  Purpose:    allows for player2 to choose a name
#//
#//  Parameters:  turn - passed in what players turn it is.
#//
#// Member/Global Variables: player 2 - variable storing player 2's name
#//
#//
#// Pre Conditions:
#//
#// Post Conditions: the player types in his name and that is returned
#//
#//******************************************************************

def choose_player2_name():
        player2 = raw_input("Player 2, choose a name-> ")
        return player2


#//******************************************************************
#//
#//  Function:   load_save()
#//
#//  Purpose:    loads the most previous game
#//
#//  Parameters:  none
#//
#//  Member/Global Variables:
#//
#//
#//  Pre Conditions: there is an empty board
#//
#//  Post Conditions: The most recent board is loaded into the current board
#//
#//******************************************************************

def load_save():
    q = []
    f = open("save_data.txt", "r")
    for line in f:
        q.append(line.rstrip())
    return q
    f.close()

#//******************************************************************
#//
#//  Function:   save_game()
#//
#//  Purpose:    saves current game
#//
#//  Parameters:  counter - what turn it is
#//               play1 - player 1 name
#//               play2 - player 2 name
#//               player1_wins - the number of wins player 1 has
#//               player2_wins - the number of wins player 2 has
#//               board1 - the status of the current board
#//
#//  Member/Global Variables:
#//
#//
#//  Pre Conditions: there is an empty board
#//
#//  Post Conditions: The most recent board is loaded into the current board
#//
#//******************************************************************
def save_game(counter, play1, play2, player1_wins, player2_wins, board1):
    f = open('save_data.txt', 'w')
    print >> f, counter,'\n', play1, '\n', play2, '\n', player1_wins, '\n', player2_wins,'\n'
    for i in range(len(board1)-1):
        print >> f, board1[i]
    f.close()
#//******************************************************************
#//
#//  Function:   play_next_move()
#//
#//  Purpose:    This function determines what players turn it is, then the player can
#//              make a move, save the game, or resign. The score of how many wins there
#//              are is also kept
#//
#//  Parameters:  board1 - the game board passed from the play function
#//               count - the variable to keep track of what turn it is
#//               play1 - the player 1 name
#//               play2 - the player 2 name
#//               player1_wins - the number of wins player 1 has
#//               player2_wins - the number of wins player 2 has
#//
#//  Member/Global Variables: restart - hold the input of what the player wants
#//                                     to play another game
#//
#//
#//  Pre Conditions: The board is empty and is awaiting input from the first player
#//
#//  Post Conditions: The board, nnumber of wins, or weather a game is saved or not
#//                   is altered depending on user input. The new board, along with
#//                   the reference board are printed so the next player knows what
#//                   moves are available. An illegal move flag is thrown if what is typed
#//                   is not valid.
#//
#//******************************************************************

def play_next_move(board1, count, play1, play2, player1_wins, player2_wins):
    print"\n Type in a number that corresponds to a spot on the board"
    print_board(board1)
    while not who_won(board1):
        no_more_spots(board1, count, play1, play2, player1_wins, player2_wins)
        if count % 2 == 0:
            print play1, ", Place an X, hit R to resign, Hit s to save, H to bring up reference baord"
            ans = raw_input("-> ")
            ans = ans.upper()
            if ans == "R":
                player2_wins = player2_wins + 1
                print "You have resigned. Player 2 wins"
                print play1, "wins:",player1_wins,"     ", play2, "wins:", player2_wins, "\n"
                restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
                restart = restart.lower()
                if restart == "y":
                    i = 0
                    board2 = []
                    n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3) ->")
                    while not n.isdigit():
                        n = raw_input("enter the correct value please")
                    n = int(n)*int(n)
                    count = 0
                    while i < n:
                        board2.append('_')
                        i = i+1
                    play_next_move(board2, count, play1, play2, player1_wins, player2_wins)
                else:
                    player1_wins = 0
                    player2_wins = 0
                    main.start(player1_wins, player2_wins)
            elif ans =="S":
                save_game(count, play1, play2, player1_wins, player2_wins, board1)
                print "game saved"
            elif ans =="H":
                print_help(len(board1))
            else:
                while not is_legal1(ans, board1):
                    ans = raw_input("Illegal Move. Must pick a number on the board, and must not be an O ->")
                ans = int(ans)
                board1[ans] = "X"
                count = count + 1
                print_board(board1)
                if who_won(board1):
                    player1_wins = player1_wins + 1
                    print"Player 1 wins"
                    print play1, "wins:",player1_wins,"     ", play2, "wins:", player2_wins, "\n"
                    restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
                    restart = restart.lower()
                    if restart == "y":
                        i = 0
                        board2 = []
                        n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3 ->")
                        while not n.isdigit():
                            n = raw_input("enter the correct value please")
                        n = int(n)*int(n)
                        count = 0
                        while i < n:
                            board2.append('_')
                            i = i + 1
                        play_next_move(board2, count, play1, play2, player1_wins, player2_wins)
                    else:
                        player1_wins = 0
                        player2_wins = 0
                        main.start(player1_wins, player2_wins)
        else:
            print play2, ", Place an O, hit R to resign, hit S to save, or H to bring up reference board"
            ans = raw_input("-> ")
            ans = ans.upper()
            if ans == "R":
                player1_wins = player1_wins + 1
                print "You have resigned. Player 1 wins \n"
                print play1, "wins:",player1_wins,"     ", play2, "wins:", player2_wins, "\n"
                restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
                restart = restart.lower()
                if restart == "y":
                    i = 0
                    board2 = []
                    n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3) ->")
                    while not n.isdigit():
                        n = raw_input("enter the correct value please")
                    n = int(n)*int(n)
                    count = 0
                    while i < n:
                        board2.append('_')
                        i += 1
                    play_next_move(board2, count, play1, play2, player1_wins, player2_wins)
                else:
                    player1_wins = 0
                    player2_wins = 0
                    main.start(player1_wins, player2_wins)
            elif ans =="S":
                save_game(count, play1, play2, player1_wins, player2_wins, board1)
                print "game saved"
            elif ans == "H":
                print_help(len(board1))
            else:
                while not is_legal1(ans, board1):
                    ans = raw_input("Illegal Move. Must pick a number on the board, and must not be an X ->")
                ans = int(ans)
                board1[ans] = "O"
                count = count + 1
                print_board(board1)
                if who_won(board1):
                    player2_wins = player2_wins + 1
                    print"Player 2 wins"
                    print play1, "wins:",player1_wins,"     ", play2, "wins:", player2_wins,"\n"
                    restart = raw_input("Would you like to play again(y - restart, any other key to return to main menu) \n-> ")
                    restart = restart.lower()
                    if restart == "y":
                        board2 = []
                        n = raw_input("Enter the size of the board (Example: If entered 3, board will be 3x3 ->")
                        while not n.isdigit():
                            n = raw_input("enter the correct value please")
                        n = int(n)*int(n)
                        i = 0
                        count = 0
                        while i < n:
                            board2.append('_')
                            i+=1
                        play_next_move(board2, count, play1, play2, player1_wins, player2_wins)
                    else:
                        player1_wins = 0
                        player2_wins = 0
                        main.start(player1_wins, player2_wins)
                        
