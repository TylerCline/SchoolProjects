#**********************************************************
# Program : LAMain.py
#
# Author : Tyler Cline
# email : tc670611@ohio.edu
# 
# Description : This code is used as a syntactic parser for a basic
#               Grammar consisting of numbers 0-9, (, ), +, -, *, ^, and /
#               The parser takes tokens from the lexical analyzer and
#               uses its member functions to see if the grammar is valid
#               and compute the value of the expression
#
# Date: 3-16-2015
#**********************************************************
import LexicalAnalyzer

#*********************************************************
# Function: error()
#
# Purpose: To flag an error to the user if his expression 
#          was invalid
#
# Pre Conditions: The current lexeme is passed in and evaluated
#
# Post Conditions: The current lexeme is evaluated, if it is 
#                  unknown a lexical error is returned, if it is
#                  known a syntactic error is returned
#********************************************************

def error(token):
    if token == 'UNKNOWN':
        return("Lexical Error! " + la.nextLexeme_ + " is not a valid character for this grammar")

    else:
        return("Syntactic Error!")


#*********************************************************
# Function: factor()
#
# Purpose: To evaluate the current token
#
# Member Variables: result
#
# Pre Condition: the token from the lexical analyzer is used
#
# Post Condition: the token is evaluated. If it is a number
#                 we advance the lexical analyzer and return result
#                 If it is a left parenthesis, we result is expr()
#                 and we check to see if it ends in a right parenthesis.
#                 If it does not, then error() is called. If the token is
#                 minus we call -factor(). An error is given otherwise
#********************************************************        
def factor(): 
    if la.nextToken_ == "NUMBER":
        result = int(la.nextLexeme_)
        la.lex()
        return result


    elif la.nextToken_ == "LPAR":
        la.lex()
        result = expr()
        
        if la.nextToken_ == "RPAR":
            la.lex()
            return result
        if la.nextToken_ == "EOF":
            print(error(la.nextLexeme_))
            exit()
        else:
            print(error(la.nextToken_))
            exit()
            
    elif la.nextToken_ == "MINUS":
        la.lex()
        return - factor()
        
    else:
        print(error(la.nextToken_))
        exit()

        
#*********************************************************]
# Function: carret()
#
# Purpose: to add exponintiation to the expression
#
# Member Variables: result
# 
# Pre Condition: the current token from the lexical analyzer
#                is used for evaluation
#
# Post condition: the toke is evaluated and, if it is a carret symbol
#                 , the lexical analyzer is advanced and result is
#                 exponentiated with factor() while the token is still
#                 CARRET. When the loop breaks the result is returned
#********************************************************
def carret():   
    result = factor()
    while la.nextToken_ == "CARRET":
        
        la.lex()
        result = result ** factor()
        
    return result


#**********************************************************
# Function: term()
# 
# Purpose: To evaluate if the token is multiplication or division
#
# Member Variables: result
#
# Pre Condition: the current toke from the lexical analyzer is 
#                used for evaluation
#
# Post Condition: The toke is evaluated and, if it is a SLASH (/),
#                 we advance the lexical analyzer and call carret().
#                 if it is a STAR(*), we advance the lexical analyzer
#                 and call carret(). When the loop breaks result is returned
#***********************************************************
def term():
    result = carret()
    while la.nextToken_ == "STAR" or la.nextToken_ == "SLASH" or la.nextToken_ == 'CARRET':
            
        if la.nextToken_ == 'SLASH':
            la.lex()
            result = result / carret()
            
        elif la.nextToken_ == 'STAR':
            la.lex()
            result = result * carret()
        
    return result


#**********************************************************
# Function: expr()
#
# Purpose: to evaluate the current token and see if it is
#          a PLUS(+) or a MINUS(-)
#
# Member Variables: result
#
# Pre Condition: The current token from the lexical analyzer
#                is used for evaluation
#
# Post Condition: The token is evaluated. If the token is a PLUS (+)
#                 the lexical analyzer is advanced and term() is 
#                 added to result. If the token is MINUS(-), the lexical
#                 analyzer is advanced and term() is subtracted from
#                 result
#*********************************************************
def expr():
    
    result = term()
    while la.nextToken_ == "PLUS" or la.nextToken_ == "MINUS" :
        
        if la.nextToken_ == "PLUS":
            la.lex()
            result = result + term()
            
        else:
            la.lex()
            result = result - term()
            
    return result

expression = ' '
while expression != 'q':
    expression = input('->')
    la = LexicalAnalyzer.LexicalAnalyzer(expression)
    print(expr())
    
