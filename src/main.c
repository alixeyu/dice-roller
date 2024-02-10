#include <gtk/gtk.h>

static void print_hello(GtkWidget * widget, gpointer data) {
    g_print("Hello, world!\n");
}

GtkWidget* init_window(GtkApplication* app, char* title, int width, int height, bool is_fixed_size) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_resizable(GTK_WINDOW(window), !is_fixed_size);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    return window;
}

GtkWidget* init_button(char* title) {
    GtkWidget *button = gtk_button_new_with_label(title);
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    return button;
}

GtkWidget* init_dropdown(const char* const options[]) {
    GtkWidget* dropdown = gtk_drop_down_new_from_strings(options);
    return dropdown;
}

GtkWidget* init_input_panel() {
    const char* const dice_types[] = { "d4", "d6", "d8", "d10", "d12", "d20", "d100", NULL };

    GtkWidget* input_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(input_panel, GTK_ALIGN_FILL);
    gtk_box_set_spacing(GTK_BOX(input_panel), 10);

    GtkWidget *dice_num = gtk_entry_new();
    GtkWidget *mod_value = gtk_entry_new();

    gtk_entry_set_max_length(GTK_ENTRY(dice_num), 3);
    gtk_entry_set_max_length(GTK_ENTRY(mod_value), 5);

    GtkWidget *dice_type = init_dropdown(dice_types);
    gtk_widget_set_size_request(dice_type, 120, -1);

    gtk_box_append(GTK_BOX(input_panel), dice_num);
    gtk_box_append(GTK_BOX(input_panel), dice_type);
    gtk_box_append(GTK_BOX(input_panel), mod_value);

    return input_panel;
}


GtkWidget* init_info_panel() {
    GtkWidget* info_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* throw_result = gtk_text_new();

    gtk_widget_set_halign(info_panel, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(info_panel), throw_result);

    return info_panel;
}


GtkWidget* init_control_panel() {
    GtkWidget* control_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* roll_button = init_button("Roll");

    gtk_widget_set_halign(control_panel, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(control_panel), roll_button);

    return control_panel;
}


static void activate(GtkApplication *app, gpointer used_data) {
    GtkWidget *window = init_window(app, "Dice Roller", 360, 240, true);
    GtkWidget *main_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_box_append(GTK_BOX(main_panel), init_input_panel());
    gtk_box_append(GTK_BOX(main_panel), init_info_panel());
    gtk_box_append(GTK_BOX(main_panel), init_control_panel());

    gtk_window_set_child(GTK_WINDOW(window), main_panel);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
