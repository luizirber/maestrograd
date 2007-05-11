#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#include <iomanip>

using std::setw;

#include "tartaruga.h"

int main(void){

  tartaruga logo;
  char virgula;
  logo.CanetaRisca();
  int comando=0,passos=0;
  while ( comando!=9 ){
    cout<<"     ##     "<<"  Turtle Graphics"<<endl
        <<"    #  #    "<<"  A tartaruga esta na posicao ("<<logo.getPos_h()<<","<<logo.getPos_v()<<")"<<endl
        <<"### #  # ###"<<"  e virada para a direcao "<<logo.getFrente()<<endl
        <<"# #  ##  # #"<<"  Use os comandos: "<<endl
        <<"####/| \\####"<<"  1 - Caneta risca"<<endl
        <<"   /| | \\   "<<"  2 - Caneta nao risca"<<endl
        <<"  | | |  |  "<<"  3 - Giro à direita"<<endl
        <<"  | | |  |  "<<"  4 - Giro à esquerda"<<endl
        <<"###\\ | |/###"<<"  5,M - Move M espacos"<<endl
        <<"# ##\\ |/## #"<<"  6 - Executa os comandos e imprime o arranjo"<<endl
        <<"###  ##  ###"<<"  9 - Termina o programa"<<endl
        <<"Insira os comandos: ";
        comando=0;
        while ((comando!=6)&&(comando!=9)){
          cin>>setw(1)>>comando;
          if ((comando<=6)&&(comando>=1)){
            if (comando==5){
              cin>>virgula>>setw(2)>>passos;
              logo.InsereComando(comando,passos);
            }
            else
              logo.InsereComando(comando,0);
          }
        }
  }
  return 0;
}
