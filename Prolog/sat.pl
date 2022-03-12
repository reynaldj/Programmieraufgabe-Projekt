:- use_module(tseitin).
:- use_module(dpll).
:- use_module(al_def).
:- use_module(al_literals).
:- use_module(al_nf).

:- op(300, xfx, user:(<=>)).

sat(F) :- tseitinstep2(F,KM),!,dpll(KM).
tseitinstep2(F,KM) :- tseitin(F,L), convert(L,KM).
convert([H|T],[X|T1]) :- X=[H], convertthen(T,T1).

convertthen([ X <=> Y \/ Z | T], [[~ X,Y,Z], [X,X1] , [X,X2] | T1]) :- Y= ~ X1, Z= ~ X2,!,convertthen(T,T1).
convertthen([ X <=> Y \/ Z | T], [[~ X,Y,Z], [X,X1] , [X,~ Z] | T1]) :- Y= ~ X1,!,convertthen(T,T1).
convertthen([ X <=> Y \/ Z | T], [[~ X,Y,Z], [X,~ Y] , [X,X2] | T1]) :- Z= ~ X2,!,convertthen(T,T1).
convertthen([ X <=> Y \/ Z | T], [[~ X,Y,Z], [X,~ Y] , [X,~ Z] | T1]) :- convertthen(T,T1).

convertthen([ X <=> Y /\ Z | T], [[~ X,Y], [~ X,Z] , [X1, X2, X] | T1]) :- Y= ~ X1, Z= ~ X2,!, convertthen(T,T1).
convertthen([ X <=> Y /\ Z | T], [[~ X,Y], [~ X,Z] , [X1, ~ Z, X] | T1]) :- Y= ~ X1,!,convertthen(T,T1).
convertthen([ X <=> Y /\ Z | T], [[~ X,Y], [~ X,Z] , [~ Y, X2, X] | T1]) :- Z= ~ X2,!,convertthen(T,T1).
convertthen([ X <=> Y /\ Z | T], [[~ X,Y], [~ X,Z] , [~ Y, ~ Z, X] | T1]) :- convertthen(T,T1).

convertthen([ X <=> (Y => Z) | T], [[~ X,X1,Z], [Y,X] , [X2,X] | T1]) :- Y= ~ X1, Z= ~ X2,!,convertthen(T,T1). 
convertthen([ X <=> (Y => Z) | T], [[~ X,X1,Z], [Y,X] , [~ Z,X] | T1]) :- Y= ~ X1,!,convertthen(T,T1).
convertthen([ X <=> (Y => Z) | T], [[~ X,~ Y,Z], [Y,X] , [X2,X] | T1]) :- Z= ~ X2,!,convertthen(T,T1).
convertthen([ X <=> (Y => Z) | T], [[~ X,~ Y,Z], [Y,X] , [~ Z,X] | T1]) :- convertthen(T,T1). 

convertthen([ X <=> ~ Y | T], [[~X,~ Y], [X,Y]| T1]) :- convertthen(T,T1).

convertthen([],[]). 

%fuer KNF, die im DIMACS-Format geschrieben sind, kann man sat_dimacs(File) aufrufen, um die Erfüllbarkeit zu prüfen

sat_dimacs(File):-
         open(File,read,Str),
         read_dimac(Str,Dimac),
         close(Str),
	 
         dimacs_parse(Dimac,KM),
	 dpll(KM).
   
read_dimac(Stream, []) :-
	at_end_of_stream(Stream),!.

read_dimac(Stream,[Char|Chars]):-
        get_code(Stream,Code),
	char_code(Char, Code),
	read_dimac(Stream,Chars).

dimacs_parse(W,KM) :- dimacs_getcnf(KM,W,[]).

dimacs_getcnf(KM) -->	
		dimacs_skip2,
		dimacs_clauses(KM).
		dimacs_skips.

dimacs_skip --> [' '].
dimacs_skip --> ['\n'].
dimacs_skip --> ['\t'].
dimacs_skip --> [c, '\n'].
dimacs_skip --> [c, ' '], dimacs_comment.
dimacs_comment --> [X], {X \= '\n'},!, dimacs_comment.
dimacs_comment --> [].
dimacs_skips --> dimacs_skip,!,dimacs_skips.
dimacs_skips --> [].

dimacs_skip2 --> dimacs_skips, [p], dimacs_skips, [c,n,f], dimacs_skips, dimacs_digits, dimacs_skips, dimacs_digits.
dimacs_digits --> [X], {char_code(X,C), C >= 48, C =< 57},!, dimacs_digits.
dimacs_digits --> [].

dimacs_clauses([X|Xs]) -->	
			dimacs_clause(X), !, dimacs_clauses(Xs).
dimacs_clauses([]) --> [].

dimacs_clause([]) --> dimacs_skips, ['0'].
dimacs_clause([X|Xs]) --> 
	dimacs_skips,
	dimacs_literal(X),!,
	dimacs_clause(Xs).

dimacs_literal(~Z) --> [-],dimacs_cnf_natural(L),{name('x',[X]),name(L,Y),name(Z,[X|Y])},!.
dimacs_literal(Z) --> dimacs_cnf_natural(L),{name('x',[X]),name(L,Y),name(Z,[X|Y])}, !.

dimacs_cnf_natural(N) --> dimacs_cnf_digits(Xs), {Xs \= [], number_chars(N, Xs)}.

dimacs_cnf_digits([X|Xs]) --> [X], {char_code(X, C), C >= 48, C =< 57}, !, dimacs_cnf_digits(Xs).
dimacs_cnf_digits([]) --> [].

