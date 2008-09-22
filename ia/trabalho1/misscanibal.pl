% Alexandre Y. Harano - RA: 254274
% Luiz Carlos Irber Jr. - RA: 254258
% Problema dos missionarios e canibais.

:- ensure_loaded(library(lists)).

/*****************************************************************************
   Definicoes dos predicados de impressao de resultados
******************************************************************************/

writeState(S) :- write(S).

% Imprime o caminho de solucao.
showPath(Path) :-
  Path=[First|_],
  last(Path,Last),
  nl, write('Uma solucao de '),
  showState(First),
  write(' para '),
  showState(Last),
  nl,
  forEachS(member(S,Path),(write(' '), showState(S), nl)).

% chama Action para cada caminho para provar P.
forEachS(P,Action) :- P, onceOnly(Action),fail.

forEachS(_,_).

% onceOnly(P) executa P somente uma vez.
onceOnly(P) :- call(P), !.

showState(S) :- writeState(S) -> true| write(S).


/*****************************************************************************
   Definicoes da busca cega
******************************************************************************/

% dfs -> depth first setransicaoh (busca em profundidade)
/*
 dfs/1: predicado chamado pelo usuario, passando como parametro qual das 
        tres possiveis combinações de caminhos ele deseja percorrer.
*/
/*
 dfs/2: predicado com um parametro dummy e um que contem a opcao de combinacao
        de escolha o usuario deseja percorrer.
*/
/*
 dfs/3: predicado com um parametro dummy, um que contem a opcao de combinacao
        de escolha o usuario deseja percorrer e outro que contem o caminho
        percorrido pelo trace da execucao.
*/
/*
 dfs/4: predicado com um parametro dummy, um que contem a opcao de combinacao
        de escolha o usuario deseja percorrer, outro que contem o estado atual
        e o ultimo que contem o caminho percorrido pelo trace da execucao.
*/
/*
 dfs/5: predicado com um parametro dummy, um que contem a opcao de combinacao
        de escolha o usuario deseja percorrer, outro que contem o estado atual,
        outro contem o caminho ate entao e outro que contera o caminho
        percorrido pelo trace da execucao.
*/

dfs(X) :- A is X mod 3,
          B is abs(A),
          dfs(dummy,B).

dfs(dummy,A) :- dfs(dummy,A,Path), showPath(Path).

dfs(dummy,A,Path) :- inicial(S), dfs(dummy,A,S,Path).

dfs(dummy,A,S,Path) :-
    dfs(dummy,A,S,[S],ThePath),
    reverse(ThePath,Path).

dfs(dummy,A,S,SoFar,Path) :-
    possibilidade(A,P),
    transicao(S,S2,P,dummy),
    \+(member(S2,SoFar)),
      % impede a formacao de ciclo verificando se ja foi passado pelo estado S2
    dfs(dummy,A,S2,[S2|SoFar], Path).
dfs(dummy,_,S,Path,Path) :- objetivo(S).

% As tres possibilidades de verificacao de transicoes possiveis.
possibilidade(0,[1,2,3,4,5,6,7,8,9,10]).
possibilidade(1,[10,9,8,7,6,5,4,3,2,1]).
possibilidade(2,[1,7,5,3,9,2,8,6,4,10]).

/*****************************************************************************
   Definicoes do problema
******************************************************************************/

/*
   Representacao do estados -> [ME, CE, MD, CD, B], onde:
     ME - Missionarios na esquerda.
     CE - Canibais na esquerda.
     MD - Missionarios na direita.
     CE - Canibais na direita.
     B  - Posicao do btransicaoo.
*/

/*
 transicao/4: 1o. parametro: estado atual,
        2o. parametro: proximo estado,
        3o. parametro: lista com ordem de analise,
        4o. parametro: dummy
*/
/*
 transicao/3: 1o. parametro: estado atual,
        2o. parametro: proximo estado,
        3o. parametro: numeracao da analise
*/

transicao(S,S2,[Head|Rest],dummy) :- 
                          transicao(S,S2,Head);
                          transicao(S,S2,Rest,dummy).

