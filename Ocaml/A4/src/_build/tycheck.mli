open AST
open Exp

(** The [Tycheck] module defines Grumpy's type-checker. *)

(** [Ty_error err]: A type error, with error message [err] *)
exception Ty_error of string

(** [p' = tycheck_prog p]: Type-check program [p], returning the
    annotated program [p'] in which every sub-expression in each
    function this program defines has been annotated with its type. 
    
    @raise Ty_error On type errors, this function raises a type error
    coupled with an error message giving the line number at which the
    error occurred. *)
val tycheck_prog : (ty, 'a exp) prog -> (ty, ty exp) prog
