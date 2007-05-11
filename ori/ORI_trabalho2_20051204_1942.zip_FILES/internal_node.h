#ifndef internal_node_h
#define internal_node_h
#define block_size 4096
#include "node.h"
#include "file_block.h"

template <class K>
class internal_node : public node {
 public:
  internal_node();
  ~internal_node();
  virtual bool insert (node* current_node, K key, block* address, bool divided, K promoted, node* created_node);
  virtual bool find (node* current_node,K key, block* address);
 private:
  struct i_node{
   int counter;
   K keys[(block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*))];
   node* ptr[1+(block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*))];
   bool NA[block_size-(sizeof(int)+sizeof(node*)+(sizeof(K)+sizeof(node*))*((block_size-(sizeof(int)+sizeof(node*)))/(sizeof(K)+sizeof(node*))))];
  };
  i_node iNODE;
  virtual void divide (K key, block* address, K promoted, node* divided_node, node* created_node);
};

#endif
