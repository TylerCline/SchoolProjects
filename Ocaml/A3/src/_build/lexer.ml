# 1 "lexer.mll"
 
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

# 35 "lexer.ml"
let __ocaml_lex_tables = {
  Lexing.lex_base = 
   "\000\000\229\255\078\000\155\000\234\255\235\255\001\000\238\255\
    \239\255\240\255\241\255\242\255\002\000\245\255\012\000\001\000\
    \249\255\250\255\251\255\252\255\049\000\254\255\001\000\255\255\
    \233\255\002\000\253\255\247\255\246\255\243\255\237\255\165\000\
    \095\000\252\255\253\255\004\000\017\000\255\255\254\255";
  Lexing.lex_backtrk = 
   "\255\255\255\255\025\000\023\000\255\255\255\255\019\000\255\255\
    \255\255\255\255\255\255\255\255\011\000\255\255\026\000\026\000\
    \255\255\255\255\255\255\255\255\007\000\255\255\001\000\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\024\000\
    \255\255\255\255\255\255\003\000\003\000\255\255\255\255";
  Lexing.lex_default = 
   "\001\000\000\000\255\255\255\255\000\000\000\000\255\255\000\000\
    \000\000\000\000\000\000\000\000\255\255\000\000\255\255\255\255\
    \000\000\000\000\000\000\000\000\255\255\000\000\255\255\000\000\
    \000\000\025\000\000\000\000\000\000\000\000\000\000\000\255\255\
    \033\000\000\000\000\000\255\255\255\255\000\000\000\000";
  Lexing.lex_trans = 
   "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\023\000\021\000\021\000\026\000\022\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \023\000\019\000\000\000\000\000\000\000\000\000\015\000\027\000\
    \011\000\010\000\016\000\018\000\005\000\017\000\038\000\020\000\
    \003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
    \003\000\003\000\006\000\007\000\013\000\012\000\030\000\029\000\
    \037\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\024\000\000\000\000\000\000\000\000\000\
    \025\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\009\000\014\000\008\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \028\000\036\000\000\000\000\000\000\000\000\000\035\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\000\000\000\000\000\000\000\000\002\000\000\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\031\000\000\000\003\000\003\000\003\000\003\000\003\000\
    \003\000\003\000\003\000\003\000\003\000\031\000\031\000\031\000\
    \031\000\031\000\031\000\031\000\031\000\031\000\031\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \004\000\000\000\255\255\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\034\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000";
  Lexing.lex_check = 
   "\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\000\000\000\000\022\000\025\000\000\000\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \000\000\000\000\255\255\255\255\255\255\255\255\000\000\015\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\035\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\006\000\012\000\
    \036\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\020\000\255\255\255\255\255\255\255\255\
    \020\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \014\000\032\000\255\255\255\255\255\255\255\255\032\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\255\255\255\255\255\255\255\255\002\000\255\255\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\002\000\002\000\002\000\002\000\002\000\002\000\002\000\
    \002\000\003\000\255\255\003\000\003\000\003\000\003\000\003\000\
    \003\000\003\000\003\000\003\000\003\000\031\000\031\000\031\000\
    \031\000\031\000\031\000\031\000\031\000\031\000\031\000\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \000\000\255\255\025\000\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\032\000\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255";
  Lexing.lex_base_code = 
   "";
  Lexing.lex_backtrk_code = 
   "";
  Lexing.lex_default_code = 
   "";
  Lexing.lex_trans_code = 
   "";
  Lexing.lex_check_code = 
   "";
  Lexing.lex_code = 
   "";
}

let rec token lexbuf =
    __ocaml_lex_token_rec lexbuf 0
and __ocaml_lex_token_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 37 "lexer.mll"
                   ( token lexbuf )
# 184 "lexer.ml"

  | 1 ->
# 38 "lexer.mll"
               ( token lexbuf )
# 189 "lexer.ml"

  | 2 ->
# 39 "lexer.mll"
                             ( token lexbuf )
# 194 "lexer.ml"

  | 3 ->
# 40 "lexer.mll"
               ( DEREF )
# 199 "lexer.ml"

  | 4 ->
# 41 "lexer.mll"
                   ( PLUS )
# 204 "lexer.ml"

  | 5 ->
