#include <iostream>
#include <cstdlib>
#include "tad.h"

using namespace std;

int main(void){
  int cont=1;
  conteiner dados;
  for(int i=0;i<=50;i++){
    dados.entra(random());
  }
  cout<<"Chamadas recebidas, procedendo para atendimento:"<<endl;
  while (dados.vazia()==false){
    cout<<"Atendendo chamada "<<cont<<": Custo: "<<dados.sai()<<endl;
    cont++;
  }
  cout<<"Todas as chamadas foram atendidas. Saindo.";
  return 0;
}
