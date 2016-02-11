(* A1: intro2.ml *)

(* This assignment is subject to revision until its post date *)

(** EXERCISE 1: Fill out the following README: (1 point) *)

(* README

 Name: Tyler Cline
 Year (e.g., Sophomore, Junior): Senior
 ID: 100124250

 *)

(** EXERCISE 2: Sign up for Piazza. (2 points) 

    If you haven't done so by the due-date for this assignment, 
    you will lose points!
*)

(** ************ PART I: More OCaml Intro. **************)

(** (MUTUAL) RECURSION *)

(* As a warmup, consider the following function, [evenb], that returns a
   Boolean value [true] if it's integer argument [x] is even and [false]
   otherwise (in case [x] is odd). *)

(* precondition: x >= 0 *)
let rec evenb (x : int) : bool =
  if x = 0 || x = 2 then true
  else if x = 1 then false
  else evenb (x - 2)

(*
# evenb 23;;
- : bool = false
# evenb 24;;
- : bool = true
 *)

(* This function introduces a couple new OCaml features that we may have 
   only briefly looked at in class: 
   - The type [bool], of Boolean values
   - The equality comparison operator (=), as in [x = 0]
   - The Boolean disjunction operator (||), as in [x = 0 || x = 2]
   - The [let rec] keyword, for introducing recursive function 
     definitions. *)

(* In OCaml, it's possible to define mutually recursive functions as
   well. For example, consider the following pair of functions [f] and 
   [g] that mutually recursively decrement from an integer [x >= 0] down 
   to 0: *)

(* precondition: x >= 0 *)
let rec f (x : int) : int =
  if x = 0 then 0 else g (x-1)

and g (x : int) : int =
  if x = 0 then 0 else f (x-1)

(*
# f 3;;
f 3;;
- : int = 0
# g 3;;
g 3;;
- : int = 0
 *)

(* In general, a group of mutually recursive functions is defined by 
   introducing the first function with [let ref ...] and the remaining 
   functions in the group with [and ...]. *)

(** EXERCISE 3: (4 points) *)

(* Using only function definitions, if/then/else, mutual recursion,
   and subtraction by 1, define a pair of mutually recursive functions 
     - even : int -> bool 
     - odd : int -> bool 
   s.t. [even n = true] iff [n] for [n >= 0] is even and 
        [odd n = true] iff [n] for [n >= 0] is odd. 
   In particular, your definitions of [even] and [odd] should not refer
   to [evenb] defined above (or the 'mod' function).

   Examples: 

     even 3 = false
     even 27 = false
     even 40 = true
     odd 3 = true
     odd 0 = false
 *)

let rec even (x : int) : bool = 
    if x == 0 then
         true
    else 
       if x mod 2 == 0 then
           true    
       else
           odd (x-1)
and odd (x : int) : bool =
    if x == 0 then
         false
    else 
        if x mod 2 != 0 then
           true
        else
           even (x-1)

 

let rev_list l =
  let rec rev_acc acc = function
    | [] -> acc
    | hd::tl -> rev_acc (hd::acc) tl
  in 
  rev_acc [] l

(** DATA TYPES *)
			 
(* The basic data types in OCaml include everything you'd typically see in 
   imperative languages like C. We've already seen 
     - int       Fixed-width signed integers
     - bool      The Boolean values [true] and [false]
   but there's also
     - float     Floating-point numbers
     - char      Characters
     - string    Sequences of characters
   (See http://caml.inria.fr/pub/docs/manual-ocaml/coreexamples.html for 
    more details.) *)

(* In addition, OCaml supports a number of compound or composite types
   (as well as user-defined types, which we'll see later on in this 
   assignment).  For example, the type of pairs of integer values is
   written: *)

type intPair = (int * int)       (* The type of pairs of integers *)

(* [type intPair ...] introduces a type "synonym", a new name for the 
   the type [(int * int)], the type of pairs of integers. *)

