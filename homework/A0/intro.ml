(* A0: intro.ml *)

(* == EXERCISE 1. == 

   Complete the following README *)

(* README

 Name: Tyler Cline
 Year (e.g., Sophomore, Junior): Senior
 ID: 100124250
 Have you ever used a functional programming language before?: Yes
 If so, which one?: Scheme

*)

(* Translation units in OCaml (.ml files) typically include a
   number of function and data type definitions, optionally followed
   by some "main" code. This is similar to a language like C or C++
   (.c or .cpp file) except that there is no "main" function per se,
   as we'll see below. OCaml also incorporates a notion of module 
   interfaces (.mli files), similar in spirit to, e.g., .h files. We'll 
   encounter those later, in the next assignment. *)

(* As an example of a function definition, the following chunk of code
   defines a function, called [inc], that increments its integer
   argument [x]: *)

let inc (x : int) : int = x + 1

(* Here's a breakdown: 

let       <-- The "let" keyword introduces function definitions.
inc       <-- This is the name of the function we're defining.

(x : int) <-- The sole argument to the this function is "x", which 
              must have type "int" (i.e., integer)

: int     <-- The "int" following the colon is the return type of
              the function. This function returns an integer.

= x + 1   <-- Finally, following the symbol "=" we define the 
              function's body, which may refer to the function's 
              argument "x". Note the lack of a "return" statement: 
              in OCaml, a function returns whichever value its 
              body expression evaluates to (here, x + 1).
*)

(* == EXERCISE 2. == 

   Define a function, [sum], that returns the sum of two integers
   [x] and [y]. *)

let sum(x : int )(y : int) : int = x + y

(* A distinguishing feature of functional programming languages is that 
   they support so-called "higher-order" functions -- functions that may 
   take and return other functions as arguments and results. *)

(* For example, here's a function, called [twice], that takes as an
   argument a second function [f], and applies [f] twice to the
   argument [x]: *)

let twice (f : int -> int) (x : int) : int = f (f x)

(* The type of the function parameter [f] is [int -> int] (read "int
   arrow int"), or the type of functions that take a single integer  
   as an argument and return an integer as result. *)

(* To use [twice], we might apply it to the function [inc] above, 
   as in: *)

let inc2_example : int = twice inc 2 (* = 4 *)

(* The effect of applying [twice] to [inc] and [2] is to increment 
   [2] twice, resulting in the return value [4]. That is, 

   twice inc 2 
 = inc (inc 2)          By the definition of [twice]
 = inc (2 + 1)          By the definition of [inc]
 = inc 3                By the definition of (+)
 = 3 + 1                By the definition of [inc]
 = 4                    By the definition of (+)
*)

(* Note that it's also possible to "partially apply" a function in
   OCaml. For example: *)

let inc2 : int -> int = twice inc

(* [inc2] is a function (of type [int -> int]) that when supplied with 
   an integer returns that integer plus 2. *)

(*  If we apply [inc2] to [2], we get the same result as in [inc2_example]: *)

let inc2_example' : int = inc2 2 (* = 4 *)

(* == EXERCISE 3. == 

   Using only addition (+), define a function [triplicate] that takes an
   integer [x] as argument and returns [3 * x]. *)

let triplicate(x : int) : int = 3 * x
