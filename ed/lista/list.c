#include <stdlib.h>  /* for malloc */
#include <stdio.h>   /* for printf */
#include <string.h>  /* for string comparison and copy */
#include "list.h"

node *list_add(node **p, int tar, char* city) {
    node *n = malloc(sizeof(node));
    n->next = *p;
    *p = n;
    n->tarifa = tar;
    strncpy (n->cidade, city, 29);
    return n;
}

void list_remove(node **p) { /* remove head */
    if (*p != NULL) {
        node *n = *p;
        *p = (*p)->next;
        free(n);
    }
}

node **list_search_tarifa(node **n, int tar) {
    while (*n != NULL) {
        if ((*n)->tarifa == tar) {
            return n;
        }
        n = &(*n)->next;
    }
    return NULL;
}

node **list_search_cidade(node **n, char* city) {
    while (*n != NULL) {
        if (!strncmp ( (*n)->cidade, city, 29) ) {
            return n;
        }
        n = &(*n)->next;
    }
    return NULL;
}

void list_print(node *n) {
    if (n == NULL) {
        printf("list is empty\n");
    }
    while (n != NULL) {
        printf("print %p %p %d %s\n", n, n->next, n->tarifa, n->cidade);
        n = n->next;
    }
}