(* Pairs, or values of pair type, are written 
   [(<fst-val>, <snd-val>)]: *)

let intPair_example : intPair = (1, 2)

(* To extract the first or second element of a pair, use 
   [fst] for the first component and [snd] for the second. *)

let x = fst intPair_example (* = 1 *)

let y = snd intPair_example (* = 2 *)

(* It's also possible (and many times preferable) to use let-syntax 
   to destruct pairs. For example: *)

let (z, w) = intPair_example;;
z + w;; (* = 3 *)

(* The types on the two sides of a pair need not be the same. For example, 
   here's a type synonym for the type of integer-Boolean pairs: *)

type intBoolPair = (int * bool)

let intBoolPair_example : intBoolPair = (3, false)

(** EXERCISE 4: (1 point) *)

(* Using [fst], [snd], and the pair constructor [( , )],
   define a function, [swapFstSnd], that takes a pair of integers and 
   swaps their components. So for example, [swapFstSnd (1, 2) = (2, 1)]. *)

let swapFstSnd ((int1,int2) : intPair) : intPair =
    (int2, int1)

(** ************ PART II: Lists **************)
					  
(* The second composite data type we'll look at in this assignment is
   lists, which are an abstraction of the linked lists you'd typically
   code yourself in a language like C.

   In OCaml, a list is either empty, written [], or a "cons" of a "head"
   element, say 1, tacked on to the front of a "tail" list, say l. 

     NOTE: Previously in this document, square brackets "[ ... ]" were 
     used to delimit code examples within comments. Since "[ ... ]" plays
     double-duty to denote lists, we'll use quotation marks instead of 
     square brackets in this section to delimit code.

   Cons is written as "1 :: l". For example: the list containing the 
   integers 1, 2, 3 in that order can be written in OCaml as: *)

let list1 : int list = 1 :: 2 :: 3 :: []

(* That is, list1 is 
     1 cons'd onto 
       (the list 2 cons'd onto 
          (the list 3 cons'd onto 
             the empty list [])) *)
					
(* Lists can also be built with the syntax: *)

let list1' = [1; 2; 3]

(* which is equivalent to the above, and in general preferable because 
   it's more compact. *)

(* The type of list1 (and of list1') is "int list", which stands for
   "list of integers". In general, lists may range over any type (they 
   are what is called "polymorphic"), so we can have "bool list", "(int
   list) list" (the type of lists of lists of integers), etc. *)

(* As a complement to building lists, we'd also like to have a way to 
   compute with them. This is done by what's called "pattern-matching"
   in OCaml. Example: *)

let rec sumIntList (l : int list) : int =
  match l with
  | [] -> 0
  | x :: l' -> x + sumIntList l'

(*
# sumIntList list1;;
sumIntList list1;;
- : int = 6
# sumIntList list1';;
sumIntList list1';;
- : int = 6
*)

(* Here's a breakdown: 

let rec sumIntList (l : int list) : int =
  match l with      <-- Start a "pattern match" on the list l. 
                        That is, we'll consider all the ways in which we 
                        could have built the list l (hint: there are only 
                        two). For each case, we may associate variables with 
                        the parts of the list we're matching, and will define a 
                        different result -- probably depending on the variables 
                        we matched to various parts of the list -- in each 
                        case. 

  | [] -> 0         <-- So for example, when l is the empty list [], we just return 0.

  | x :: l' ->      <-- Otherwise, when l is composed of head x cons'd onto tail l',
    x +             <-- return x added to 
    sumIntList l'   <-- sumIntList recursively applied to the tail l'. 

                        In the above, the variable "x" in the pattern " x :: l' " 
                        is bound to the head (first element) of the list l, and may 
                        be referred to in the body of the match. Likewise, l' is 
                        bound to the tail of the list l (all elements except the first
                        one) and may also be referred to in the body of the match. *)

(** EXERCISE 5: (6 points) *)			      
   
(* Using pattern-matching, recursion, and a let-bound inner auxiliary function,
   define a new function, sumFirstLast (l : int list) : int list, that sums 
   the first and last elements of an integer list. If the list l is empty,
   sumFirstLast should return 0. If l contains just a single element, then 
   that element is both first and last. For example:

     sumFirstLast [1; 2; 3] = 4
     sumFirstLast [1] = 2
     sumFirstLast [] = 0
     sumFirstLast [-1; 1] = 0
   
 *)
let rec sumFirstLast (l : int list) : int =
    match l with
    | [] -> 0
    | [x] -> x + x
    | x::[y] -> x + y
    | x::l' ->
        let rec tail lst : int =  
        match lst with 
        |[] -> 0
        |[q] -> sumFirstLast [x; q]
        |q::w -> tail w 
    in tail l'
        

		      
(** EXERCISE 6: (6 points) *)  

(* Define a function, decToBin (n : int) : bool list, that returns the
   little-endian binary encoding, as a list of boolean values, of the
   positive integer n. For example,
   
     decToBin 1 = [true]
     decToBin 2 = [false; true]
     decToBin 3 = [true; true]
     decToBin 23 = [true; true; true; false; true]
 *)

(* precondition: n > 0 *)
(* let rec decToBin (n : int) : bool list = ... *)

let decToBin (x : int) : bool list = 
      let rec binaryConversion y lst = 
         match y with 
        | 0 -> rev_list lst
        | _ -> binaryConversion (y/2) ((if y mod 2 == 1 then true else false)::lst)
      in
      binaryConversion x []



(** ************ PART III: Data Types **************)

(* If you recall from class, it's possible in OCaml for users both to define 
   their own data types and to use standard OCaml language features, like 
   pattern-matching, to compute over values of user-defined types. 

   For example, here's the type of 2d points which you saw in class on
   Tuesday:
 *)

type point = (float * float);;	     

(* The type [point] is really just an abbreviation for the type of pairs 
   of floats, written (float * float). *)

(* Of course, more interesting data types are encodable as well. For example, 
   the following is a (highly inefficient) unary encoding of the natural 
   numbers, defined as an OCaml data type: *)

type nat =
  | Zero           (* a constructor for the natural number 0 *)
  | Succ of nat    (* "successor": a constructor for n + 1 *)
;;

(* The constructor [Zero] represents the natural number 0. [Succ n] represents, 
   in unary, the natural number n + 1. So the encoding of 3, for example, is 
   Succ (Succ (Succ Zero), or 1 1 1 0. 

   Here's a highly inefficient function to add two unary natural numbers (it's 
   running time is linear in the value of n): *)  

let rec addNat (n : nat) (m : nat) : nat =
  match n with
  | Zero -> m (* Zero plus any m is just m *)
  | Succ n' -> Succ (addNat n' m)	      

(* We can do better, of course. One way is just to use good old machine 
   integers, type [int] in OCaml. But such integers have a fixed range, as 
   determined by the word size of our machine. 

   Here's a representation of the positive natural numbers (starting
   from one) that gives arbitrary precision, just like [nat] above,
   yet doesn't pay quite as steep a performance penalty: *)

type binNat =
  | One
  | BO of binNat
  | BI of binNat   
;;

(* Do you see what's going on here? We're using a binary representation instead 
   of a unary one, in which: 
     - [One] represents the number 1
     - [BO n] represents, for a given [binNat] [n], the number [2 * n], and 
     - [BI n] represents [(2 * n) + 1]. 
   For example, here's the encoding of 5: *)

let two = BO One;;
let five = BI two;;
five;;  

  (* Another way to think about these constructors: One is the bit string 1, BO n 
     shifts n left by 1 and adds 0, BI n shifts n left by 1 and adds 1. *)
  

(** EXERCISE 7: (6 points) *)  
  
(* Write a function, intToBinNat (x : int) : binNat, that maps an integer [x] to 
   the equivalent [binNat]. You may assume that [x > 0]. *)

let rec intToBinNat (x : int) : binNat = 
    match x with 
   |1 -> One
   |2 -> BO One
   |3 -> BI One
   |_ -> if x mod 2 == 0 then
            BO (intToBinNat (x / 2))
         else
            BI (intToBinNat (x / 2))

(* precondition: x > 0 *)
(* let rec intToBinNat (x : int) : binNat = ... *)  
  
(** EXERCISE 8: (4 points) *)  
  
(* Write a function, binNatToInt (x : binNat) : int, that maps a binary positive
   natural [x] to the equivalent integer. *)

(* let rec binNatToInt (x : binNat) : int = ... *)

(* To convince yourself that your [intToBinNat] and [binNatToInt] functions are 
   defined correctly, write at least three test cases that exploit the fact that 
   [intToBinNat] and [binNatToInt] are inverses. That is, it should be the case that:
    
      For all positive integers n, binNatToInt (intToBinNat n) = n
 *)

let rec binNatToInt (x : binNat) : int = 
match x with
|One -> 1
|BO One -> 2
|BI One -> 3
|BO x'  -> 2*(binNatToInt (x'))
|BI x'  -> 2*(binNatToInt (x')) + 1

