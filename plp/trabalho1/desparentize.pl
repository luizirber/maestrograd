// Funciona       

flatten(X, Y) :- flatpair(X, Y-[]).

flatpair([], L-L).

flatpair([H|T], L1-L3) :-

    flatpair(H, L1-L2), flatpair(T, L2-L3).

flatpair(X, [X|Z]-Z).

// Funciona também

desparentize([], []).

desparentize([H|T], L3) :-

      desparentize(H, L1), desparentize(T, L2), append(L1, L2, L3).

desparentize(X, [X]).

// implementação do swi-prolog
flatten(List, FlatList) :-
	flatten(List, [], FlatList0), !,
	FlatList = FlatList0.

flatten(Var, Tl, [Var|Tl]) :-
	var(Var), !.
flatten([], Tl, Tl) :- !.
flatten([Hd|Tl], Tail, List) :-
	flatten(Hd, FlatHeadTail, List), 
	flatten(Tl, Tail, FlatHeadTail).
flatten(Atom, Tl, [Atom|Tl]).