# 42 "lexer.mll"
                   ( MINUS )
# 209 "lexer.ml"

  | 6 ->
# 43 "lexer.mll"
                   ( TIMES )
# 214 "lexer.ml"

  | 7 ->
# 44 "lexer.mll"
                   ( DIV )
# 219 "lexer.ml"

  | 8 ->
# 45 "lexer.mll"
            ( AND )
# 224 "lexer.ml"

  | 9 ->
# 46 "lexer.mll"
            ( OR )
# 229 "lexer.ml"

  | 10 ->
# 47 "lexer.mll"
               ( LT )
# 234 "lexer.ml"

  | 11 ->
# 48 "lexer.mll"
            ( EQ )
# 239 "lexer.ml"

  | 12 ->
# 49 "lexer.mll"
            ( INT_EQ )
# 244 "lexer.ml"

  | 13 ->
# 50 "lexer.mll"
                   ( LPAREN )
# 249 "lexer.ml"

  | 14 ->
# 51 "lexer.mll"
                   ( RPAREN )
# 254 "lexer.ml"

  | 15 ->
# 52 "lexer.mll"
            ( LBRACE )
# 259 "lexer.ml"

  | 16 ->
# 53 "lexer.mll"
            ( RBRACE )
# 264 "lexer.ml"

  | 17 ->
# 54 "lexer.mll"
            ( SEMI )
# 269 "lexer.ml"

  | 18 ->
# 55 "lexer.mll"
              ( DEFEQ )
# 274 "lexer.ml"

  | 19 ->
# 56 "lexer.mll"
            ( COLON )
# 279 "lexer.ml"

  | 20 ->
# 57 "lexer.mll"
            ( COMMA )
# 284 "lexer.ml"

  | 21 ->
# 58 "lexer.mll"
            ( EOF )
# 289 "lexer.ml"

  | 22 ->
# 59 "lexer.mll"
            ( nested_comments 0 lexbuf )
# 294 "lexer.ml"

  | 23 ->
let
# 61 "lexer.mll"
                  lxm
# 300 "lexer.ml"
= Lexing.sub_lexeme lexbuf lexbuf.Lexing.lex_start_pos lexbuf.Lexing.lex_curr_pos in
# 62 "lexer.mll"
    ( print_string "INT(";
      let i = Int32.of_string lxm
      in print_int (Int32.to_int i);
        print_string ")";
        INTCONST(i)
    )
# 309 "lexer.ml"

  | 24 ->
let
# 68 "lexer.mll"
                               lxm
# 315 "lexer.ml"
= Lexing.sub_lexeme lexbuf lexbuf.Lexing.lex_start_pos lexbuf.Lexing.lex_curr_pos in
# 69 "lexer.mll"
     ( print_string "FLOAT(";
		     let i = float_of_string lxm
		     in print_float (i);
		     FLOATCONST(i)
		   )
# 323 "lexer.ml"

  | 25 ->
let
# 74 "lexer.mll"
                                                         id
# 329 "lexer.ml"
= Lexing.sub_lexeme lexbuf lexbuf.Lexing.lex_start_pos lexbuf.Lexing.lex_curr_pos in
# 75 "lexer.mll"
               ( try
                   Hashtbl.find keyword_table id
                 with Not_found ->
                   ID id ;)
# 336 "lexer.ml"

  | 26 ->
# 80 "lexer.mll"
     ( raise (Syntax_err ("Unexpected char: " ^ Lexing.lexeme lexbuf)) )
# 341 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_token_rec lexbuf __ocaml_lex_state

and nested_comments level lexbuf =
    __ocaml_lex_nested_comments_rec level lexbuf 32
and __ocaml_lex_nested_comments_rec level lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 84 "lexer.mll"
         ( if level = 0 then token lexbuf  
           else nested_comments (level-1) lexbuf )
# 354 "lexer.ml"

  | 1 ->
# 86 "lexer.mll"
         ( nested_comments (level+1) lexbuf)
# 359 "lexer.ml"

  | 2 ->
# 87 "lexer.mll"
         (raise End_of_file)
# 364 "lexer.ml"

  | 3 ->
# 88 "lexer.mll"
       ( nested_comments level lexbuf )
# 369 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_nested_comments_rec level lexbuf __ocaml_lex_state

;;

