
(* The type of tokens. *)

type token = 
  | WHILE
  | UNIT
  | TT
  | TIMES
  | THEN
  | SEMI
  | RPAREN
  | REF
  | RBRACE
  | PLUS
  | OR
  | NOT
  | MINUS
  | LT
  | LPAREN
  | LET
  | LBRACE
  | INT_EQ
  | INTCONST of (int32)
  | INT
  | IN
  | IF
  | ID of (string)
  | FLOATCONST of (float)
  | FLOAT
  | EQ
  | EOF
  | ELSE
  | DIV
  | DEREF
  | DEFEQ
  | DEF
  | COMMA
  | COLON
  | BOOLCONST of (bool)
  | BOOL
  | AND

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> ((AST.ty, unit Exp.exp) AST.prog)
