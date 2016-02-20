{
  open Lexing
  open Parser
  open Printf

  exception Eof
  exception Syntax_err of string
	    
  let next_line lexbuf =
    let pos = lexbuf.lex_curr_p in
    lexbuf.lex_curr_p <-
      { pos with pos_bol = pos.pos_cnum;
                 pos_lnum = pos.pos_lnum + 1;
      }
}

let newline = '\r' | '\n' | "\r\n"

rule token = parse
  | "//"     			{comment lexbuf}
  | "/*"                        {comment lexbuf}
  | [' ' '\t']			{token lexbuf}
  | newline             	{next_line; token lexbuf}
  | ['0'-'9']+ as lxm   	{ INTCONST(Int32.of_string lxm) }
  | "while"             	{WHILE}
  | "tt"           		{TT}
  | "then"              	{THEN}
  | ';'                 	{SEMI}
  | ')'   			{RPAREN}
  | "ref"			{REF}
  | '}'                 	{RBRACE}
  | '+'                 	{PLUS}
  | "||" 			{OR}
  | "not" 			{NOT}
  | '-' 			{MINUS}
  | '<'  			{LT}
  | '('   			{LPAREN}
  | "let"               	{LET}
  | '{'                 	{LBRACE}
  | "==" 			{INT_EQ}
  | "int" 			{INT}
  | "in"                	{IN}
  | "if"                	{IF}
  | ['a'-'z']+['A'-'Z']+'_'['a'-'z']*['A'-'Z']*['0'-'9']* as lxm {ID(lxm)}
  | ['-''+']['0'-'9']+'.'['0'-'9']* as lxm {FLOATCONST(float_of_string lxm)}
  | "float"             	{FLOAT}
  | "="                 	{EQ}
  | "else"              	{ELSE}
  | "def"               	{DEF}
  | ','                 	{COMMA}
  | ':'                  	{COLON}
  | "true"|"false" as lxm  	{BOOLCONST(bool_of_string lxm)}
  | '*' 			{TIMES}
  | '/' 			{DIV}
  | "&&" 			{AND}
  | ":=" 			{DEFEQ}
  | '!'   			{DEREF}
  | "bool"  			{BOOL}
  | "unit"  			{UNIT}
  |  eof    			{EOF}
and comment = parse
  | newline  {next_line; token lexbuf}
  | "*/"     {token lexbuf}
  | _        {comment lexbuf}

 (* { raise (Syntax_err ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }*)


  

