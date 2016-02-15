
exception Error

let _eRR =
  Error

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

type _menhir_env = {
  _menhir_lexer: Lexing.lexbuf -> token;
  _menhir_lexbuf: Lexing.lexbuf;
  _menhir_token: token;
  mutable _menhir_error: bool
}

and _menhir_state
  

  open AST
  open Exp


let rec prog : (Lexing.lexbuf -> token) -> Lexing.lexbuf -> ((AST.ty, unit Exp.exp) AST.prog) =
  fun lexer lexbuf ->
    let _menhir_env = let _tok = Obj.magic () in
    {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = _tok;
      _menhir_error = false;
    } in
    Obj.magic (let _menhir_stack = ((), _menhir_env._menhir_lexbuf.Lexing.lex_curr_p) in
    let _menhir_env = let lexer = _menhir_env._menhir_lexer in
    let lexbuf = _menhir_env._menhir_lexbuf in
    let _tok = lexer lexbuf in
    {
      _menhir_lexer = lexer;
      _menhir_lexbuf = lexbuf;
      _menhir_token = _tok;
      _menhir_error = false;
    } in
    let _tok = _menhir_env._menhir_token in
    match _tok with
    | INTCONST _v ->
        let _menhir_stack = Obj.magic _menhir_stack in
        let _endpos = _menhir_env._menhir_lexbuf.Lexing.lex_curr_p in
        let _startpos = _menhir_env._menhir_lexbuf.Lexing.lex_start_p in
        let _menhir_stack = Obj.magic _menhir_stack in
        let _endpos___ = _endpos in
        let _ = _v in
        let _startpos___ = _startpos in
        let _v : ((AST.ty, unit Exp.exp) AST.prog) = let _endpos = _endpos___ in
        let _startpos = _startpos___ in
          ( {fundefs = [];
     result = {start_of = _startpos;
     	       end_of = _endpos;
	       exp_of = EUnit;
	       ety_of = ()}}
   ) in
        let _menhir_stack = Obj.magic _menhir_stack in
        let _menhir_stack = Obj.magic _menhir_stack in
        let _1 = _v in
        Obj.magic _1
    | _ ->
        assert (not _menhir_env._menhir_error);
        _menhir_env._menhir_error <- true;
        let _menhir_stack = Obj.magic _menhir_stack in
        raise _eRR)
  

