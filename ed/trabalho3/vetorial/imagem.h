#ifndef imagem_h
#define imagem_h

#include "poligono.h"

class imagem{
  private:
   bool vazia();
  
   //Lista de Poligonos
   struct node{
     poligono pol;
     struct node *next;
   };
   typedef struct node *nodeptr;
   nodeptr topo;
  public:
    imagem();
    //void drawall();
    //void remove();
    void insere(poligono);
};
  
#endif

