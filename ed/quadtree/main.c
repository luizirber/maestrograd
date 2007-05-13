/*****************************************************************************
    http://www.gtk.org/tutorial/
    
*****************************************************************************/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <math.h>
#include "quadtree.h"

GdkPixbuf *pixbuf;
GdkPixbuf *gerada;

node* raiz;

static void destroy (GtkWidget *widget, 
                     gpointer data  )
{
    gtk_main_quit();
}

static void load_pixbuf (GtkWidget *widget,
                         GtkWidget *draw )
{
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Abrir",
                        NULL,
                        GTK_FILE_CHOOSER_ACTION_OPEN,
                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                        NULL);
    
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar *filename;
    
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        gdk_pixbuf_fill(pixbuf, 0x00000000);
        gdk_draw_pixbuf (draw->window,
                         draw->style->fg_gc[GTK_WIDGET_STATE (widget)],
                         pixbuf, 0, 0, 0, 0, -1, -1,
                         GDK_RGB_DITHER_NONE, 0, 0);
        gtk_widget_queue_draw(draw);
        pixbuf = gdk_pixbuf_new_from_file (filename, NULL);
        gdk_draw_pixbuf (draw->window,
                         draw->style->fg_gc[GTK_WIDGET_STATE (widget)],
                         pixbuf, 0, 0, 0, 0, -1, -1,
                         GDK_RGB_DITHER_NONE, 0, 0);

        g_free (filename);
    }
    
    gtk_widget_destroy (dialog);   
}

static void source_expose (GtkWidget *widget,
                           GdkEventExpose *event,
                           gpointer data)
{
    if (pixbuf)
        gdk_draw_pixbuf (widget->window,
                         widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                         pixbuf, 0, 0, 0, 0, -1, -1, 
                         GDK_RGB_DITHER_NONE, 0, 0);
}

static void sink_expose (GtkWidget *widget,
                         GdkEventExpose *event,
                         gpointer data)
{
    if (gerada)
        gdk_draw_pixbuf (widget->window,
                         widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                         gerada, 0, 0, 0, 0, -1, -1, 
                         GDK_RGB_DITHER_NONE, 0, 0);
}

static void exec (GtkWidget *widget,
                  GtkWidget *draw   )
{   
    int imagem_valida = 1;
    
//    if ( gdk_pixbuf_get_width(pixbuf) == gdk_pixbuf_get_height(pixbuf) && 
//         ( (int)(sqrt( gdk_pixbuf_get_width(pixbuf) ) ) % 2 ) == 0 )
//         imagem_valida = 1;
    
    if (imagem_valida) {
        CriaQuadTree(&raiz, pixbuf);
    
        gerada = RecuperaQuadTree(&raiz);
        gdk_draw_pixbuf (draw->window,
                         draw->style->fg_gc[GTK_WIDGET_STATE (widget)],
                         gerada, 0, 0, 0, 0, -1, -1,
                         GDK_RGB_DITHER_NONE, 0, 0);
        gtk_widget_queue_draw(draw);
        
        printf("\n");        
        imprimeQuadTree(&raiz);
    }
    else {
        GtkMessageDialog *dialog;
        dialog = gtk_message_dialog_new (NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_ERROR,
                                         GTK_BUTTONS_CLOSE,
                                         "Imagem invalida.");    
        int response = gtk_dialog_run(dialog);
        if (response)
            gtk_widget_destroy(dialog);
    }
    raiz = new_node();    
}

int main(int argc, char* argv[])
{
    raiz = new_node();
    GtkWidget* window;
    GtkWidget* vbox;
    GtkWidget* hbox;
    GtkWidget* source_area;
    GtkWidget* sink_area;
    GtkWidget* widget;
    
    gtk_init (&argc, &argv);
    gerada = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 256, 256);
    gdk_pixbuf_fill(gerada, 0xffffff00);
    
    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 256, 256);
    gdk_pixbuf_fill(pixbuf, 0x00000000);

    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL) ;
                  
    vbox = gtk_vbox_new(FALSE, 2);
    hbox = gtk_hbox_new(FALSE, 2);
    gtk_container_add (GTK_CONTAINER( window ), vbox);    
    gtk_container_add (GTK_CONTAINER( vbox ), hbox);        
        
    source_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (source_area, 256, 256);    
    g_signal_connect (G_OBJECT (source_area), "expose-event",
                    G_CALLBACK (source_expose), NULL);
    sink_area = gtk_drawing_area_new ();    
    gtk_widget_set_size_request (sink_area, 256, 256);    
    g_signal_connect (G_OBJECT (sink_area), "expose-event",
                      G_CALLBACK (sink_expose), NULL);    
    gtk_box_pack_start (GTK_BOX( hbox ), source_area, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX( hbox ), sink_area, FALSE, FALSE, 3);        
    
    widget = gtk_button_new_with_label ("Carregar");
    gtk_widget_set_size_request (widget, 50, 40);    
    gtk_box_pack_start (GTK_BOX( vbox ), widget, FALSE, FALSE, 3);
    g_signal_connect (G_OBJECT (widget), "clicked",
                      G_CALLBACK (load_pixbuf), source_area);
    
    widget = gtk_button_new_with_label ("Executar");
    g_signal_connect (G_OBJECT (widget), "clicked",
                      G_CALLBACK (exec), sink_area);
    gtk_widget_set_size_request (widget, 50, 40);        
    gtk_box_pack_end (GTK_BOX( vbox ), widget, FALSE, FALSE, 3);
                  
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0; 
}
