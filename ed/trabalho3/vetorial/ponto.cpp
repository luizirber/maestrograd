#include "ponto.h"

ponto::ponto() {
  x=0; y=0;}
  
ponto::ponto(int a, int b){
  set_ponto(a,b);}
 
void ponto::set_ponto(int a, int b){
  x=a; y=b;
}

void ponto::get_ponto(int &x1,int &y1){
  x1=x;
  y1=y;
}

