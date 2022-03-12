:- module(dpll, [ dpll/1 ] ).
:- use_module(unit_propagation, [ unit_propagation/2 ]).
:- use_module(pure_literal, [ pure_literal/2 ]).
:- use_module(al_literals, [ negate_lit/2 ]).
:- use_module(al_nf, [ literal/2 ]).

% Vereinfachungsregeln auf Klauselmenge anwenden
simplify(KM, KM3) :-
    unit_propagation(KM, KM2),
    pure_literal(KM2, KM3).

% Implementation des DPLL-Algorithmus
dpll(KM) :-
    simplify(KM, KM2),
    dpll_cases(KM2).

% Abbruchbedingungen testen und rekursiver Aufruf vom DPLL-Algorithmus
% Klauselmenge ist erfüllbar, wenn sie leer ist
dpll_cases([]) :- !.
% Klauselmenge ist unerfüllbar, wenn sie eine leere Klausel enthält
dpll_cases(KM) :- member([], KM), !, fail.
% Ansonsten Literal wählen und rekursiver Aufruf
dpll_cases(KM) :-
    literal(L, KM), !,
    dpll_step(KM, L).

% Erweiterung der Klauselmenge um neue Einser-Klausel { L }
dpll_step(KM, L) :-
    dpll([ [ L ] | KM ]), !.
% ... bzw. nach Backtracking um { ~L } 
dpll_step(KM, L) :- 
    negate_lit(L, LN),
    dpll([ [ LN ] | KM ]).
