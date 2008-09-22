% Funcionou no SWI-Prolog v. 5.6.45.
% 
% Alexandre Y. Harano   - RA: 254274
% Luiz Carlos Irber Jr. - RA: 254258
% Problema do homem do saco (knapsack problem).
% 

:- ensure_loaded(library(lists)).

/*****************************************************************************
   Predicados auxiliares
******************************************************************************/

remove([], _, []) :- !.

remove([H|T], El, List) :-
        \+ El\=H,
        !,
        remove(T, El, List).

remove([H|T], El, [H|List]) :- remove(T, El, List).

contador([], Numero) :- Numero is 0, !.

contador([_|Cauda], Numero) :- contador(Cauda, N), Numero is N + 1.

somaPeso([], Peso) :- Peso is 0, !.

somaPeso([Item|Cauda], Peso) :- somaPeso(Cauda, P), peso(Item, Pitem),
                                Peso is P + Pitem.

somaValor([], Valor) :- Valor is 0, !.

somaValor([Item|Cauda], Valor) :- somaValor(Cauda, V), valor(Item, Vitem),
                                  Valor is V + Vitem.

/*****************************************************************************
   Definicoes dos predicados de impressao de resultados
******************************************************************************/

mostraTrajetoria(SacoInicial,Saco,Acoes) :-
      contador(Acoes,Numero), mostraTrajetoria(SacoInicial,Saco,Acoes,Numero).

mostraTrajetoria(SacoInicial,Saco,_,0) :-
      write('Nao foi realizado nenhuma acao entre '), write(SacoInicial),
      write(' e '), write(Saco), write(' pois o esforco foi 0.'), nl.

mostraTrajetoria(SacoInicial,Saco,Acoes,Numero) :- \+(Numero is 0),
      nl, write('Uma solucao de '), write(SacoInicial), write(' para '),
      write(Saco), write(' com esforco '), write(Numero), write(', valor '),
      somaValor(Saco,Valor), write(Valor), write(' e peso '),
      somaPeso(Saco,Peso), write(Peso), write(':'), nl,
      paraCadaAcao( member(A,Acoes), (write(' '),mostraAcao(A),nl) ).

paraCadaAcao(VerificaAcao, Imprime) :-
      VerificaAcao, somenteUmaVez(Imprime), fail.
paraCadaAcao(_,_).

somenteUmaVez(X) :- call(X), !.
mostraAcao(Acao) :- imprimeAcao(Acao) -> true| write(Acao).
imprimeAcao(Acao) :- write(Acao).

/*****************************************************************************
   Definicoes das heuristicas
******************************************************************************/

%bt2 -> busca tipo 2 (pattern-directed search)
/*
 bt2/1: predicado chamado pelo usuario, passando como parametro qual das 
        duas heuristicas utilizadas ele deseja utilizar.
 bt2/2: predicado com um parametro de peso maximo do saco e um que contem
        a opcao de heuristica que o usuario deseja utilizar.
 bt2/7: predicado com um parametro de peso maximo do saco, um que contem
        a opcao de heuristica que o usuaria deseja utilizar, um que contem
        o estado atual do saco, um que contem a trajetoria de acoes percorrida,
        o saco final, as acoes finais e os itens restantes.
*/

bt2(X) :- A is X mod 2,
          B is abs(A),
          bt2(15,B).

bt2(PesoMaximo,X) :- inicial(SacoI,AcoesI,ItensI),
                     bt2(PesoMaximo,X,SacoI,AcoesI,Saco,AcoesR,ItensI),
                     reverse(AcoesR,Acoes),
                     mostraTrajetoria(SacoI,Saco,Acoes).

bt2(PesoMaximo,X,SacoAtual,AcoesAtuais,Saco,Acoes,ItensRestantes) :-
      \+objetivo(PesoMaximo,SacoAtual),
      \+(ItensRestantes = []),
      avaliacao(PesoMaximo,X,ItensRestantes,I,AcoesAtuais,A,SacoAtual,S),
      bt2(PesoMaximo,X,S,A,Saco,Acoes,I), !.

% Checa se o peso do saco e o peso maximo sao iguais.
bt2(PesoMaximo,_,Saco,AcoesAntigo,Saco,Acoes,_) :- objetivo(PesoMaximo,Saco),
      Acoes = ['saco atingiu o limite de peso!'|AcoesAntigo], !.

% Tambem chega ao objetivo se todos os itens ja foram verificados.
bt2(_,_,Saco,AcoesAntigo,Saco,Acoes,[]) :-
      Acoes = ['nao ha mais itens a serem avaliados!'|AcoesAntigo], !.

/*****************************************************************************
   Definicoes do problema
*****************************************************************************/

/*
   Representacao do estados -> o estado como fazemos uso na notacao de aula eh
                               uma lista que contem os itens do saco. Todas as
                               informacoes relacionadas a peso e valor podem
                               ser computadas atraves de uma somatoria dos
                               itens contidos na lista, sendo tais somatorios
                               definidos na secao de predicados auxiliares.
*/

