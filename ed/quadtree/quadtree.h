#ifndef QUADTREE_H
#define QUADTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glib.h>
#include <gdk/gdkpixbuf.h>

typedef struct ns {
    guint32 cor;
    int width, height;
    struct ns *EsqSuperior, *EsqInferior, *DirSuperior, *DirInferior;
} node;

node *new_node();

int Opaco(node **raiz);

void CriaQuadTree(node **raiz, GdkPixbuf *imagem);
GdkPixbuf *RecuperaQuadTree(node **raiz);

char* gera_string(char* string, int recuo);
void AuxImprimeQuadTree(node **raiz, int recuo);
void imprimeQuadTree(node **raiz);

#ifdef __cplusplus
}
#endif

#endif //QUADTREE_H
