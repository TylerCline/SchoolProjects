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

let keyword_table = Hashtbl.create 53
  let _ =
    List.iter (fun (kwd, tok) -> Hashtbl.add keyword_table kwd tok)
              [ "def", DEF;
                "let", LET;
                "while", WHILE;
                "if", IF;
                "then", THEN;
                "else", ELSE;
                "ref", REF;
                "float", FLOAT;
                "bool", BOOL;
                "unit", UNIT;
                "tt", TT;
                "in", IN;
                "not", NOT ]
}

let newline = '\r' | '\n' | "\r\n"

rule token = parse 
  | [' ' '\t']     { token lexbuf }
  | newline	   { token lexbuf }
  | '/' '/' [^'\n']* '\n'	   { token lexbuf }  
  | '!'	   	   { DEREF }
  | '+'            { PLUS }
  | '-'            { MINUS }
  | '*'            { TIMES }
  | '/'            { DIV }
  | "&&"	   { AND }
  | "||"	   { OR }
  | '<'	   	   { LT }
  | '='		   { EQ }
  | "=="	   { INT_EQ }
  | '('            { LPAREN }
  | ')'            { RPAREN }	
  | '{'		   { LBRACE }
  | '}'		   { RBRACE }
  | ';'		   { SEMI }
  | ":="  	   { DEFEQ }
  | ':'		   { COLON }
  | ','		   { COMMA }
  | eof		   { EOF }
  | "/*"	   { nested_comments 0 lexbuf }
 
  | ['0'-'9']+ as lxm
    { print_string "INT(";
      let i = Int32.of_string lxm
      in print_int (Int32.to_int i);
        print_string ")";
        INTCONST(i)
    }
  | ['0'-'9']+'.'['0'-'9']* as lxm
		   { print_string "FLOAT(";
		     let i = float_of_string lxm
		     in print_float (i);
		     FLOATCONST(i)
		   } 
  | ['A'-'Z' 'a'-'z'] ['A'-'Z' 'a'-'z' '0'-'9' '_'] * as id
               { try
                   Hashtbl.find keyword_table id
                 with Not_found ->
                   ID id ;}
  | _
		   { raise (Syntax_err ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }


and nested_comments level = parse
  | "*/" { if level = 0 then token lexbuf  
           else nested_comments (level-1) lexbuf }
  | "/*" { nested_comments (level+1) lexbuf}
  | eof  {raise End_of_file}
  | _  { nested_comments level lexbuf }

