//---------------------------------------------------------------------------
// Unit1
//---------------------------------------------------------------------------
#if !defined(fila_h)
  #define fila_h
#endif // fila_h
#include <cassert>

template < class TipoElementar >
class fila{
  public:
    fila();
    void entra(TipoElementar);
    TipoElementar sai();
    bool vazia();
  private:
    struct node;
    typedef node * nodeptr;
    struct node {
      TipoElementar data;
      nodeptr next;
    };
    nodeptr inicio;
    nodeptr fim;
};

template < class TipoElementar >
fila<TipoElementar>::fila()
{
  //inicia ponteiros como null
  fim=0;
  inicio=0;
}

template < class TipoElementar >
void fila<TipoElementar>::entra(TipoElementar t)
{
  // cria novo node e o coloca no fim da fila
  nodeptr n(new node);
  assert(n);
  n->next =0;
  n->data = t;
  if (inicio != 0)
  {  // se a lista não for vazia
    fim->next = n; // adiciona um novo elemento ao fim
    fim=n;
  }
  else
  {          // se for vazia
    inicio = n;   // começo e fim devem ser
    fim = n;      // o próprio node
  }
}

template < class TipoElementar >
TipoElementar fila<TipoElementar>::sai()
{
  assert(inicio); //garante que não está vazia
  nodeptr n(inicio);
  TipoElementar valor=inicio->data;
  inicio = inicio->next;
  delete n;
  if ( inicio == 0 ) // se for o último node
    fim = 0;
  return valor;
}

template < class TipoElementar >
bool fila<TipoElementar>::vazia()
{
  return bool(inicio == 0); // verdadeiro se fila vazia - inicio é um ponteiro null
}
