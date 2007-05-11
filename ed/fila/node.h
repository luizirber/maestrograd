//Definição de node.h
#ifndef NODE_H
#define NODE_H

template < class TipoElementar >
class node{
  public: 
    node( const TipoElementar & );
    void setData( TipoElementar );
    TipoElementar getData() const;
    void setNextPtr( node & );
    const node *getNextPtr();
  private:
    TipoElementar data;
    node *nextPtr;
};
#endif
