#include <gtk-2.0/gtk/gtk.h> 
#include <stdio.h>

//Build with gcc `pkg-config --cflags --libs gtk+-2.0` main.c -o gtktest

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(win);
    gtk_main();
    return 0;
}