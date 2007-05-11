#include "poligono.h"

poligono::poligono(){
  visivel=false;
  aberto=false;
  topo=0;
}

bool poligono::vazio(){
  return (topo==0);
}

void poligono::set_aberto(bool abr){
  aberto=abr;
}

void poligono::set_visivel(bool vis){
  visivel=vis;
}

void poligono::set_vertice(ponto aux){
  nodeptr p;
  p=new node;
  p->vertice=aux;
  p->next=0;
  
  if (vazio()){
    topo=p;}
  else {
    nodeptr corredor;
    corredor = topo;
    while (corredor->next != 0) {
      corredor->next = corredor;
    }
    corredor->next=p;
  }
}

//void draw(){}