transicao([ME,CE,MD,CD,esquerda], [ME2,CE2,MD2,CD2,direita], 1):-
    % dois canibais deslocam para a direita
    CD2 is CD+2,
    CE2 is CE-2,
    MD2 is MD,
    ME2 is ME,
    estadoLegal([ME2,CE2,MD2,CD2,direita]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,direita], [ME2,CE2,MD2,CD2,esquerda], 2):-
    % um canibal desloca para a esquerda
    CD2 is CD-1,
    CE2 is CE+1,
    ME2 is ME,
    MD2 is MD,
    estadoLegal([ME2,CE2,MD2,CD2,esquerda]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,esquerda], [ME2,CE2,MD2,CD2,direita], 3):-
    % dois missionarios deslocam para a direita
    MD2 is MD+2,
    ME2 is ME-2,
    CE2 is CE,
    CD2 is CD,
    estadoLegal([ME2,CE2,MD2,CD2,direita]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,direita], [ME2,CE2,MD2,CD2,esquerda], 4):-
    % um missionario e um canibal deslocam para a esquerda
    MD2 is MD-1,
    ME2 is ME+1,
    CD2 is CD-1,
    CE2 is CE+1,
    estadoLegal([ME2,CE2,MD2,CD2,esquerda]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

% Definicao do conjunto de transicoes validos.
transicao([ME,CE,MD,CD,esquerda], [ME2,CE2,MD2,CD2,direita], 5):-
    % um missionario e um canibal deslocam para a direita
    MD2 is MD+1,
    ME2 is ME-1,
    CD2 is CD+1,
    CE2 is CE-1,
    estadoLegal([ME2,CE2,MD2,CD2,direita]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,direita], [ME2,CE2,MD2,CD2,esquerda], 6):-
    % um missionario desloca para a esquerda
    MD2 is MD-1,
    ME2 is ME+1,
    CD2 is CD,
    CE2 is CE,
    estadoLegal([ME2,CE2,MD2,CD2,esquerda]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,esquerda], [ME2,CE2,MD2,CD2,direita], 7):-
    % um canibal desloca para a direita
    CD2 is CD+1,
    CE2 is CE-1,
    ME2 is ME,
    MD2 is MD,
    estadoLegal([ME2,CE2,MD2,CD2,direita]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,direita], [ME2,CE2,MD2,CD2,esquerda], 8):-
    % dois canibais deslocam para a esquerda
    CD2 is CD-2,
    CE2 is CE+2,
    MD2 is MD,
    ME2 is ME,
    estadoLegal([ME2,CE2,MD2,CD2,esquerda]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,esquerda], [ME2,CE2,MD2,CD2,direita], 9):-
    % um missionario desloca para a direita
    MD2 is MD+1,
    ME2 is ME-1,
    CD2 is CD,
    CE2 is CE,
    estadoLegal([ME2,CE2,MD2,CD2,direita]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

transicao([ME,CE,MD,CD,direita], [ME2,CE2,MD2,CD2,esquerda], 10):-
    % dois missionarios deslocam para a esquerda
    MD2 is MD-2,
    ME2 is ME+2,
    CD2 is CD,
    CE2 is CE,
    estadoLegal([ME2,CE2,MD2,CD2,esquerda]),
    viagemLegal([ME,CE,MD,CD],[ME2,CE2,MD2,CD2]).

% Verificacao: o estado eh valido?
estadoLegal(S) :-
    ultimoEstado(S);
    outroEstado(S).

ultimoEstado(S) :-
    objetivo(S).

outroEstado(S) :-
    \+(objetivo(S)),
    S = [ME|L1],
    L1 = [CE|L2],
    L2 = [MD|L3],
    L3 = [CD|_],
    ME>=0,
    CE>=0,
    MD>=0,
    CD>=0,
    3 is ME+MD,
     % o numero de missionarios eh igual a 3 em qualquer estado
    3 is CD+CE,
     % o numero de canibais eh igual a 3 em qualquer estado
    verificaMissionariosCanibais(ME,CE),
    verificaMissionariosCanibais(MD,CD).

%Verificacao: missionarios >= canibais ou missionarios = 0?     
verificaMissionariosCanibais(M,C) :-
    M is 0;
    M >= C.

% Verificacao: a viagem eh valida?
viagemLegal([ME,CE,MD,CD], [ME2, CE2, MD2, CD2]) :-

    abs(ME-ME2) =:= abs(MD2-MD),
      % a variacao do numero de missionarios de um lado eh igual ao do outro lado
    abs(CE-CE2) =:= abs(CD2-CD),
      % a variacao do numero de canibais de um lado eh igual ao do outro lado
    abs(ME-ME2)+abs(CE-CE2) =:= 1;
      % o barco leva uma pessoa ou
    abs(ME-ME2)+abs(CE-CE2) =:= 2.
      % o barco leva duas pessoa

% Estado inicial e estado objetivo
inicial([3,3,0,0,esquerda]).
objetivo([0,0,3,3,direita]).