#include <iostream>
using namespace std;

int fatorial (int);

int main(void)
{
  
}

int fatorial(int n){
  int resultado=1;
  for (int i=1; i<=n; i++){
    resultado=resultado*i;
  }
  return resultado;
}
