#include <gtk-2.0/gtk/gtk.h> 
#include <stdio.h>
#include <time.h>
//Build with gcc `pkg-config --cflags --libs gtk+-2.0` main.c -o gtktest

struct Vector{
    int x;
    int y;
} typedef vector;

vector position = { 0 , 0 };
vector velocity = { 1 , 1 };

void detectEdge(gpointer ptr){
    gint currentWidth, currentHeight;
    GdkScreen *screen = gdk_screen_get_default();
    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);
    gtk_window_get_size(ptr, &currentWidth, &currentHeight);
    if((position.x > width - currentWidth) ||  (position.x < 0)){
        velocity.x = -velocity.x;
        system("( speaker-test -t sine -f 1000 )& pid=$! ; sleep 0.1s ; kill -9 $pid");
    }
    if((position.y > height - currentHeight) || (position.y < 0)){
        velocity.y = -velocity.y;
        system("( speaker-test -t sine -f 1000 )& pid=$! ; sleep 0.1s ; kill -9 $pid");
    }
}

gint move_window(gpointer ptr){
    position.x += velocity.x;
    position.y += velocity.y;
    gtk_window_move(ptr,  position.x, position.y);
    detectEdge(ptr);
    return 1;
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
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), win);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
    gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    g_timeout_add(1, move_window, win);
    gtk_main();
    return 0;
}