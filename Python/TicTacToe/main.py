import game
#//******************************************************************
#//
#//  Function:   start()
#//
#//  Purpose:    create a start menu interface
#//
#//               player2_wins - the number of wins player 2 has
#//
#//  Member/Global Variables: answer - the users choice
#//
#//
#//  Pre Conditions: the menu is given to the user
#//
#//  Post Conditions: the user enters his response and a subroutine is initiated
#//
#//******************************************************************

def start(player1_wins, player2_wins):
    print "\n"
    print "Welcome to Tic Tac Toe! "
    answer = raw_input ("P - new game     L - load last game     Q - quit -> ")
    answer = answer.upper()
    print "\n"
    get_starting_answers(answer, player1_wins, player2_wins)



#//******************************************************************
#//
#//  Function:   get_starting_answer()
#//
#//  Purpose:    to check the users input to see if it is valid
#//
#//  Parameters:  player1_wins - the number of wins player 1 has
#//               player2_wins - the enumber of wins player 2 has
#//               ans - the users choice
#//  Member/Global Variables:
#//
#//
#//  Pre Conditions: the users input is passed in
#//
#//  Post Conditions: the users input is evaluated and a subroutine is generated
#//                   if deemed valid. the number of wins are also
#//
#//******************************************************************
def get_starting_answers(ans, player1_wins, player2_wins):
    if ans == "Q":
        print"Goodbye"
        exit(1)
    elif ans == "P":
        game.play(player1_wins, player2_wins)
    elif ans == "L":
        f = game.load_save()
        if f == 1:
            print "no save data. Hit P for new game, or Q to quit"
            ans1 = raw_input("Please enter correct answer -> ")
            ans1 = ans1.upper()
            get_starting_answers(ans1, player1_wins, player2_wins)
        else:
            count = int(f[0])
            play1 = f[1]
            play2 = f[2]
            player1_wins = int(f[3])
            player2_wins = int(f[4])
            board1 = f[6:]
            game.play_next_move(board1, count, play1, play2, player1_wins, player2_wins)
    else:
        print "Invalid Input, Must Choose Q, P, L"
        ans1 = raw_input("Please enter correct answer -> ")
        ans1 = ans1.upper()
        get_starting_answers(ans1, player1_wins, player2_wins)


player1_wins = 0
player2_wins = 0
start(player1_wins, player2_wins)
