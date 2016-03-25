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

%nonassoc IN
%nonassoc ELSE
%right SEMI

%nonassoc DEFEQ
%nonassoc REF
	  
%left OR
%left AND
%nonassoc LT INT_EQ
%left PLUS MINUS
%left TIMES DIV
%nonassoc unary_over_binary

%start <(AST.ty, unit Exp.exp) AST.prog> prog

%%

mytype:
| LPAREN ty = mytype RPAREN 
  { ty }
| INT  
  { TyInt }
| FLOAT
  { TyFloat }
| BOOL
  { TyBool }
| ty = mytype REF
  { TyRef ty }
| UNIT 
  { TyUnit }

unop:
| MINUS
  { UMinus }
| NOT
  { UNot }
| DEREF
  { UDeref }

%inline binop:
| PLUS
  { BPlus }
| MINUS
  { BMinus }
| TIMES
  { BTimes }
| DIV
  { BDiv }
| AND
  { BAnd }
| OR
  { BOr }
| LT
  { BLt }
| INT_EQ
  { BIntEq }
| DEFEQ
  { BUpdate }

id:
| i = ID
  { Id i }

exp_list:
| l = separated_list(COMMA, exp)
  { l }
  
exp: 
| e = raw_exp
  { {start_of = $startpos; end_of = $endpos; exp_of = e; ety_of = ()} }
| LPAREN e = exp RPAREN 
  { e }

raw_exp:
| n = INTCONST
  { EInt n }
| n = FLOATCONST
  { EFloat n }
| i = id
  { EId i }
| e1 = exp SEMI e2 = exp
  { exp_seq e1 e2 }
| i = id LPAREN el = exp_list RPAREN
  { ECall(i, el) }
| REF e = exp 
  { ERef e }
| u = unop e = exp %prec unary_over_binary
  { EUnop(u, e) }
| e1 = exp b = binop e2 = exp
  { EBinop(b, e1, e2) }
| IF e1 = exp THEN e2 = exp ELSE e3 = exp
  { EIf(e1, e2, e3) }
| LET i = id EQ e1 = exp IN e2 = exp
  { ELet(i, e1, e2) }
| LBRACE e = exp RBRACE
  { EScope e }
| TT
  { EUnit }
| b = BOOLCONST
  { if b then ETrue else EFalse }
| WHILE e1 = exp LBRACE e2 = exp RBRACE
  { EWhile(e1, e2) }

arg:
| arg = id COLON arg_ty = mytype
  { mk_tid arg arg_ty }			    
  
arg_list:
| l = separated_list(COMMA, arg)
  { l }		    
  
fundef:
| DEF nm = id LPAREN args = arg_list RPAREN COLON ret_ty = mytype LBRACE body = exp RBRACE
  { {nm; args; ret_ty; body} }

prog:
| fs = list(fundef) e = exp EOF
  { {fundefs = fs; result = e} }



	

