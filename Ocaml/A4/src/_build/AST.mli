open Batteries
open BatFormat       

(** The [AST] module defines generic types useful in the construction
    of abstract syntax trees (ASTs). *)

(** The [Internal_error] exception indicates an unexpected error. We
    raise it in situations that are expected not to occur (e.g., a
    pattern-match case that is impossible because of a particular program
    invariant). *)
exception Internal_error of string

(** [id] is a general-purpose identifier type, represented as a
    string.  We distinguish [id]s from plain-old vanilla strings, as a
    distinguished type, to give OCaml's typechecker enough information to
    prevent us from using plain strings where an [id] is expected. This is
    useful for code maintenance: e.g., we may change the representation of
    [id] in the future. *)
type id =
  | Id of string

(** Likewise, a [label] (program point) is also just a string, but
    defined as a new distinct type. *)
type label = 
  | Label of id

(** A [tid] is an [id] with some extra information, typically a type
    (['a]). It's defined as a record with two projections. The first,
    [id_of], returns the [id]. The second, [ty_of], returns the [id]'s
    type, of OCaml type ['a]. *)
type 'a tid = 
  { id_of : id;
    ty_of : 'a }

(** [mk_tid] is just a convenience function, for constructing
    [tids]. *)
val mk_tid : id -> 'a -> 'a tid

(** [ty] is a datatype defining the types supported by the grumpy 
    language. Think of type [ty = ...] as a little like a tagged union 
    in C, with types
    - [int32]
    - [bool (=int1)]
    - [ty*]
    - [unit] 
*)
type ty =
  | TyInt          (** The type of 32-bit signed integers *)
  | TyFloat        (** The type of double-precision floating point numbers *)
  | TyBool         (** The type of booleans (e.g., [true] or [false]) *)
  | TyRef of ty    (** The type of references (pointers) to values of type [ty] *)
  | TyUnit         (** The "unit" type, which describes certain kinds of stateful 
                       computations *)

(** Is type [t] an arithmetic type? *)
val is_arith_ty : ty -> bool

(** The language supports three unary operations, or [unop]s. *)
type unop =
  | UMinus         (** Integer negation *)
  | UNot           (** Boolean negation *)
  | UDeref         (** Dereference *)

(** The language supports a number of binary operations, or [binop]s. *)        
type binop =
  | BPlus          (** Add two integers *)
  | BMinus         (** Subtract two integers *)
  | BTimes         (** Multiply two integers *)
  | BDiv           (** Divide two integers *)
  | BAnd           (** Take the conjunction of two booleans *)
  | BOr            (** Take the disjunction of two booleans *)
  | BLt            (** Compute less-than on integers *)
  | BIntEq         (** Equality on integers *)
  | BUpdate        (** Update a reference cell *) 
					   
(** The type [fundef] is a generic representation of (the abstract
    syntax of) a function, which we'll use across the intermediate
    languages of the compiler. It's parameterized over the types:

 - ['ty]: The kind of types associated with a particular intermediate representation
 - ['exp]: The kind of code associated with a particular intermediate representation *)
type ('ty,'exp) fundef = 
  { nm  : id;    (** The function's name, e.g. [f]*)
    args : ('ty tid) list; (** The types of this function's parameters. *)      
    ret_ty : 'ty;(** The function's return type. *)
    body : 'exp; (** The body of the function, an ['exp]. *)
  }

(** [prog], likewise, is a generic representation of programs that
    we'll use to represent programs in every intermediate language of the
    compiler.  It's also parameterized by types ['ty] and ['exp], the sort
    of type and code associated with a particular intermediate
    representation. *)
type ('ty,'exp) prog =
  { fundefs : (('ty,'exp) fundef) list; (** The list of functions that this program defines *)
    result  : 'exp;                     (** The "main" code that this program executes*)
  }

(** Finally, we provide a number of pretty-printing functions the the
    types defined above. *)
    
val pp_id : formatter -> id -> unit
val pp_label : formatter -> label -> unit
val pp_int : formatter -> int -> unit
val pp_float : formatter -> float -> unit
val pp_ty : formatter -> ty -> unit				   
val pp_tid : formatter -> 'a tid -> unit
val pp_unop : formatter -> unop -> unit
val pp_binop : formatter -> binop -> unit				     
val pp_list : formatter ->
  (formatter -> 'a -> unit) -> (formatter -> unit -> unit) ->
  'a list ->
  unit
val pp_comma : formatter -> unit -> unit
val pp_semi : formatter -> unit -> unit
val pp_nl : formatter -> unit -> unit
val pp_fundef : formatter ->
  (formatter -> 'exp -> unit) ->		
  (formatter -> 'ty -> unit) ->
  ('ty, 'exp) fundef ->
  unit
val pp_prog : formatter ->
  (formatter -> 'exp -> unit) ->
  (formatter -> 'ty -> unit) ->
  (formatter -> unit -> unit) ->	      
  ('ty, 'exp) prog -> 
  unit
val pp_to_string : (formatter -> unit) -> string
