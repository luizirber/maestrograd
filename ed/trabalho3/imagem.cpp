#include "imagem.h"

imagem::imagem(){
  topo=0;             //Lista Vazia
}

bool imagem::vazia(){
  return (topo=0);
}

void imagem::insere(poligono aux){   
  nodeptr p;
  p=new node;
  p->pol=aux;
  p->next=0;
  
  if (vazia()){
    topo=p;}
  else {
    nodeptr corredor;
    corredor=topo;
    while (corredor->next != 0){
      corredor=corredor->next;
    }
    
    corredor->next=p;  //Next da ultima posicao recebe p (insere-se o poligono a ultima posicao)

  }     

}

