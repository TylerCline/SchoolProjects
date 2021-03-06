
(** EXERCISE 0: Fill out the following README: (1 point) *)

(* README

 Name: Tyler Cline
   ID: 100124250
 Year: Senior

 *)

open Batteries

(** * A2: Regular Expressions Re-Examined *)

(** ** Part I: Interpreting REs

    In part I of this assignment, your job is to define an interpreter
    for a small language of regular expressions (type ['char regexp]
    below). The interpreter won't necessarily be efficient (in fact,
    it'll be quite slow). Part II will speed things up through the use
    of "regular expression derivatives" (also known as "Brzozowski
    derivatives"). Although it's often more common to implement
    regular expression matchers via compilation first to NFAs then to
    DFAs (this is what lexers like ocamllex, which we'll use in the
    next assignment, do), RE derivatives present a fun and interesting
    alternative approach.

    Much of this assignment was developed using material from 

      "Regular-expression derivatives reexamined", 
      by Scott Owens, John Reppy, and Aaron Turon
      
   which is available here: 

      https://www.mpi-sws.org/~turon/re-deriv.pdf.

   *** Before you get started, read sections 1 through 3.2 (up through 
       "Using derivatives for RE matching") of 
       "Regular-expression derivatives reexamined". 

       Later parts of this assignment will refer to parts of this 
       paper. ***

 *)

(** The following data type ['char regexp] defines a little language
    of regular expressions (recall the RE language we saw in class in
    Week 3 -- go back to the lecture notes to refresh your memory if
    necessary!). As reference, you might also find useful definition
    2.1 of the paper linked above.
 *)
       
type 'char regexp =
  | Empty
  | Epsilon
  | Char of 'char
  | Concat of ('char regexp * 'char regexp)
  | Star of ('char regexp)
  | Or of ('char regexp * 'char regexp)
  | And of ('char regexp * 'char regexp)
  | Not of ('char regexp)


(** For example:
    - The constructor [Empty] denotes the RE 0 (which
      matches *no* strings). 
    - Likewise, the constructor [Epsilon] matches the empty string [""].
    - [Char c] matches the string containing just the character [c]
      (note that the type below is parameterized over the type of
      characters, ['char]).
    - [Concat(r1, r2)] matches strings of characters [s] that are
      splittable into two subtrings [s1] and [s2] such that [r1] matches
      [s1] and [r2] matches [s2].
    - [Or(r1, r2)] matches strings that are matched by either [r1] or [r2].
    - [And(r1, r2)] matches strings that are matched by both [r1] and [r2].
    - Finally, [Not r] matches strings that are *not* matched by [r].
  *)

(* EXERCISE 1: 

   Define a function, [regexp_to_string], that "pretty prints" regular
   expressions of type ['char regexp], by mapping each regular
   expression to a string. You may find the string concatenation
   operator (^) useful (recall that (^) has type [string -> string ->
   string]). 

   *** You are free to choose WHATEVER string representation of 
   REs you like, as long as each RE that's printed is easily identifiable
   from its string representation. *** 
   
   This is primarily for your own benefit; the [regexp_to_string]
   function will be used to pretty-print REs in a number of test cases
   below.

   Note that, since [regexp]s are parameterized by the type of
   characters they may contain ['char], your [regexp_to_string]
   function will be parameterized by a pretty-printing function for
   the ['char] type as well ([char_to_string : 'char -> string]).
   Use this function to display characters (type ['char])    
 *)

let rec regexp_to_string
(f : 'char -> string)(r : 'char regexp) : string = 
 match r with
 |Empty        -> ""
 |Epsilon      -> "'epsilon'"
 |Char x       -> f x
 |Concat(x, y) -> regexp_to_string (f) (x) ^ "." ^  regexp_to_string (f) (y)
 |Star x       -> "(" ^ regexp_to_string (f) (x) ^ ")*"
 |Or(x, y)     -> regexp_to_string (f) (x) ^ "|" ^  regexp_to_string (f) (y)
 |And(x, y)    -> regexp_to_string (f) (x) ^ "&" ^  regexp_to_string (f) (y)
 |Not x        -> "not("^regexp_to_string (f) (x) ^")"
;;


(* EXERCISE 2: 

   Define a function, [string_to_re], that encodes a string of 
   OCaml characters (type [char]) as a [char regexp], an RE 
   specialized to characters of type [char]. For example, 

     string_to_re "a" = Concat (Char 'a', Epsilon)
     string_to_re ""  = Epsilon
     string_to_re "ab"= Concat (Char 'a', Concat (Char 'b', Epsilon)
     ...

   While implementing this function, you may find the Batteries
   [BatString] library useful (the documentation for which is 
   available here:

 http://ocaml-batteries-team.github.io/batteries-included/hdoc2/BatString.html).

   In particular, note the function [to_list : string -> char list]. 
   To call this function in the current program, you can prefix it by 
   its library name, as in: [BatString.to_list]. The same applies to 
   any batteries library function: [<BatLibraryName>.<function_name>]. 

 *)
							       
let string_to_re (s : string) : char regexp =
  let lst = BatString.to_list s in 
  match lst with
  |[]    -> Epsilon 
  |x::lst' -> Concat(Char x, let rec con l : char regexp = 
              match l with 
              |[] -> Epsilon 
              |y::l'-> Concat(Char y,(con l')) in con lst');;

(* Some test inputs: *)  
string_to_re "a";; (* expected: Concat (Char 'a', Epsilon)*)
string_to_re "";;  (*expected: Epsilon *)
string_to_re "ab";;(*expected: Concat (Char 'a', Concat (Char 'b', Epsilon)*)

(** Recall from lecture that each RE denotes a *language*, i.e., a set
    of strings. Each string is a list of characters drawn from the 
    underlying alphabet, Sigma.

    In this assignment, we'll represent languages in OCaml as
    functions from strings to bools. That is, a language is a function
    that, for each possible string, returns true if that string is in
    the language and false otherwise.  
  *)
	

(* EXERCISE 3: 

   Define a function, [all_splits], that returns all possible
   "splittings" of an input character list [s]. 

   What do I mean by "splitting" here? Just a partition of the
   characters in [s] into two strings [s1] and [s2] such that [s1 ^ s2
   = s]. For example,

     - ("", "abc") is a splitting of the string "abc" because 
       "" ^ "abc" = "abc".

     - Likewise, ("abc", "def") is a splitting of "abcdef". 

     - ("abcdef", "") also splits "abcdef".

  When defining [all_splits], you may find useful functions: 
     - [BatList.length]
     - [BatList.takedrop].
  Both of these functions are described in the Batteries documentation
  for the [BatList] module:

http://ocaml-batteries-team.github.io/batteries-included/hdoc2/BatList.html.

 *)
let rev_list l =
  let rec rev_acc acc = function
    | [] -> acc
    | hd::tl -> rev_acc (hd::acc) tl
  in 
  rev_acc [] l
				      
let all_splits (s : 'char list) : ('char list * 'char list) list =
 let a = BatList.length s in
    let rec split (n: int)(lst : 'char list): ('char list * 'char list) list = 
      if n = 0 then
        [(BatList.takedrop n lst)]
      else
        (BatList.takedrop n lst)::(split (n-1) lst)
      in rev_list (split a s)
    ;;
      
          
 

  (* A test input: *)
all_splits [false; true];;
(*expected: [([], [false;true]); ([false], [true]); ([false;true], [])]*)

(* EXERCISE 4: 

   Define a function, [interp], that maps regular expressions of type
   ['char regexp] to the languages (of type ['char language]) that
   they recognize. 

   Your implementation of [interp] should be inspired quite closely by
   the mathematical definition of [interp] we discussed in class. You may
   also find useful the mathematical definition of the function L[[ . ]] 
   given in Section 2.1 of "Regular-expression derivatives reexamined".

   HINT: Be particularly careful in the [Star] case. The naive
   interpretation of [Star] (e.g., following "Regular-expression
   derivatives reexamined" Section 2.1 verbatim) will probably cause
   your interpretation function to infinite loop. Consider an
   alternative implementation (inspired perhaps by the second
   interpretation I showed in class :-)).

   Once you've finished a first draft of [interp], move on to EXERCISE
   5 to more thoroughly test your implementation.

 *)
type 'char language = 'char list -> bool

	
let rec interp (r : 'char regexp) : 'char language =
 match r with
 |Empty        -> fun (b:'char list) -> false
 |Epsilon      -> fun (b:'char list) -> [] = b
 |Char x       -> fun (b:'char list) -> [x] = b
 |Concat(x, y) -> fun (b:'char list) -> List.exists (fun ((w, v):(('a list * 'a list))) -> (interp x w) && (interp y v))(all_splits b)
 |Star x       -> fun (b:'char list) -> ([] = b) || (List.exists (fun ((w, v):(('a list * 'a list))) -> (interp x w) && (interp x v))(all_splits b))
 |Or(x, y)     -> fun (b:'char list) -> (((interp x) b) || ((interp y) b))
 |And(x, y)    -> fun (b:'char list) -> (((interp x) b) && ((interp y) b))
 |Not x        -> fun (b:'char list) -> (not ((interp x) b))
;;

let string_interp (r : char regexp) : string -> bool =
  fun s -> interp r (BatString.to_list s)

(* EXERCISE 5: 

   The test harness below provides a generic mechanism for testing an
   interpretation function, like your [interp] above, against a number
   of (regular expression, input string) pairs.  A few test cases are
   given for you. Add at least 10 more. 

   Don't be afraid to get creative! We'll award BONUS points if you
   come up with a test case that breaks our reference implementation.

 *)

type expectedResult = Pass | Fail
				     
let test1 (interp : char regexp -> string -> bool)
	  (e : expectedResult) (r : char regexp) (s : string) : unit =
  let char_to_string c = BatString.of_list [c] in
  let show_regexp r = regexp_to_string char_to_string r in
  let print_result msg =
    BatPrintf.printf "  %s: %s \"%s\"\n" msg (show_regexp r) s in
  let result = interp r s in
  match (result, e) with
  | (true, Pass) -> print_result "pass"
  | (false, Pass) -> print_result "*** FAILED"
  | (true, Fail) -> print_result "*** PASSED"
  | (false, Fail) -> print_result "fail"
		     
let test (testfun : expectedResult -> char regexp -> string -> 'a) : unit =
  let _ =
    BatList.map
      (fun (e,r,s) -> testfun e r s)
      [ (Fail, Empty, "abcde");
	(Fail, Epsilon, "abcde");
	(Pass, Epsilon, "");
	(Pass, string_to_re "a", "a");
	(Pass, string_to_re "abc", "abc");
        (Fail, Empty, "");
        (Fail, Epsilon, ("ba"));
        (Fail, Epsilon, "bbab");
        (Fail, string_to_re "(a&b)*", "a");
    	(Fail, string_to_re "a|b", "a");
        (Fail, Empty, "cbeasdfasd");
        (Pass, (Not (Or (Char 'a', Epsilon))),"booootttts");
        (Pass, (Concat (Char 'a', Char 'b')), "ab");
	(Fail, Concat(Char 'a', Char 'b'), "a");
       	(Fail, (And (Concat( Char 'a', Char 'b'), (Not (Char 'c')))), "abq");
        (Fail, Epsilon, "cattle");
         (Fail, (And (Concat(Char 'a', Char 'b'),(Or(Char 'c', Char 'e')))), "(abe lincoln)");
         (Fail,(Not (Star (Char 'a'))), "aaaaaaaa");
	 (Pass, (Concat(Char 'a', Char 'c')), "ac");
       	 (Fail, (And(Epsilon, (Not (Epsilon)))), "abc");
         (Fail, (And(Concat(Char 'a', Char 'b'), (Or(Char 'c', Char 'e')))), "epsilon");
         (Fail, (Concat (Epsilon, Epsilon)), "abbc");
         (Fail, (Not (Or (Char 'a', Epsilon))), "a");
	 (Fail, (Star (Or (Char 'a', Char 'b'))), "c");
       	 (Fail, (Or (Or (And (Char 'a', Char 'b'), Char 'c'), Char 'b')), "abc");
         (Fail, (Not (Epsilon)), "");
         (Fail, (Concat (Char 'q', Char 's')), "wxyz");

      ]
  in ();;
  
test (test1 string_interp);;  

(** ** Part II: Regular Expression Derivatives 

    In Part I, you defined an interpreter [interp] that mapped REs to
    the languages they represented. The interpreter was kind of dumb,
    in the sense that it followed the mathematical definition we gave
    in class quite closely, even when that caused a performance hit
    (hint: when interpreting [Concat(r1, r2)], your [interp] probably
    explored all possible "splittings" of the input string).

    In Part II, we'll use RE derivatives to implement a more efficient
    regular expression matcher. This part of the assignment follows 
    Sections 3.1 and 3.2 of "Regular-expression derivatives reexamined". 
*)

(* EXERCISE 6: 

   (Re-)read Section 3.1 of "Regular-expression derivatives reexamined". 

   Following the definition of the "nu" (greek letter nu) function 
   given in Section 3.1, define a function, called [nullable], that 
   returns [true] if a regexp [r] accepts the empty string and 
   [false] otherwise. 

 *)
  
let rec nullable (r : 'char regexp) : bool =
  match r with 
  |Empty         -> false
  |Char x        -> false
  |Epsilon       -> true
  |Concat(x, y)  -> nullable(x) && nullable(y)
  |Or(x, y)      -> nullable(x) || nullable(y)
  |Star x        -> true
  |And(x, y)     -> nullable(x) && nullable(y)
  |Not x         -> if nullable(x) = false then
                        true
                    else
                        false
;;

(* Some test inputs: *)  
nullable Epsilon;; (*expected: true*)
nullable Empty;; (*expected: false*)
nullable (Concat(Epsilon, Epsilon));; (*expected: true*)

(* EXERCISE 7:

   Following the definition of the "delta" function given in 
   Section 3.1, define a function [deriv] that returns the 
   derivative of a regular expression [r] with respect to any 
   given character [a : 'char]. For example,  

     deriv 'a' (Star (Char 'a')) = Concat (Epsilon, Star 'a')
                  
 *)
let check (a : 'char regexp) : 'char regexp =
   if nullable a then Epsilon else Empty;;
		  
let rec deriv (a : 'char) (r : 'char regexp) : 'char regexp =
  match r with 
  |Empty        -> Empty
  |Epsilon      -> Empty
  |Char x       -> if x != a then Empty else Epsilon 
  |Concat(x, y) -> Or((Concat((deriv a x), y)), (Concat((check x), (deriv a y))));
  |Star x       -> Concat((deriv a x), Star x)
  |Or(x, y)     -> Or((deriv a x), (deriv a y))
  |And(x, y)    -> And((deriv a x), (deriv a y))
  |Not x        -> Not (deriv a x)
;;				  

(* A test input: *)
deriv 'a' (Star (Char 'a'));; (*expected: Concat (Epsilon, Star 'a')*)

(* EXERCISE 8:

   Re-read Section 3.2 of "Regular-expression derivatives reexamined". 

   Following the definition of the "matches" relation "r ~ s" in
   Section 3.2, define a function [matches] that takes as arguments 
     - a regular expression [r : 'char regexp]
     - a string [s : 'char list] 
   and returns [true] if [r] matches [s] and [false] otherwise. 

   For example, 
   
     matches (Char a) [a] = true
     matches (Star (Char a)) [] = true
     matches (Or (Char a, Char b)) [] = false
     matches (Or (Char a, Char b)) [a; b] = false
     matches (Or (Char a, Char b)) [b] = true

 *)
			    
let rec matches (r : 'char regexp) (s : 'char list) : bool =
  match s with 
  |[]     -> if nullable(r)then true else false
  |s::l'  -> matches (deriv s r) l'
;;

(* Test inputs: *)
matches (Char 'a') ['a'];; (*expected: true*)
matches (Star (Char 'a')) [];; (*expected: true*)
matches (Or (Char 'a', Char 'b')) [];; (*expected: false*)
matches (Or (Char 'a', Char 'b')) ['a'; 'b'];; (*expected: false*)
matches (Or (Char 'a', Char 'b')) ['b'];; (*expected: true*)
				  

(* EXERCISE 9:

   Using [BatString.to_list], define a wrapper around [matches]
   that checks whether an RE [r : char regexp] (that is, specialized 
   to OCaml characters) matches an OCaml string [s]. 

 *)
		       
let string_matches (r : char regexp) : string -> bool =
 fun x -> matches r (BatString.to_list x)
;;		   

(*Some test inputs:*)
string_matches (Char 'a') "a";; (*expected output: true*)
string_matches (Star (Char 'a')) "";; (*expected output: true*)
string_matches (Star (Char 'a')) "aaa";; (*expected output: true*)
string_matches (Star (Char 'a')) "aba";; (*expected output: false*)          
  
test (test1 string_matches);;
