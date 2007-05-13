#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ns {
        char cidade[30];
        int tarifa;
        struct ns *next;
} node;

node *list_add(node **p, int tar, char* city);

void list_remove(node **p);

node **list_search_tarifa(node **n, int tar);

node **list_search_cidade(node **n, char* city);

void list_print(node *n);

#ifdef __cplusplus
}
#endif

#endif /*LIST_H*/
