#include <stdio.h>
#include <gtk/gtk.h>

void on_file_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Abrir archivo", NULL, action,
        "_Cancelar", GTK_RESPONSE_CANCEL, "_Abrir", GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        
        FILE *archivo;
        char buffer[100];

        archivo = fopen(filename, "r");
        if (archivo == NULL) {
            printf("Error al abrir el archivo");
            return;
        }

        while (fgets(buffer, 100, archivo)) {
            printf("%s", buffer);
        }

        fclose(archivo);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lector de archivos");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    button = gtk_button_new_with_label("Seleccionar archivo");
    g_signal_connect(button, "clicked", G_CALLBACK(on_file_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(box), button);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}