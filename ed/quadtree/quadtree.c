#include <stdlib.h>
#include <string.h>
#include "quadtree.h"

node *new_node() {
    node *temp = malloc(sizeof(node));    
    temp->EsqInferior = NULL;
    temp->DirInferior = NULL;    
    temp->EsqSuperior = NULL;
    temp->EsqSuperior = NULL;
    temp->cor = 0;
    temp->width = 0;
    temp->height = 0;
    return temp;
}

int Opaco(node **raiz) {
    if ( (*raiz) && (*raiz)->EsqInferior && (*raiz)->EsqSuperior && 
         (*raiz)->DirInferior && (*raiz)->DirSuperior   )
        return 0;
    else
        return 1;
}

int cor_uniforme(GdkPixbuf* img) {

    int x, y;
    
    for ( y=0; y < gdk_pixbuf_get_height(img) - 1; y++)
        for ( x=0; x < gdk_pixbuf_get_width(img) - 1 ; x++) { 
            
            guint n_channels, rowstride;
    
            guchar *pixels, 
                   *current,
                   *next;
    
            pixels = gdk_pixbuf_get_pixels (img);
            n_channels = gdk_pixbuf_get_n_channels (img);
            rowstride = gdk_pixbuf_get_rowstride (img);
            current = pixels + x * n_channels + y * rowstride;
                
            pixels = gdk_pixbuf_get_pixels (img);
            n_channels = gdk_pixbuf_get_n_channels (img);
            rowstride = gdk_pixbuf_get_rowstride (img);
            next = pixels + (x+1) * n_channels + y * rowstride;
                                
            guint32 pixel_next;
            guint32 pixel_current;
    
            pixel_next = (
                           (next[0]) << 24 | 
                           (next[1]) << 16 |
                           (next[2]) <<  8
                         );            
    
            pixel_current = (
                                (current[0]) << 24 | 
                                (current[1]) << 16 |
                                (current[2]) <<  8 
                            );
            if ( pixel_next != pixel_current ) 
                return 0;
        }    
    
    return 1;
}

void CriaQuadTree(node **raiz, GdkPixbuf *imagem) {
    if ( cor_uniforme(imagem) ) {
        guchar *pixels = gdk_pixbuf_get_pixels (imagem);
        guint32 pixel;
        pixel = (
                    pixels[0] << 24 |
                    pixels[1] << 16 |
                    pixels[2] <<  8
                );
        (*raiz)->cor = pixel;
        (*raiz)->width = gdk_pixbuf_get_width (imagem);
        (*raiz)->height = gdk_pixbuf_get_height (imagem);        
    }
    else {
        node *ES = new_node();
        node *EI = new_node();
        node *DS = new_node();
        node *DI = new_node();
        (*raiz)->EsqInferior = EI;
        (*raiz)->EsqSuperior = ES;        
        (*raiz)->DirInferior = DI;
        (*raiz)->DirSuperior = DS;
        (*raiz)->width = gdk_pixbuf_get_width (imagem);
        (*raiz)->height = gdk_pixbuf_get_height (imagem);        
        
        int width_total = gdk_pixbuf_get_width (imagem);
        int height_total = gdk_pixbuf_get_height (imagem);
        int width_ES = width_total/2;
        int height_ES = height_total/2;                        
        
        GdkPixbuf *subpixbuf = gdk_pixbuf_new_subpixbuf (imagem, 0, 0, 
                                                         width_ES, 
                                                         height_ES);
        CriaQuadTree(&ES, subpixbuf);
       
        subpixbuf = gdk_pixbuf_new_subpixbuf (imagem, 0, height_ES,
                                              width_ES,
                                              height_total - height_ES);
        CriaQuadTree(&EI, subpixbuf);
        
        subpixbuf = gdk_pixbuf_new_subpixbuf (imagem, width_ES, 0, 
                                              width_total - width_ES,
                                              height_ES);
        CriaQuadTree(&DS, subpixbuf);                
        
        subpixbuf = gdk_pixbuf_new_subpixbuf (imagem, width_ES, height_ES,
                                              width_total - width_ES,
                                              height_total - height_ES);        
        CriaQuadTree(&DI, subpixbuf);
    }
}

GdkPixbuf *RecuperaQuadTree(node **raiz) {
    GdkPixbuf *img = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 
                    (*raiz)->width, (*raiz)->height);

    if ( Opaco ( &(*raiz) ) ) {
        gdk_pixbuf_fill(img, (*raiz)->cor);        
        return img;
    }
    else {
        GdkPixbuf *temp;
        gdk_pixbuf_fill(img, 0xffffff00);        
        
        temp = RecuperaQuadTree( &(*raiz)->EsqSuperior );
        gdk_pixbuf_copy_area (temp, 0, 0,
                              gdk_pixbuf_get_width (temp),
                              gdk_pixbuf_get_height (temp), 
                              img, 0, 0);
                     
        temp = RecuperaQuadTree( &(*raiz)->EsqInferior );
        gdk_pixbuf_copy_area (temp, 0, 0,
                   gdk_pixbuf_get_width (temp),
                   gdk_pixbuf_get_height (temp), 
                   img, 
                   0,
                   gdk_pixbuf_get_height (img) - gdk_pixbuf_get_height (temp));
        
        temp = RecuperaQuadTree( &(*raiz)->DirSuperior );
        gdk_pixbuf_copy_area (temp, 0, 0,
                   gdk_pixbuf_get_width (temp),
                   gdk_pixbuf_get_height (temp), 
                   img,
                   gdk_pixbuf_get_width (img) - gdk_pixbuf_get_width (temp),
                   0);
        
        temp = RecuperaQuadTree( &(*raiz)->DirInferior );
        gdk_pixbuf_copy_area (temp, 0, 0,
                   gdk_pixbuf_get_width (temp),
                   gdk_pixbuf_get_height (temp), 
                   img,
                   gdk_pixbuf_get_width (img) - gdk_pixbuf_get_width (temp),
                   gdk_pixbuf_get_height (img) - gdk_pixbuf_get_height (temp));
        return img;        
    }
}

char* gera_string(char* string, int recuo) {
    char* temp = malloc(sizeof(char)*(recuo+1)*10);
    int x;    
    for (x = 0; x < recuo; x++)
        temp[x] = '\0';
    for (x = 0; x < recuo; x++)
        strcat(temp, "   ");
    
    strcat(temp, string);
    
    return temp;
}

void AuxImprimeQuadTree(node **raiz, int recuo) {
    printf("endereco: %x\twidth: %i\theight: %i\t",
           (*raiz), (*raiz)->width, (*raiz)->height);
    if ( Opaco( &(*raiz ) ) ) 
        printf("cor: %x\n", (*raiz)->cor);
    else {
        printf("cor: transparente\n");        
        recuo++;
            
        char* aux = gera_string("EsqSuperior -> ", recuo);
        printf("%s", aux);
        AuxImprimeQuadTree(&(*raiz)->EsqSuperior, recuo);
        
        aux = gera_string("EsqInferior -> ", recuo);
        printf("%s", aux);
        AuxImprimeQuadTree(&(*raiz)->EsqInferior, recuo);

        aux = gera_string("DirInferior -> ", recuo);
        printf("%s", aux);
        AuxImprimeQuadTree(&(*raiz)->DirInferior, recuo);
        
        aux = gera_string("DirSuperior -> ", recuo);
        printf("%s", aux);
        AuxImprimeQuadTree(&(*raiz)->DirSuperior, recuo);
    }
    recuo--;    
}

void imprimeQuadTree(node **raiz) {
    int recuo = 0;
    AuxImprimeQuadTree(&(*raiz), recuo);
}
