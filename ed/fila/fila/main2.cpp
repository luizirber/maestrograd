#include <iostream>
#include "fila.h"

using std::cout;
using std::cin;

int main(void){
/*  node<float> n1(1),n2(2);
  n1.setNextPtr(n2);
  float x;
  x=n1.getData();
  cout<<x;
  return 0;
*/
  fila<int> teste;
  for (int i=0;i<=50;i++)
    teste.entra(i);
  int saida;
  for (int j=0;j<=50;j++)
  {
    saida=teste.sai();
    cout<<saida<<"\n";
  }
  return 0;
}
