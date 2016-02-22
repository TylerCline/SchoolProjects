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
%left OR AND
%nonassoc LT INT_EQ
%left PLUS MINUS
%left TIMES DIV
%nonassoc NOT DEREF

%%

ty:
  | INT		{ TyInt }
  | FLOAT	{ TyFloat }
  | BOOL	{ TyBool }
  | t = ty REF	{ TyRef t }
  | UNIT	{ TyUnit }

unop:
  | MINUS 	{ UMinus }
  | NOT		{ UNot }
  | DEREF	{ UDeref }

binop:
  | PLUS	{ BPlus }
  | MINUS	{ BMinus }
  | TIMES	{ BTimes }
  | DIV		{ BDiv }
  | AND		{ BAnd }
  | OR		{ BOr }
  | LT		{ BLt }
  | INT_EQ	{ BIntEq }
  | DEFEQ	{ BUpdate }



exp:
  | LPAREN ex = exp RPAREN
	{start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = ex.exp_of; 
	       ety_of = ()
        }
 	
  | LBRACE ex = exp RBRACE
	{start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = (EScope ex);
	       ety_of = ()
        }
  | ex = ID  {EId ex}
  | ex = INTCONST {EInt ex}
  | ex = FLOATCONST {EFloat ex}
  | ex = BOOLCONST {if ex == TRUE then ETRue else EFalse}
  | ex = exp SEMI exp
	{start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = (ESeq (BatString.to_list ex));
	       ety_of = ()
        }
  | x = ID RPAREN ex = exp RPAREN {ECall (m, (BatString.to_list ex))}
  | REF ex = exp  {ERef ex}
  | ex = unop x = exp {EUnop (ex, x)}
  | ex = exp x = binop e = exp {EBinop (x, ex, e)}
  | IF ex = exp THEN x = exp ELSE y = exp  {EIf (ex, x, y)}
  | WHILE ex = exp RBRACE x = exp LBRACE {EWhile (ex, x)}
  | LET c = ID EQ x = exp IN y = exp  {ELet (c, x, y)}
  | TT {EUnit}

(*fundef:
  | DEF x = ID RPAREN y = ID COLON z = ty COMMA LPAREN COLON RBRACE v = exp LBRACE
    {start_of = $startpos;
     end_of = $endpos;
     exp_of = (ESeq ex);
     ety_of = ()
    }
Not sure how to impliment this yet
*)
prog:
| a = exp EOF
  { {fundefs = [];
     result = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = EUnit;
	       ety_of = ()}}

   } 
