#ifndef poligono_h
#define poligono_h

#include "ponto.h"



class poligono{
  private:
    bool aberto;
    bool visivel;
    bool vazio();
    
    /*Lista de pontos, que e tambem uma lista de vertices*/
    struct node{
      ponto vertice;
      struct node *next;
      };
    typedef struct node *nodeptr;
    nodeptr topo;
    /* Fim de definicao da lista*/
    
  public:
    poligono();                           //Construtor
    void set_aberto(bool);                //Modifica variavel que indica de poligono e aberto ou fechado
    void set_visivel(bool);               //Modifica variavel que indica se o poligono e visivel
    void set_vertice(ponto);           //Adiciona vertice ao poligono
//    void Draw();                          //Desenha poligono no canvas
};

#endif

