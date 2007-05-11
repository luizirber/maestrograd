#ifndef TAD_H
#define TAD_H
#include <cassert>

class conteiner {
  public:
    conteiner();
    void entra(int);
    int sai();
    bool vazia();
  private:
    struct node;
    typedef node * nodeptr;
    struct node {
      int custo;
      nodeptr next;
    };
    nodeptr inicio;
    nodeptr fim;
    void posiciona(int,nodeptr,nodeptr,nodeptr);
};

conteiner::conteiner()
{
  //inicia ponteiros como null
  fim=0;
  inicio=0;
}

void conteiner::entra(int t)
{
  // cria novo node e o coloca no fim da fila
  nodeptr n(new node);
  assert(n);
  nodeptr aux(new node); // node auxiliar, realiza a busca
  assert(aux);
  nodeptr ant(new node); // node auxiliar, node n sera inserido apos esse
  assert(ant);
  n->next = 0;
  n->custo = t;
  posiciona(t,inicio,ant,aux);
  ant->next=n;
  n->next=aux;
}

int conteiner::sai()
{
  assert(inicio); //garante que não está vazia
  nodeptr n(inicio);
  int valor=inicio->custo;
  inicio = inicio->next;
  delete n;
  if ( inicio == 0 ) // se for o último node
    fim = 0;
  return valor;
}

bool conteiner::vazia()
{
  return bool(inicio == 0); // verdadeiro se fila vazia - inicio é um ponteiro null
}

void conteiner::posiciona(int x,nodeptr comeco,nodeptr ant,nodeptr aux){
  aux=comeco; 
  ant=aux;
  aux=aux->next;
  bool achou=false;
  if (aux->custo >= comeco->custo)
    while ((aux!=0)&&(aux->custo <= x)&&(achou==false)){
      if (x > aux->custo)
        achou=true;
      else{
        ant=aux;
        aux=aux->next;
      }
    }
  else
    while (aux!=0){
      ant=aux;
      aux=aux->next;
    }
}    
#endif
