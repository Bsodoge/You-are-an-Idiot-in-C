#include <gtk-2.0/gtk/gtk.h> 
#include <stdio.h>
#include <time.h>
//Build with gcc `pkg-config --cflags --libs gtk+-2.0` main.c -o gtktest

struct Vector{
    gint x;
    gint y;
} typedef vector;

struct Window{
    GtkWindow *win;
    GtkImage *img;
    vector position;
    vector velocity;
    gint isWhite;
} typedef window;

/* void set_inital_pos(){
    GdkScreen *screen = gdk_screen_get_default();
    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);
    position.x = width/2;
    position.y = height/2;
}  */

gint change_image(gpointer currentWindow){
    window *ptr = currentWindow;
    gtk_image_clear(ptr->img);
    if(ptr->isWhite == 0){
        gtk_image_set_from_file(ptr->img, "white.svg");
        ptr->isWhite = 1;
    } else {
        gtk_image_set_from_file(ptr->img, "black.svg");
        ptr->isWhite = 0;
    }
    return 1;
}

void detectEdge(gpointer currentWindow){
    gint currentWidth, currentHeight;
    window *ptr = currentWindow;
    GdkScreen *screen = gdk_screen_get_default();
    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);
    gtk_window_get_size(ptr->win, &currentWidth, &currentHeight);
    if((ptr->position.x > width - currentWidth) ||  (ptr->position.x < 0)){
        ptr->velocity.x = -ptr->velocity.x;
    }
    if((ptr->position.y > height - currentHeight) || (ptr->position.y < 0)){
        ptr->velocity.y = -ptr->velocity.y;
    }
}

gint move_window(gpointer currentWindow){
    window *ptr = currentWindow;
    ptr->position.x += ptr->velocity.x;
    ptr->position.y += ptr->velocity.y;
    gtk_window_move(ptr->win,  ptr->position.x, ptr->position.y);
    detectEdge(ptr);
    return 1;
}

void end_program(GtkWidget *wid, gpointer ptr){
    gtk_main_quit();
}

/* void procreate(){
    for (gint i = 0; i < 1; i++){
        GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        GtkWidget *img = gtk_image_new_from_file("black.svg");
        gtk_container_add(GTK_CONTAINER(win), img);
        gtk_widget_show_all(win);
        g_timeout_add(1, move_window, win);
        g_timeout_add(400, change_image, img);
    }
} */

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer ptr){ 
    if(event->keyval == 65513 || event->keyval == 65514 || event->keyval == 65428 || event->keyval == 65507 || event->keyval == 65508 || event->keyval == 65535 || event->keyval == 65473){
/*         procreate(); */
        GtkWidget *dlg = gtk_dialog_new_with_buttons("Warning", GTK_WINDOW(ptr), GTK_DIALOG_DESTROY_WITH_PARENT, "Ok", 0, NULL);
        GtkWidget *lbl = gtk_label_new("You are an Idiot!");
        gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), lbl);
        gtk_widget_show_all(dlg);
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
    }
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
/*     set_inital_pos(); */
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *img = gtk_image_new_from_file("black.svg");
    g_signal_connect(win, "key_press_event" ,G_CALLBACK(on_key_press), win);
    gtk_container_add(GTK_CONTAINER(win), img);
    gtk_widget_show_all(win);
    window newWindow = {GTK_WINDOW(win), GTK_IMAGE(img), {0, 0}, {1, 1}, 0}; 
    g_timeout_add(1, move_window, &newWindow);
    g_timeout_add(400, change_image, &newWindow);
    gtk_main();
    return 0;
}