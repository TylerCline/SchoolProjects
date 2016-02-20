%{

  open AST
  open Exp

%}

%token <int32> INTCONST
%token <float> FLOATCONST
%token <bool> BOOLCONST
%token <string> ID

%token DEF LET WHILE IF THEN ELSE REF INT FLOAT BOOL UNIT TT IN

%token NOT DEREF
%token PLUS MINUS TIMES DIV
%token AND OR LT INT_EQ DEFEQ

%token LPAREN RPAREN LBRACE RBRACE SEMI EQ COLON COMMA EOF 

%start <(AST.ty, unit Exp.exp) AST.prog> prog

%right SEMI
%left OR 
%left AND
%nonassoc LT INT_EQ
%left PLUS MINUS
%left TIMES DIV
%nonassoc NOT DEREF

%%

(** NOTE: to complete the assignment, you will have to change
    the definition of the prog rule given below. *)

%inline ty:
 |INT   {TyInt}
 |FLOAT {TyFloat}
 |BOOL  {TyBool}
 |REF   {TyRef ty}
 |UNIT  {TyUnit}

%inline unop:
 |MINUS {UMinus}
 |NOT   {UNot}
 |DEREF {UDeref}

%inline binop:
 |PLUS {BPlus}
 |MINUS {BMinus}
 |TIMES {BTimes}
 |DIV   {BDiv}
 |AND   {BAnd}
 |OR    {BOr}
 |LT    {BLt}
 |INT_EQ {BIntEq}
 |DEFEQ {BUpdate}

exp:
 |LPAREN n = exp RPAREN {n}
 |LBRACE n = exp RBRACE {Escope n}
 |n = ID {EId id}
 |n = INTCONST {Eint n}
 |n = FLOATCONST {EFloat n}
 |n = BOOLCONST {if n = true then ETrue else EFalse}
 |exp SEMI c = exp {ESeq (BatString.to_list c)}
 |m = ID LPAREN n = exp RPAREN {ECall m (BatString.to_list n)}
 |REF n = exp {ERef n}
 |n = unop x = exp {EUnop (n, x)}
 |n = exp  x = binop a = exp {EBinop (x, n, a)}
 |IF n = exp THEN x = exp ELSE a = exp {EIf (n, x, a)}
 |WHILE x = exp LBRACE y = exp RBRACE {EWhile (x, y)}
 |LET z = ID EQ x = exp IN y = exp {ELet (z,x,y)}
 |TT  {EUnit}

fundef:
  |DEF ID LPAREN ID COLON x = ty RPAREN COLON z = ty LBRACE g = exp RBRACE {x, y, z, g}

prog:
 | _ = INTCONST
  { {fundefs = [];
     result = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = EUnit;
	       ety_of = ()}}
   }



	

