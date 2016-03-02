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
id:
  | x = ID {Id x}


exp:
  | LPAREN ex = exp RPAREN
	{ex}
 	
  | LBRACE ex = exp RBRACE
	{let x = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = (ex);
	       ety_of = ()} in
         EScope x}
  | ex = id  
           {EId ex}
  | ex = INTCONST 
           {EInt ex}
  | ex = FLOATCONST 
           {EFloat ex}
  | ex = BOOLCONST 
           {if ex == true then ETrue else EFalse}
  | ex = exp SEMI ey = exp
     {let x = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = (ex);
	       ety_of = ()} in
      let y = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ey);
          ety_of = ()} in
      ESeq ([x]@[y])}
  | i = id LPAREN ex = exp RPAREN 
     {let x = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = (ex);
	       ety_of = ()} in
      ECall (i, [x])}
  | REF ex = exp  
    {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ex);
          ety_of = ()} in
     ERef x}
  | ex = unop y = exp 
    {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (y);
          ety_of = ()} in
     EUnop(ex, x)}
  | ex = exp ey = binop ez = exp 
   {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ex);
          ety_of = ()} in
    let y = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ez);
          ety_of = ()} in
   EBinop(ey, x, y)}
  | IF ex = exp THEN ez = exp ELSE ey = exp  
   {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ex);
          ety_of = ()} in
    let y = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ez);
          ety_of = ()} in
    let z = 
       { start_of = $startpos;
         end_of = $endpos;
         exp_of = (ey);
         ety_of = ()}in
    EIf(x, y, z)}

  | WHILE ex = exp LBRACE ey = exp RBRACE 
      {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ex);
          ety_of = ()} in
    let y = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ey);
          ety_of = ()} in
    EWhile(x, y)}
  | LET c = id EQ ex = exp IN ey = exp 
   {let x = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ex);
          ety_of = ()} in
    let y = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (ey);
          ety_of = ()} in
    ELet(c, x, y)}
  | TT {EUnit}
  | UNIT {EUnit}
  | i = id LPAREN ex = INTCONST RPAREN
      {EInt ex}

fundef:
  | DEF x = ID RPAREN y = ID COLON z = ty LPAREN COLON  q = ty RBRACE v = exp LBRACE
    {let ex = 
        { start_of = $startpos;
          end_of = $endpos;
          exp_of = (v);
          ety_of = ()} in    

    {start_of = $startpos;
     end_of = $endpos;
     exp_of = ({nm = x; args = z; ret_ty = q; body = ex;})
     ety_of = ()
    }}
prog:
| a = exp EOF
  { {fundefs = [];
     result = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = EUnit;
	       ety_of = ()}}

   } 
(*| f = fundef x = exp a = ty v = exp EOF
  {{let ex = { start_of = $startpos;
          end_of = $endpos;
          exp_of = (x);
          ety_of = ()} in
    fundefs = [(a, ex) f];
    result = {start_of = $startpos;
     	       end_of = $endpos;
	       exp_of = EUnit;
	       ety_of = ()}}

   }*)
