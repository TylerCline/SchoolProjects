(*
  NAME: Tyler Cline
  OUID: tc670611

  NAME: Jordan Leach
  OUID: jl499611
*)

open Batteries
open BatFormat

open Lexing

open Lexer
open AST
open Exp

(** Declare a new exception type, Ty_error, which takes as 
    its first argument a message describing the type error *)
       
exception Ty_error of string 

(** Given an error string, raise the associated type error *)
			
let raise_ty_err (err : string) = raise (Ty_error err)

(** The type of type environments \Gamma, mapping identifiers to the
    types they've been assigned *)
					
type ty_env = ty Symtab.t

(** The type of the global environment \Delta, mapping function names 
    (identifiers) to the types of their arguments and to their 
    result type *)
		 
type globs_env = (ty list * ty) Symtab.t

(** delta is a file-scope reference to the global type environment *)
				
let delta : globs_env ref = ref (Symtab.create ())

(** Return the argument types and return type associated with 
    function id [f] in [delta], or raise a type error. *)
				
let ety_of_funid (f : id) : (ty list * ty) =
  match Symtab.get f !delta with
  | None ->
     raise_ty_err
       (pp_to_string
	  (fun ppf ->
	   fprintf ppf "unbound function identifier '%a'" pp_id f))
  | Some tys -> tys

(** Is id [x] bound in environment [gamma]? *)
				
let is_bound (gamma : ty_env) (x : id) : bool =
  BatOption.is_some (Symtab.get x gamma)

(** The tycheck function checks whether [e] is well-typed in 
    environment [gamma]. If so, the function returns the new 
    expression equal to [e] but annotated with its type (in 
    the [ety_of] field -- see type ['a exp] in [exp.mli] for 
    additional information). *)
let rec tycheck (gamma : ty_env) (e : 'a exp) : ty exp =
  match e.exp_of with
  | EInt i -> { e with exp_of = EInt i; ety_of = TyInt }
  | EFloat f -> { e with exp_of = EFloat f; ety_of = TyFloat }
  | EId x -> 
     (match Symtab.get x gamma with
      | None ->
	 raise_ty_err
	   (pp_to_string (fun ppf -> fprintf ppf "unbound identifier '%a'@ at position %a" 
      				             pp_id x pp_pos e))
      | Some t ->
	 { e with 
             exp_of = EId x; 
             ety_of = t
     })
  | ETrue -> { e with exp_of = ETrue; ety_of = TyBool }
  | EFalse -> { e with exp_of = EFalse; ety_of = TyBool }
  | ELet(i, e1, e2) -> let t1 = tycheck gamma e1 in
                       let t2 = tycheck (Symtab.set i t1.ety_of gamma) e2 in
                       {e with exp_of = ELet(i, t1, t2); ety_of = t2.ety_of}
  | EUnit -> { e with exp_of = EUnit; ety_of = TyUnit}
  | EIf (e1, e2, e3) -> let t1 = tycheck gamma e1 in
                        let t2 = tycheck gamma e2 in
                        let t3 = tycheck gamma e3 in
                        (match t1.ety_of with
                         | TyBool -> if t2.ety_of = t3.ety_of then
                                       {e with exp_of = EIf(t1, t2, t3); ety_of = t2.ety_of}
                                       else {e with exp_of = EUnit; ety_of = TyUnit}
                         | _ -> raise_ty_err "EIf type error"                                                                                  
                        )
  |EScope e1 -> let t1 = tycheck gamma e1 in
                (match t1.ety_of with
                 | (TyInt | TyBool | TyFloat | TyUnit) ->
                            {e with exp_of = EScope t1; ety_of = t1.ety_of}
                 |_ -> raise_ty_err "Escope error"
                )
  | ESeq r -> let rec iterate (lst : ('a exp) list) : (ty exp) list =
              match lst with
              | [] -> [{e with exp_of = EUnit; ety_of = TyUnit}]
              | [h] -> let t1 = tycheck gamma h in [{e with exp_of = t1.exp_of; ety_of = t1.ety_of}]
              | h::tl -> let t2 = tycheck gamma h in
                         (match t2.ety_of with
                          |TyUnit -> {e with exp_of = t2.exp_of; ety_of = t2.ety_of}::(iterate tl)
                          |_ -> raise_ty_err "not Unit"
                         )
              in let rec get_last (l : ('a exp) list) : ty exp =
              match l with
              | [h] -> let t1 = tycheck gamma h in {e with exp_of = t1.exp_of; ety_of = t1.ety_of}
              | h::tl -> get_last tl
              | _ -> raise_ty_err "Blahhhhhhh"
                 in {e with exp_of = ESeq (iterate r); ety_of = (get_last r).ety_of}
                   
  | ERef e -> let t1 = tycheck gamma e in {e with exp_of = ERef t1; ety_of = TyRef(t1.ety_of)}
  | EWhile (e1, e2) -> let t1 = tycheck gamma e1 in
                       let t2 = tycheck gamma e2 in
                       {e with exp_of = EWhile(t1, t2); ety_of = TyUnit}                    
  | EUnop(u, e1) -> tycheck_unop e gamma u e1			
  | EBinop(b, e1, e2) ->  tycheck_binop e gamma b e1 e2
  | ECall(i, e1) -> (match (ety_of_funid i) with
                       | (func_args_ty, func_ret_ty) ->
                           let cl = BatList.map (fun (x) -> tycheck gamma x) e1 in
                            if (args func_args_ty cl)
                               then {e with exp_of = ECall(i, cl); ety_of = func_ret_ty}
                            else raise_ty_err "This code is dumb")

and args (function_args : 'ty list) (call_args : ('ty exp) list) : bool =
      match function_args, call_args with
      | ( [], [] ) -> true
      | ( a1 :: al, a2 :: al2) -> if (ty_eq a1 a2.ety_of) 
                                    then args al al2 
                                    else raise_ty_err "Args Error"
      | _ -> raise_ty_err "Args Error"
(** [assert_ty gamma e t]: Raise a type error if [e] does not 
    have type [t] in [gamma]. Returns a type-annotated version 
    of [e] (just as in [tycheck]) *)
                   
and assert_ty (gamma : ty_env) (e : 'a exp) (t : ty) : ty exp =
 let t1 = tycheck gamma e in
  if t1.ety_of = t then {e with exp_of = t1.exp_of; ety_of = t1.ety_of}
  else raise_ty_err "Assert Ty Unimplemented"

(** [assert_arith gamma e]: Raise a type error if [e] does not have an
    arithmetic type (see [exp.ml] and [exp.mli] for the definition of
    "arithmetic type". Returns a type-annotated version of [e]
    (just as in [tycheck]) *)
	    
and assert_arith (gamma : ty_env) (e : 'a exp) : ty exp =
  let t1 = tycheck gamma e in
  if is_arith_ty t1.ety_of then {e with exp_of = t1.exp_of; ety_of = t1.ety_of}
  else raise_ty_err "Arithmetic ty unimplemented"    

(** [tycheck_unop e gamma u e2]: 
    Assumes [e = EUnop(u, e2)]. 
    Checks that [EUnop(u, e2)] is well-typed in [gamma].
    Returns a type-annotated version of [e]. *)
		  
and tycheck_unop (e : 'a exp) (gamma : ty_env) (u : unop) (e2 : 'a exp) : ty exp =
  let t1 = tycheck gamma e2 in 
  (match (u, t1.ety_of) with
   |(UNot, TyBool) -> {e with exp_of = EUnop(u, t1); ety_of = TyBool}
   |(UMinus, TyInt) -> {e with exp_of = EUnop(u,t1) ; ety_of = TyInt}
   |(UMinus, TyFloat) -> {e with exp_of = EUnop(u,t1) ; ety_of = TyFloat}
   |(UDeref, TyRef(r)) -> {e with exp_of = EUnop(u,t1) ; ety_of = r}
   |(_,_) -> {e with exp_of = EUnit; ety_of = TyUnit}				
 )     

(** [tycheck_binop e gamma b e1 e2]: 
    Assumes [e = EBinop(b, e1, e2)]. 
    Checks that [EBinop(b, e1, e2)] is well-typed in [gamma].
    Returns a type-annotated version of [e]. *)
		  
and tycheck_binop (e : 'a exp) (gamma : ty_env)
                  (b : binop) (e1 : 'a exp) (e2 : 'a exp) : ty exp =
 let t1 = tycheck gamma e1 in 
 let t2 = tycheck gamma e2 in
 (match b with
 | (BPlus | BMinus | BTimes | BDiv) ->  if t1.ety_of = t2.ety_of && is_arith_ty t1.ety_of then
                                            {e with exp_of = EBinop(b, t1, t2); ety_of = t1.ety_of}
					else raise_ty_err "Binop arithmetic type error"
		
 | (BAnd | BOr) -> if t1.ety_of = t2.ety_of && t1.ety_of = TyBool
                                  then {e with exp_of = EBinop(b, t1, t2); ety_of = t1.ety_of}
				  else raise_ty_err "Binop boolean error"
 | BIntEq -> if t1.ety_of = t2.ety_of && t1.ety_of = TyInt
             then {e with exp_of = EBinop(b,t1,t2) ; ety_of = TyBool}
	     else raise_ty_err "Binop Equality Error"
					
 | BLt -> if t1.ety_of = t2.ety_of && is_arith_ty t1.ety_of
          then {e with exp_of = EBinop(b,t1,t2) ; ety_of = TyBool}
          else raise_ty_err "Binop Less Than Error"
		
 | BUpdate ->(match t1.ety_of with
              | TyRef a -> if a = t2.ety_of then
                             {e with exp_of = EBinop(b, t1, t2); ety_of = TyUnit}
               else raise_ty_err "Binop Update error"
              | a -> raise_ty_err "Binop Error")
 )
   
let rec mGamma (gamma : ty_env) (args : ('ty tid) list) : ty_env =
  match args with
  | [] -> gamma
  | x_tid :: l -> let nGamma = Symtab.set x_tid.id_of x_tid.ty_of gamma in
                   mGamma nGamma l
(** [tycheck_fundef f]:
    Checks that function [f] is well-typed. 
    Returns a type-annotated version of [f]. *)
	 
let tycheck_fundef (f : (ty, 'a exp) fundef) : (ty, ty exp) fundef =
  let tGamma = mGamma (Symtab.create ()) f.args in
    let args_ty = BatList.map (fun (x_tid) -> x_tid.ty_of) f.args in
      delta := Symtab.set f.nm (args_ty, f.ret_ty) !delta;
      let c_body = tycheck tGamma f.body in
        {f with ret_ty = c_body.ety_of; body = c_body}         

(** [tycheck_prog p]:
    Checks that program [p] is well-typed. 
    Returns a type-annotated version of [p]. *)
		  
let tycheck_prog (p : (ty, 'a exp) prog) : (ty, ty exp) prog =
  delta := Symtab.set (Id "putchar") ([TyInt], TyUnit) !delta;
  let funcLs = BatList.map (fun (x) -> tycheck_fundef x) p.fundefs in
    let typed_result = tycheck (Symtab.create ()) p.result in
     { fundefs = funcLs;
       result = typed_result }

let is_arith_ty (t : ty) : bool =
  match t with
  | (TyInt | TyFloat) -> true
  | _ -> false  
  
let is_bool_ty (t : ty) : bool =
	match t with
	| TyBool -> true
	| _ -> false
