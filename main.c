#include <gtk-2.0/gtk/gtk.h> 
#include <stdio.h>
#include <time.h>
//Build with gcc `pkg-config --cflags --libs gtk+-2.0` main.c -o gtktest

struct Vector{
    int x;
    int y;
} typedef vector;

vector position = { 0 , 0 };
vector velocity = { -1 , 1 };
int isWhite = 0;

void set_inital_pos(){
    GdkScreen *screen = gdk_screen_get_default();
    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);
    position.x = width/2;
    position.y = height/2;
} 

gint change_image(gpointer ptr){
    gtk_image_clear(ptr);
    if(isWhite == 0){
        gtk_image_set_from_file(ptr, "white.svg");
        isWhite = 1;
    } else {
        gtk_image_set_from_file(ptr, "black.svg");
        isWhite = 0;
    }
    return 1;
}

void detectEdge(gpointer ptr){
    gint currentWidth, currentHeight;
    GdkScreen *screen = gdk_screen_get_default();
    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);
    gtk_window_get_size(ptr, &currentWidth, &currentHeight);
    if((position.x > width - currentWidth) ||  (position.x < 0)){
        velocity.x = -velocity.x;
    }
    if((position.y > height - currentHeight) || (position.y < 0)){
        velocity.y = -velocity.y;
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

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data){ 
    if(event->keyval == 65513 || event->keyval == 65514 || event->keyval == 65428 || event->keyval == 65507 || event->keyval == 65508 || event->keyval == 65535 || event->keyval == 65473){
        gtk_main_quit();
    }
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
/*     set_inital_pos(); */
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *img = gtk_image_new_from_file("black.svg");
    g_signal_connect(win, "key_press_event" ,G_CALLBACK(on_key_press), NULL);
    gtk_container_add(GTK_CONTAINER(win), img);
    gtk_widget_show_all(win);
    g_timeout_add(1, move_window, win);
    g_timeout_add(400, change_image, img);
    gtk_main();
    return 0;
}