(** ************ PART IV: Polymorphism **************)

(* In class, we defined a so-called "polymorphic" list data type that looked like: *)

type 'a mylist =
  | Nil
  | Cons of ('a * 'a mylist)

(* Recall that ['a] is a type variable, sort of like "<T>" in a generic class in  
   Java. The type ['a list] can be instantiated to any old type we like. For 
   example, the type [int mylist] giving the type of lists with integer elements. 

   (We call this new datatype [mylist] so as not to clash with OCaml's
    standard [list].)
 *)

(* As we also saw in class, it's possible to write generic functions
   over polymorphic data types, like the following generic map
   function: *)

let rec mymap (f : 'a -> 'b) (l : 'a mylist) : 'b mylist =
  match l with
  | Nil -> Nil
  | Cons(x, l') -> Cons (f x, mymap f l')
;;
  
mymap (fun x -> x * x) (Cons(1, Cons(2, Cons(3, Nil))));;
mymap (fun x -> not x) (Cons(false, Cons(true, Nil)));;

(** EXERCISE 9: (4 points) *)

(* Write your own polymorphic data type, for binary trees. Your type 
   declaration should begin: 
 
     type 'a mytree = ... 

   and should contain two constructors, one for leaves (which contain 
   no data) and one for nodes which contain a value of type 'a, a left 
   subtree and a right subtree. 

   Name the leaf constructor "Leaf" and the node constructor "Node".

   Encode the arguments to the Node constructor in the following order:
     - first the data element, of type 'a
     - then the left subtree
     - then the right subtree.
*)  

(* type 'a mytree = ... *)

type 'a mytree =
  | Leaf 
  | Node of ('a * 'a mytree * 'a mytree)

(** EXERCISE 10: (5 points) *)

(* Write a function, sumMyTree, that sums the integer elements in an 
   [int mytree] (that is, a [mytree] specialized to ['a = int]). *)

(* let rec sumMyTree (t : int mytree) : int = ... *)

let rec sumMyTree (t : int mytree) : int = 
  match t with 
    | Leaf -> 0
    | Node(a, l, r) -> a + sumMyTree l + sumMyTree r
  
(** EXERCISE 11: (6 points) *)

(* Using your [mytree] definition as a starting point, write a generic 
   function [mytreeMap] that maps a function of type ['a -> 'b] over 
   the elements of an ['a mytree]. *)

(* let rec mytreeMap (f : 'a -> 'b) (t : 'a mytree) : 'b mytree = ... *)

let rec mytreeMap (f : 'a -> 'b) (t : 'a mytree) : 'b mytree = 
    match t with
    | Leaf -> Leaf
    | Node(a, l, r) -> Node(f(a), mytreeMap f l, mytreeMap f r)


