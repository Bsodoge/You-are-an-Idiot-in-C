#include <gtk-2.0/gtk/gtk.h> 
#include <stdio.h>
#include <time.h>
//Build with gcc `pkg-config --cflags --libs gtk+-2.0` main.c -o gtktest


void random_pos(GtkWidget *wid, gpointer ptr){
    srand(time(NULL));
    int x = rand() % 100;
    int y = rand() % 100;
    gtk_window_move(ptr,  x, y);
}

void end_program(GtkWidget *wid, gpointer ptr){
    gtk_main_quit();
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Press the button");
    GtkWidget *lbl = gtk_label_new("Hello world");
    GtkWidget *box = gtk_vbox_new(FALSE, 5);
    g_signal_connect(btn, "clicked", G_CALLBACK(random_pos), win);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
    gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}