#include <iostream>
#include <cassert>
#define block_size 4096
#include "node.h"
#include "file_block.h"
#include "leafNODE.h"
using namespace std;

template <class K>
leaf_node<K>::leaf_node() {
 lNODE.counter = 0;
 for (int i = 0; i<(1+(block_size-(sizeof(int)+sizeof(block*)))/(sizeof(K)+sizeof(block*))); i++)
  lNODE.ptr[i] = NULL;
}

template <class K>
leaf_node<K>::~leaf_node() {
 // VERIFICAÇÃO QUE INCLUI DELEÇÃO DO RESPECTIVO BLOCO NO HD
}

template <class K>
bool leaf_node<K>::insert(node* current_node, K key, block* address, bool divided, K promoted, node* created_node){
}

template <class K>
bool leaf_node<K>::find (node* current_node, K key, block* address){
 int key_array_size = block_size-(sizeof(int)+sizeof(block*)))/(sizeof(K)+sizeof(block*);
 int pos;
 bool search = binarySearch(current_node.lNODE.keys,key_array_size,pos);
 if (search)
  address = current_node.lNODE.ptr[pos+1];
 return search;
}

template <class K>
void leaf_node<K>::divide (K key, block* address, K promoted, node* dividedNODE, node* createdNODE){
 int n = 1+(block_size-(sizeof(int)+sizeof(block*)))/(sizeof(K)+sizeof(block*));
 leaf_node* newNODE;
 assert(newNODE!=0);
 newNODE = new leaf_node;
 if (K < dividedNODE.lNODE.keys[(n-1)/2]) {
  if (K > dividedNODE.lNODE.keys[(n-1)/2-1]) {
   for (int i = ((n-1)/2); i < n; i++){
    newNODE.lNODE.keys[i-(((n-1)/2)+1)] = dividedNODE.lNODE.keys[i];
    newNODE.lNODE.ptr[i+1-(((n-1)/2)+1)] = dividedNODE.lNODE.ptr[i+1];
   }
   dividedNODE.lNODE.keys[(n-1)/2] = key;
   dividedNODE.lNODE.ptr[(n-1)/2+1] = address;
  }
  else {
   for (int i = (((n-1)/2)+1); i < n; i++){
    newNODE.lNODE.keys[i-(((n-1)/2)+1)] = dividedNODE.lNODE.keys[i];
    newNODE.lNODE.ptr[i+1-(((n-1)/2)+1)] = dividedNODE.lNODE.ptr[i+1];
   }
   bool K_key_inserted = false;
   K temp1, temp2;
   block* address1;
   block* address2;
   for (int i = 0; i<((n-1)/2); i++)
    if (!K_key_inserted) {
     if (key < dividedNODE.lNODE.keys[i]) {
      temp1 = dividedNODE.lNODE.keys[i];
      addess1 = dividedNODE.lNODE.ptr[i+1];
      dividedNODE.lNODE.keys[i] = key;
      dividedNODE.lNODE.ptr[i+1] = address;
      K_key_inserted = true;
     }
    }
    else {
     temp2 = dividedNODE.lNODE.keys[i];
     address2 = dividedNODE.lNODE.keys[i+1];
     dividedNODE.lNODE.keys[i] = temp1;
     dividedNODE.lNODE.ptr[i+1] = address1;
     temp1 = temp2;
     address1 = address2;
    }
   dividedNODE.lNODE.keys[(n-1)/2] = temp1;
   dividedNODE.lNODE.ptr[(n-1)/2+1] = address1;
   address1 = NULL;
   address2 = NULL;
   delete address1;
   delete address2;
  }
 }
 else {
  bool K_key_inserted = false;
  K temp1, temp2;
  block* address1;
  block* address2;
  for (int i = (((n-1)/2)+1); i < n; i++) {
   if (!K_key_inserted){
    if (key < dividedNODE.lNODE.keys[i]) {
     temp1 = dividedNODE.lNODE.keys[i];
     addess1 = dividedNODE.lNODE.ptr[i+1];
     newNODE.lNODE.keys[i-(((n-1)/2)+1)] = key;
     newNODE.lNODE.ptr[i+1-(((n-1)/2)+1)] = address;
     K_key_inserted = true;
    }
    else {
     newNODE.lNODE.keys[i-(((n-1)/2)+1)] = dividedNODE.lNODE.keys[i];
     newNODE.lNODE.ptr[i+1-(((n-1)/2)+1)] = dividedNODE.lNODE.ptr[i+1];
    }
   }
   else {
    temp2 = dividedNODE.lNODE.keys[i];
    address2 = dividedNODE.lNODE.keys[i+1];
    newNODE.lNODE.keys[i-(((n-1)/2)+1)] = temp1;
    newNODE.lNODE.ptr[i+1-(((n-1)/2)+1)] = address1;
    temp1 = temp2;
    address1 = address2;
   }
  }
  if (!K_key_inserted) {
   newNODE.lNODE.keys[(n-1)/2] = key;
   newNODE.lNODE.ptr[(n-1)/2+1] = address;
  }
  address1 = NULL;
  address2 = NULL;
  delete address1;
  delete address2;
 }
 promoted = newNODE.lNODE.keys[0];
 dividedNODE.lNODE.counter = ((n-1)/2)+1;
 newNODE.lNODE.counter = n-(((n-1)/2)+1);
 newNODE.lNODE.ptr[0] = dividedNODE.lNODE.ptr[0];
 created_node = newNODE;
 dividedNODE.lNODE.ptr[0] = reinterpret_cast<block*>(&created_node);
 newNODE = NULL;
 delete newNODE;
}
