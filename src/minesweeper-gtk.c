#include <gtk/gtk.h>
#include <minesweeper.h>

struct board *board;

struct board_pos {
    int x;
    int y;
};

static void button_callback (GtkWidget *widget, struct board_pos* data) //gpointer data)
{
    g_print ("%d, %d\n", data->x, data->y);
}

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Minesweeper GTK");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    // Create grid
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous((GtkGrid*)grid, TRUE);
    gtk_grid_set_column_homogeneous((GtkGrid*)grid, TRUE);
    
    // and buttons for mines
    for (int x = 0; x < board->_width; x++) {
        for (int y = 0; y < board->_height; y++) {
            GtkWidget *button = gtk_button_new_with_label ("#");
            struct board_pos pos;
            pos.x = x;
            pos.y = y;

            g_signal_connect (button, "clicked", G_CALLBACK (button_callback), &pos);
            gtk_grid_attach (grid, button, x, y, 1, 1);
        }
    }

    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    // setup the board
    srand (time (NULL));
    int width = 20;
    int height = 10;
    uint8_t *buffer = malloc (minimum_buffer_size(width, height));
    board = board_init (width, height, 0.1, buffer);

    app = gtk_application_new ("se.macode.minesweeper-gtk", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run (G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    return status;
}
