#ifndef file_block_h
#define file_block_h
#define block_size 4096

template <class D>
struct block{
 D* data[block_size/(sizeof(D*) + sizeof(bool))];
 bool set[block_size/(sizeof(D*) + sizeof(bool))];
 bool NA[block_size - (sizeof(D*)+sizeof(bool))*(block_size/(sizeof(D*) + sizeof(bool)))];
};

#endif