% Funcao de avaliacao de H1.
avaliacao(PesoMaximo,1,ItAntigo,ItNovo,AcAntigo,AcNovo,SacoAntigo,SacoNovo)
:- buscaItemMaisValioso(ItAntigo,Item,AcAntigo,Ac), remove(ItAntigo,Item,I),
   string_concat('avalia ',Item,Acao), A = [Acao|Ac],
   verificaSacoItem(PesoMaximo,Item,I,ItNovo,A,AcNovo,SacoAntigo,SacoNovo).

% Funcao de avaliacao de H2.
avaliacao(PesoMaximo,0,ItAntigo,ItNovo,AcAntigo,AcNovo,SacoAntigo,SacoNovo)
:- buscaItemMaiorDensidade(ItAntigo,Item,AcAntigo,Ac), remove(ItAntigo,Item,I),
   string_concat('avalia ',Item,Acao), A = [Acao|Ac],
   verificaSacoItem(PesoMaximo,Item,I,ItNovo,A,AcNovo,SacoAntigo,SacoNovo).

% Predicado de verificacao de insercao de item
verificaSacoItem(PesoMax,Item,ItAntigo,ItNovo,AcAntigo,AcNovo,SAntigo,SNovo)
:- somaPeso(SAntigo,PesoSaco), peso(Item,P),
   (
     (
       PesoMax >= (PesoSaco + P),
       insercao(Item,ItAntigo,ItNovo,AcAntigo,AcNovo,SAntigo,SNovo), !
     ) ;
     (
       (PesoSaco + P) > PesoMax,
       (
         P > PesoMax, ItNovo = ItAntigo, AcNovo = AcAntigo,
         SNovo = SAntigo, !
       ) ;
       (
         PesoMax > P, buscaItemMenosValioso(SAntigo,Menos,AcAntigo,AMenos),
         valor(Menos,ValorMenos), valor(Item,ValorItem),
         peso(Menos,PesoMenos), peso(Item,PesoItem),
         somaPeso(SAntigo,PesoSaco),
         (
           (
             ValorMenos > ValorItem, ItNovo = ItAntigo, AcNovo = AMenos,
             SNovo = SAntigo, !
           ) ;
           (
             ValorItem > ValorMenos,
             (
               PesoMax >= (PesoItem+PesoSaco-PesoMenos),
               remocao(Menos,ItAntigo,I,AMenos,A,SAntigo,S),
               insercao(Item,I,ItNovo,A,AcNovo,S,SNovo), !
             ) ;
             (
               (PesoItem+PesoSaco-PesoMenos) > PesoMax,
               ItNovo = ItAntigo, AcNovo = AMenos,
               SNovo = SAntigo, !
             )
           ) ;
           (
             ValorMenos =:= ValorItem,
             (
               PesoMenos > PesoItem,
               remocao(Menos,ItAntigo,I,AMenos,A,SAntigo,S),
               insercao(Item,I,ItNovo,A,AcNovo,S,SNovo), !
             ) ;
             (
               PesoItem >= PesoMenos, ItNovo = ItAntigo,
               AcNovo = AMenos, SNovo = SAntigo, !
             )
           )
         )
       )
     )
   ).

% Predicado de busca de item em H1.

buscaItemMaisValioso(ItAntigo,Item,AcAntigo,AcNovo) :-
      buscaItemMaisValioso(_,ItAntigo,Item),
      itensRestantes(ItAntigo,Str),
      string_concat('busca o item com o maior valor entre [',
        Str,LB),
      string_concat(LB,']',A), AcNovo = [A|AcAntigo].

buscaItemMaisValioso(0,[],_) :- !.

buscaItemMaisValioso(MaiorValorAtual,ItensRestantes,Item) :-
     ItensRestantes = [ItemAtual|I],
     buscaItemMaisValioso(ValorEncontrado,I,ItemEncontrado),
     valor(ItemAtual,ValorAtual),
     (
       (
         ValorAtual > ValorEncontrado, Item = ItemAtual,
         MaiorValorAtual = ValorAtual, !
       ) ;
       (
         ValorEncontrado >= ValorAtual, Item = ItemEncontrado,
         MaiorValorAtual = ValorEncontrado, !
       )
     ).

% Predicado de busca de item em H2.

buscaItemMaiorDensidade(ItAntigo,Item,AcAntigo,AcNovo) :-
      buscaItemMaiorDensidade(_,ItAntigo,Item),
      itensRestantes(ItAntigo,Str),
      string_concat('busca o item com a maior relacao valor por peso entre [',
        Str,LB),
      string_concat(LB,']',A), AcNovo = [A|AcAntigo].

buscaItemMaiorDensidade(0,[],_) :- !.

buscaItemMaiorDensidade(MaiorDensidade,ItensRestantes,Item) :-
      ItensRestantes = [ItemAtual|I],
      buscaItemMaiorDensidade(DensidadeEncontrada,I,ItemEncontrado),
      densidadeMonetaria(ItemAtual, DensidadeAtual),
     (
       (
         DensidadeAtual > DensidadeEncontrada, Item = ItemAtual,
         MaiorDensidade = DensidadeAtual, !
       ) ;
       (
         DensidadeEncontrada >= DensidadeAtual, Item = ItemEncontrado,
         MaiorDensidade = DensidadeEncontrada, !
       )
     ).

