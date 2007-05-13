#include <stdio.h>   /* for printf */
#include "list.h"

int main(void) {
    node *n = NULL;

    list_add(&n, 0, "sao carlos");
    list_add(&n, 1, "sao paulo" );
    list_add(&n, 2, "sao joao"  );
    list_add(&n, 3, "sao pedro" );
    list_add(&n, 4, "sao tome"  );
    list_print(n);
    list_remove(&n);
    list_remove(list_search_tarifa(&n, 1));
    list_remove(&n->next);
    list_remove(&n);

    return 0;
}
