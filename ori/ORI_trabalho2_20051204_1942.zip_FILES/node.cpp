//node.cpp
#include "file_block.h"

template <class K>
node<K>::node(){
 modified = true;
 full = false;
}

template <class K>
node<K>::~node(){
 delete modified;
 delete full;
}

template <class K>
bool node<K>::binarySearch(K* keys, int size, K key, int position){
 bool found = false;
 int low = 0;
 int high = size - 1;
 while ((high>=low)&&(!found)) {
  int mid = (low+high)/2;
  if ( key < keys[mid] )
   high = mid - 1;
  else
   if (key > keys[mid])
    low = mid + 1;
   else
    found = true;
 }
 if (found)
  position = mid;
 else
  position = high;
 return found;
}
