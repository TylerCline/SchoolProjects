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

 (* hash table section 12.7 Common Errors from: http://caml.inria.fr/pub/docs/manual-ocaml/lexyacc.html*)
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
(* end ocaml code *)

(* implement every token in parser *)
(* from calculator example:
	http://caml.inria.fr/pub/docs/manual-ocaml/lexyacc.html
*)

let newline = '\r' | '\n' | "\r\n"

rule token = parse 
  | [' ' '\t']     { token lexbuf }     (* skip blanks *)
  | newline	   { token lexbuf }
  | '/' '/' [^'\n']* '\n'	   { token lexbuf }     (* match everything except newline followed by newline*)
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
  | "/*"	   { comments 0 lexbuf } (* call comments parser thing *)
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
		     in print_float (i)
		     FLOATCONST(i)
		   } 
  | ['A'-'Z' 'a'-'z'] ['A'-'Z' 'a'-'z' '0'-'9' '_'] * as id
               { try
                   Hashtbl.find keyword_table id
                 with Not_found ->
                   ID id }
  | _
		   { raise (Syntax_err ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }

(* for multi-line comments: http://courses.softlab.ntua.gr/compilers/ocamllex-tutorial.pdf *)

and comments level = parse
  | "*)" { Printf.printf "comments (%d) end\n" level;
  if level = 0 then token lexbuf   (* get back to parse token *)
  else comments (level-1) lexbuf 
  }
  | "(*" { Printf.printf "comments (%d) start\n" (level+1);
  comments (level+1) lexbuf
  }
  | _  { comments level lexbuf }
  | eof  { print_endline "comments are not closed";
  raise End_of_file
  } 

