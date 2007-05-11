//definição de node.cpp

#include "node.h"

template < class TipoElementar >
node<TipoElementar>::node( const TipoElementar &info)
  : data(info), nextPtr(0){ }

template < class TipoElementar >
void node <TipoElementar>::setData(TipoElementar x){
  data=x;
}

template < class TipoElementar >
TipoElementar node <TipoElementar>::getData() const{
  return data;
}

template < class TipoElementar >
void node <TipoElementar>::setNextPtr( node &p ){
  nextPtr=p;
}

template < class TipoElementar >
TipoElementar const * node<TipoElementar>::*getNextPtr(){
  return nextPtr;
}

