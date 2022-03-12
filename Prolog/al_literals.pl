:- module(al_literals, [ al_lit/1, negate_lit/2 ]).

:- use_module(al_def, [ as/1 ]).

% Das Modul al_literals exportiert ein Prädikat al_lit/1
% um aussagenlogische Literale zu erkennen, und ein
% Prädikat negate_lit/2, um Literale zu negieren

al_lit(S) :- as(S).
al_lit(~ S) :- as(S).

negate_lit(S, ~ S) :- as(S).
negate_lit(~ S, S) :- as(S).
