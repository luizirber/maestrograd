#include "vetor.h"
#include <iostream.h>
#include <assert.h>

int vetor<T>::cont_vetores =0; //inicia a variável

vetor::vetor(int t) {
  tamanho = (t > 0 ? t : 10);
  arranjo = new int [tamanho];
  assert(arranjo!=0);
  ++cont_vetores;
  for (int i=0; i<tamanho; i++)
    arranjo[i] =0 ;
}

vetor::vetor( const vetor& v):tamanho(v.tamanho) {
  arranjo = new int [tamanho];
  assert(arranjo!=0);
  ++cont_vetores;
  for (int i=0; i<tamanho; i++)
    arranjo[i] =v.arranjo[i] ;
}

vetor::~vetor( ) {
  delete [ ] arranjo;
  --cont_vetores;
}

int vetor::pega_tamanho( ) const {
  return tamanho;
}

vetor& vetor::operator=(const vetor& v) {
  if (&v!=this) // teste para auto atribuição
  { if (tamanho!= v.tamanho)
    { delete[ ] arranjo;
      tamanho = v.tamanho;
      arranjo = new int [tamanho];
      assert(arranjo!=0);
    }
    for (int i=0; i<tamanho; i++)
      arranjo[i] = v.arranjo[i];
  }
  return *this;
}

bool vetor::operator==(const vetor& v) const {
  if (tamanho!=v.tamanho)
    return false;
  for (int i=0; i<tamanho; i++)
    if (arranjo[i]!=v.arranjo[i])
      return false;
    return true;
}

bool vetor::operator!=(const vetor&v) const {
  return !(*this==v);
}

int& vetor::operator[ ](int i) {
  assert (i>=0 && i<tamanho);
  return arranjo[i];
}

const int&vetor::operator[ ](int i)const {
  assert (i>=0 && i<tamanho);
  return arranjo[i];
}

int vetor::pega_cont_vetores( ) {
  return cont_vetores;
}

ostream& operator<<(ostream& saida, const vetor& v) {
  for (int i=0; i<tamanho; i++)
    saida<<‘ ‘<<v.arranjo[i] ;
  saida<<endl;
  return saida;
}

istream& operator>>(istream& entrada,vetor& v) {
  for (int i=0; i<tamanho; i++)
    entrada>>v.arranjo[i] ;
  return entrada;
}

