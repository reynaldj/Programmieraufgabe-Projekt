:- module(al_nf, [ al_nnf/1,
		   al2nnf/2,
		   al_dklausel/1,
		   al_knf/1,
		   al2knf/2,
		   al2menge/2,
		   literal/2
		 ]).

:- use_module(al_def, [ as/1 ]).
:- use_module(al_literals).

% Testet, ob aussagenlogische Formel in Negationsnormalform ist
al_nnf(F) :- al_lit(F).
al_nnf(F /\ G) :- al_nnf(F), al_nnf(G).
al_nnf(F \/ G) :- al_nnf(F), al_nnf(G).

% Konstruiert zu einer gegebenen aussagenlogischen Formel eine äquivalente Negationsnormalform

al2nnf(F, FN) :- al2nnf(F, FN, _).

% Hilfsprädikat
al2nnf(0,0,1).
al2nnf(1,1,0).
al2nnf(X, X, ~ X) :- as(X).
al2nnf(~ X, ~ X, X) :- as(X), !.
al2nnf(~ F, G, H) :- al2nnf(F, H, G).
al2nnf(F1 /\ F2, G1 /\ G2, H1 \/ H2) :-
    al2nnf(F1,G1,H1), al2nnf(F2,G2,H2).
al2nnf(F1 \/ F2, G1 \/ G2, H1 /\ H2) :-
    al2nnf(F1,G1,H1), al2nnf(F2,G2,H2).
al2nnf(F1 => F2, H1 \/ G2, G1 /\ H2) :-
    al2nnf(F1,G1,H1), al2nnf(F2,G2,H2).

% Testet, ob aussagenlogische Formel disjunktive Klausel ist
al_dklausel(F) :- al_lit(F).
al_dklausel(F \/ G) :- al_dklausel(F), al_dklausel(G).

% Testet, ob aussagenlogische Formel KNF ist
al_knf(F) :- al_dklausel(F).
al_knf(F /\ G) :- al_knf(F), al_knf(G).

% Konstruiert zu einer Negationsnormalform eine äquivalente Formel in KNF
nnf2knf(D, D) :- al_dklausel(D), !.
nnf2knf(A1 /\ A2, B1 /\ B2) :-
    nnf2knf(A1, B1), nnf2knf(A2, B2).
nnf2knf(A1 \/ A2, C) :-
    nnf2knf(A1, B1), nnf2knf(A2, B2), distribute(B1 \/ B2, C).

% Hilfsprädikat
distribute(B1 \/ B2, B1 \/ B2) :-
    al_dklausel(B1), al_dklausel(B2), !.
distribute((A1 /\ A2) \/ B, C1 /\ C2) :- !,
    distribute(A1 \/ B, C1), distribute(A2 \/ B, C2).
distribute(A \/ (B1 /\ B2), C1 /\ C2) :-
    distribute(A \/ B1, C1), distribute(A \/ B2, C2). 

% Konstruiert zu einer aussagenlogischen Formel eine äquivalente Formel in KNF

al2knf(F, K) :-
    al2nnf(F, N),
    nnf2knf(N, K).


% Konstruiere zu disjunktiver Klausel eine äquivalente Menge von Literalen
dklausel2menge(L, [ L ]) :- al_lit(L).
dklausel2menge(F \/ G, X) :-
    dklausel2menge(F, FX), dklausel2menge(G, GX), append(FX, GX, X).

% Konstruiere zu KNF eine äquivalente Menge von Literalen
knf2menge(F /\ G, X) :-
    !, knf2menge(F, FX), knf2menge(G, GX), append(FX, GX, X).
knf2menge(F, [ X ]) :-
    dklausel2menge(F, X).

% Konstruiere zu aussagenlogischer Formel eine äquivalente Menge disjunktiver
% Klauseln

al2menge(F, X) :-
    al2knf(F, K), knf2menge(K, X).


% Ist für jedes Literal einer Klauselmenge erfüllt
literal(L, KM) :- member(K, KM), member(L, K).
