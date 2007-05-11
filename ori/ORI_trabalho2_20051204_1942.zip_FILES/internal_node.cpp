#include <iostream>
#include <cassert>
#define block_size 4096
#include "node.h"
#include "file_block.h"
#include "internal_node.h"
using namespace std;

template <class K>
internal_node<K>::internal_node() {
 iNODE.counter = 0;
 for (int i = 0; i<(1+(block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*))); i++)
  iNODE.ptr[i] = NULL;
}

template <class K>
internal_node<K>::~internal_node() {
 // VERIFICAÇÃO QUE INCLUI DELEÇÃO DO RESPECTIVO BLOCO NO HD
}

template <class K>
bool internal_node<K>::insert(node* current_node, K key, block* address, bool divided, K promoted, node* created_node){
}

template <class K>
bool internal_node<K>::find (node* current_node, K key, block* address){
 int key_array_size =  block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*);
 int pos;
 bool search = binarySearch(current_node.iNODE.keys,key_array_size,pos);
 return (find(current_node.iNODE.ptr[pos+1],key,address));
}

template <class K>
void internal_node<K>::divide(K key, block* address, K promoted, node* divided_node, node* created_node){
 int n = 1+(block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*));
 internal_node* newNODE;
 assert(newNODE!=0);
 newNODE = new internal_node;
 if ((K < dividedNODE.iNODE.keys[n/2])&&(K > dividedNODE.iNODE.keys[n/2-1])) {
  promoted = key;
  for (int i = n/2; i < n; i++ ) {
   newNODE.iNODE.keys[i-(n/2)] = dividedNODE.iNODE.keys[i];
   newNODE.iNODE.ptr[i+1-(n/2)] = dividedNODE.iNODE.ptr[i+1];
  }
  newNODE.iNODE.ptr[0] = dividedNODE.iNODE.ptr[n/2];
 }
 else {
  if (K < dividedNODE.iNODE.keys[(n/2)-1]) {
   promoted = dividedNODE.iNODE.keys[(n/2)-1];
   for (int i = (n/2); i < n; i++){
    newNODE.iNODE.keys[i-(n/2)] = dividedNODE.iNODE.keys[i];
    newNODE.iNODE.ptr[i+1-(n/2)] = dividedNODE.iNODE.ptr[i+1];
   }
   newNODE.iNODE.ptr[0] = newNODE.iNODE.ptr[(n/2)+1];
   bool K_key_inserted = false;
   K temp1, temp2;
   node* address1;
   node* address2;
   for (int i = 0; i < (n/2)-1; i++) {
    if (!K_key_inserted) {
     if (K < dividedNODE.iNODE.keys[i]) {
      temp1 = dividedNODE.iNODE.keys[i];
      address1 = dividedNODE.iNODE.ptr[i+1];
      dividedNODE.iNODE.keys[i] = key;
      dividedNODE.iNODE.ptr[i+1] = reinterpret_cast<node*>(&address);
      K_key_inserted = true;
     }
    }
    else {
     temp2 = dividedNODE.iNODE.keys[i];
     address2 = dividedNODE.iNODE.ptr[i+1];
     dividedNODE.iNODE.keys[i] = temp1;
     dividedNODE.iNODE.ptr[i+1] = address1;
     temp1 = temp2;
     address1 = address2;
    }
   }
   dividedNODE.iNODE.keys[(n-2)-1] = temp1;
   dividedNODE.iNODE.ptr[(n-2)] = address1;
   address1 = NULL;
   address2 = NULL;
  }
  else {
   promoted = dividedNODE.iNODE.keys[n/2];
   bool K_key_inserted = false;
   K temp1, temp2;
   node* address1;
   node* address2;
   for (int i = (n/2)+1; i < n-1; i++){
    if (!K_key_inserted){
     if (K < dividedNODE.iNODE.keys[i]) {
      temp1 = dividedNODE.iNODE.keys[i];
      address1 = dividedNODE.iNODE.ptr[i+1];
      newNODE.iNODE.keys[i-((n/2)+1)] = key;
      newNODE.iNODE.ptr[i+1-((n/2)+1)] = reinterpret_cast<node*>(&address);
      K_key_inserted = true;
     }
     else {
      newNODE.iNODE.keys[i-((n/2)+1)] = dividedNODE.iNODE.keys[i];
      newNODE.iNODE.ptr[i+1-((n/2)+1)] = dividedNODE.iNODE.ptr[i+1];
     }
    }
    else {
     temp2 = dividedNODE.iNODE.keys[i];
     address2 = dividedNODE.iNODE.ptr[i+1];
     newNODE.iNODE.keys[i-((n/2)+1)] = temp1;
     newNODE.iNODE.ptr[i+1-((n/2)+1)] = address1;
     temp1 = temp2;
     address1 = address2;
    }
   }
   if (!K_key_inserted) {
    newNODE.iNODE.keys[n-(n/2)] = key;
    newNODE.iNODE.ptr[n+1-(n/2)] = reinterpret_cast<node*>(&address);
   }
   newNODE.iNODE.ptr[0] = dividedNODE.iNODE.ptr[(n/2)+1];
   address1 = NULL;
   address2 = NULL;
  }
 }
 newNODE.iNODE.counter = n - (n/2);
 dividedNODE.iNODE.counter = n/2;
 created_node = newNODE;
 newNODE = NULL;
 delete newNODE;
}
