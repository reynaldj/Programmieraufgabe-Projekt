:- module(tseitin, [ tseitin/2 ]).
:- use_module(al_literals, [ al_lit/1 ]).
:- use_module(al_nf, [ al2menge/2 ]).


% Wir fuehren die Biimplikation als Operator ein, betrachten sie
% jedoch nicht als Junktor von AL
:- op(300, xfx, user:(<=>)).  % Biimplikation

% Die folgende Implementation des Tseitin-Verfahrens stammt von einem Studenten
% aus der Prolog-Übung des WS 15/16

% Gibt fuer jedes Literal das Literal selbst zurueck,
% und ansonsten ein neues Aussagensymbol
maybe_sym(L, L) :- al_lit(L), !.
maybe_sym(_, S) :- gensym(x, S).

% Hilfspraedikat


tseitin_step1(L, _, []) :- al_lit(L), !.


%% diese Zeile ist  für ~ ~ a
tseitin_step1(~ F, S, [ S <=> ~ FS | [FS <=> F ]]) :-
	al_lit(F),  ! ,gensym(x,FS).



tseitin_step1(~ F, S, [ S <=> ~ FS | T]) :-
	maybe_sym(F, FS),
	tseitin_step1(F, FS, T).

tseitin_step1(F /\ G, S, [ S <=> (FS /\ GS) | T ]) :- 
	maybe_sym(F, FS), 
	maybe_sym(G, GS),
	tseitin_step1(F, FS, FL),
	tseitin_step1(G, GS, GL),
	append(FL, GL, T).

tseitin_step1(F \/ G, S, [ S <=> (FS \/ GS) | T ]) :- 
	maybe_sym(F, FS), 
	maybe_sym(G, GS),
	tseitin_step1(F, FS, FL),
	tseitin_step1(G, GS, GL),
	append(FL, GL, T).

tseitin_step1(F => G, S, [ S <=> (FS => GS) | T ]) :- 
	maybe_sym(F, FS), 
	maybe_sym(G, GS),
	tseitin_step1(F, FS, FL),
	tseitin_step1(G, GS, GL),
	append(FL, GL, T).

% Implementiert das Tseitin-Verfahren
tseitin(F, [X| FL ]) :-
    maybe_sym(F, X),
    tseitin_step1(F, X, FL).


