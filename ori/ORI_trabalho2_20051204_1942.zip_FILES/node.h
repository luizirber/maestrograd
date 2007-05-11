#ifndef node_h
#define node_h
#include "file_block.h"

template <class K> class B_plus_Tree;

template <class K>
class node{
  friend class B_plus_Tree<K>;
 public:
  node();
  ~node();
  virtual bool insert (node* current_node, K key, block* address, bool divided, K promoted, node* created_node) = 0;
  virtual bool find (node* current_node, K key, block* address) = 0;
 protected:
  virtual void divide (K key, block* address, K promoted, node* divided_node, node* created_node) = 0;
  bool modified;
  bool full;
  bool binarySearch(K* keys, int size, K key, int position);
};

#endif
