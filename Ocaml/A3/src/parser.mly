%{

  open AST
  open Exp

%}

%token <int32> INTCONST
%token <float> FLOATCONST
%token <bool> BOOLCONST
%token <string> ID

%token DEF LET WHILE IF THEN ELSE REF INT FLOAT BOOL UNIT TT

%token NOT DEREF
%token PLUS MINUS TIMES DIV
%token AND OR LT INT_EQ DEFEQ

%token LPAREN RPAREN LBRACE RBRACE SEMI EQ COLON COMMA EOF 

%start <(AST.ty, unit Exp.exp) AST.prog> prog

%%

prog:
| _ = INTCONST
  { {fundefs = [];
     result = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = EUnit;
	       ety_of = ()}}
   }



	

