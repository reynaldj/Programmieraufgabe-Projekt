:- module(al_def,
	  [ bool/1,
	    as/1,
	    al/1
	  ]).

% Das Modul al_def exportiert die Operatoren der Aussagenlogik sowie Prädikate um
% boolesche Konstanten, Aussagensymbole und aussagenlogische Formeln zu erkennen

% Das Präfix user: sorgt dafür, dass die hier definierten Operatoren
% auch ausserhalb des Moduls verfügbar sind. Um genau zu sein, werden
% die entsprechenden Operatoren des sogenannten "user"-Moduls überschrieben.
:- op(100, fy, user:(~)).     % Negation
:- op(200, xfx, user:(/\)).   % Konjunktion
:- op(200, xfx, user:(\/)).   % Disjunktion
:- op(300, xfx, user:(=>)).   % Implikation

% boolesche Konstanten 0 und 1
bool(0).
bool(1).

% Aussagensymbole werden durc Atome repräsentiert
as(X) :- atom(X).

% al(X) besagt: X repräsentiert eine aussagenlogische Formel

%  Die booleschen Konstanten sind aussagenlogische Formeln.
al(B) :- bool(B).

%  Jedes Aussagensymbol ist eine aussagenlogische Formel.
al(X) :- as(X).

%  Die Negation einer aussagenlogischen Formel ist auch eine aussagenlogische Formel
al(~ F) :- al(F).

%  Konjunktion, Disjunktion und Implikation von zwei aussagenlogischen Formeln sind auch aussagenlogische Formeln
al(F1 /\ F2) :- al(F1), al(F2).
al(F1 \/ F2) :- al(F1), al(F2).
al(F1 => F2) :- al(F1), al(F2).