% Predicado para substituicao de item
buscaItemMenosValioso(Saco,Item,AcAntiga,AcNova) :- buscaItemMenosValioso(_,Saco,Item),
      AcNova = ['busca item de menor valor entre os itens do saco!'|AcAntiga].

buscaItemMenosValioso(V,[],invalido) :- valor(invalido,V).

buscaItemMenosValioso(MenorValorAtual,ItensRestantes,Item) :-
     ItensRestantes = [ItemAtual|I],
     buscaItemMenosValioso(ValorEncontrado,I,ItemEncontrado),
     valor(ItemAtual,ValorAtual),
     (
       (
         ValorEncontrado > ValorAtual, Item = ItemAtual,
         MenorValorAtual = ValorAtual, !
       ) ;
       (
         ValorAtual > ValorEncontrado, Item = ItemEncontrado,
         MenorValorAtual = ValorEncontrado, !
       ) ;
       (
         ValorAtual =:= ValorEncontrado, MenorValorAtual = ValorAtual,
         peso(ItemAtual,PesoAtual), peso(ItemEncontrado,PesoEncontrado),
         (
           (
             PesoAtual >= PesoEncontrado, Item = ItemAtual, !
           ) ;
           (
             PesoEncontrado > PesoAtual, Item = ItemEncontrado, !
           )
         )
       )
     ).      
   

% Predicado de insercao de item.
insercao(Item,ItensAntigo,ItensNovo,AcoesAntigo,AcoesNovo,SacoAntigo,SacoNovo)
:-    SacoNovo = [Item|SacoAntigo], string_concat('insere ',Item,Acao),
      AcoesNovo = [Acao|AcoesAntigo], ItensNovo = ItensAntigo.

% Predicado de remocao de item.
remocao(Item,ItensAntigo,ItensNovo,AcoesAntigo,AcoesNovo,SacoAntigo,SacoNovo)
:-    remove(SacoAntigo,Item,SacoNovo), string_concat('remove ',Item,Acao),
      AcoesNovo = [Acao|AcoesAntigo], ItensNovo = [Item|ItensAntigo].

% Predicado que imprime os itens restantes.
itensRestantes(Saco,I) :- itensRestantes(_,Saco,I).

itensRestantes(dummy,ListaRestante,I) :- \+(ListaRestante = []),
                                   ListaRestante = [Item|Resto],
                                   itensRestantes(_,Resto,Str),
                                   (
                                     (
                                       \+(Str = ''), string_concat(',',Str,X),
                                       string_concat(Item,X,I), !
                                     );
                                     (
                                       Str = '', I = Item, !
                                     )
                                   ).

itensRestantes(dummy,[],I) :- I = ''.

% Itens a serem avaliados.
itens(I) :- verificaItens(I).

verificaItens(I) :- verificaItens([],I).

verificaItens(Lista,ListaFinal) :- peso(I,_), valor(I,_), \+member(I,Lista),
                                   \+(I = 'invalido'),
                                   verificaItens([I|Lista], ListaFinal), !.

verificaItens(Lista,ListaFinal) :- remove(Lista,invalido,ListaFinal), !.

% Dados dos itens
peso(ventilador,P) :- P is 2.
peso(computador,P) :- P is 8.
peso(microondas,P) :- P is 18.
peso(televisor,P) :- P is 8.
peso(videogame,P) :- P is 4.
peso(videocassete,P) :- P is 3.
peso(telefone,P) :- P is 1.
peso(guitarra,P) :- P is 5.
peso(dicionario,P) :- P is 7.
peso(autorama,P) :- P is 6.
peso(theArtOfProgramming,P) :- P is 4.
peso(ouro,P) :- P is 4.
peso(teclado,P) :- P is 12.
peso(invalido,P) :- P is 0.

valor(ventilador,V) :- V is 40.
valor(computador,V) :- V is 1500.
valor(microondas,V) :- V is 150.
valor(televisor,V) :- V is 450.
valor(videogame,V) :- V is 900.
valor(videocassete,V) :- V is 100.
valor(telefone,V) :- V is 50.
valor(guitarra,V) :- V is 550.
valor(dicionario,V) :- V is 300.
valor(autorama,V) :- V is 800.
valor(theArtOfProgramming,V) :- V is 1337.
valor(ouro,V) :- V is 6200.
valor(teclado,V) :- V is 2500.
valor(invalido,V) :- V is 9999999999999999999999999999999999999999999999999999999999999.

densidadeMonetaria(I,Densidade) :- valor(I,V), peso(I,P), Densidade = V/P.

% Estado inicial
inicial([],[], I) :- itens(I).

% Verificacao de objetivo
objetivo(PesoMaximo,Saco) :- somaPeso(Saco,PesoMaximo).
