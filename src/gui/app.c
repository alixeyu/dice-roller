#include <gtk/gtk.h>
#include "../constants.h"
#include "../dice/dice.h"

typedef struct {
    GtkWidget* dice_num;
    GtkWidget* dice_type;
    GtkWidget* mod_val;
    GtkWidget* throw_result;
} FieldsSet;


void make_throw(GtkWidget* widget, gpointer data) {
    FieldsSet* fields = data;
    const char* dice_num = gtk_editable_get_text(GTK_EDITABLE(fields->dice_num));
    const int dice_type = (int)gtk_drop_down_get_selected(GTK_DROP_DOWN(fields->dice_type));
    const char* mod_value = gtk_editable_get_text(GTK_EDITABLE(fields->mod_val));

    int dices = strtol(dice_num, (char **)NULL, 10);
    int modificator = strtol(mod_value, (char **)NULL, 10);

    char throw_result[25];
    sprintf(
        throw_result,
        "%d (%d%s+%d)",
        calculate_average_throw(dices, &DiceArray[dice_type]) + modificator,
        dices,
        *(&DiceArray[dice_type].dice_type),
        modificator
    );



    gtk_editable_set_text(GTK_EDITABLE(fields->throw_result), throw_result);
}


void configurate_app(GtkApplication* app, gpointer used_data) {
    static FieldsSet fields;
    FieldsSet* fields_ptr = &fields;

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Dice Roller");
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_window_set_default_size(GTK_WINDOW(window), 360, 240);

    GtkWidget* root_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(root_panel, GTK_ALIGN_FILL);
    gtk_box_set_spacing(GTK_BOX(root_panel), 30);

    GtkWidget* input_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(input_panel, GTK_ALIGN_FILL);
    gtk_box_set_spacing(GTK_BOX(input_panel), 10);

    GtkWidget* dice_num = gtk_entry_new();
    GtkWidget* dropdown = gtk_drop_down_new_from_strings(dice_types);
    GtkWidget* mod_value = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(dice_num), 3);
    gtk_widget_set_size_request(dropdown, 120, -1);
    gtk_entry_set_max_length(GTK_ENTRY(mod_value), 5);

    gtk_box_append(GTK_BOX(input_panel), dice_num);
    gtk_box_append(GTK_BOX(input_panel), dropdown);
    gtk_box_append(GTK_BOX(input_panel), mod_value);

    GtkWidget* info_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* throw_result = gtk_text_new();
    gtk_widget_set_halign(info_panel, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(info_panel), throw_result);

    fields_ptr->dice_num = dice_num;
    fields_ptr->dice_type = dropdown;
    fields_ptr->mod_val = mod_value;
    fields_ptr->throw_result = throw_result;

    GtkWidget* control_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* roll_button = gtk_button_new_with_label("Roll");
    gtk_widget_set_halign(control_panel, GTK_ALIGN_CENTER);
    g_signal_connect(GTK_BUTTON(roll_button), "clicked", G_CALLBACK(make_throw), &fields);

    gtk_box_append(GTK_BOX(control_panel), roll_button);

    gtk_box_append(GTK_BOX(root_panel), input_panel);
    gtk_box_append(GTK_BOX(root_panel), info_panel);
    gtk_box_append(GTK_BOX(root_panel), control_panel);

    gtk_window_set_child(GTK_WINDOW(window), root_panel);
    gtk_window_present(GTK_WINDOW(window));
}


int init_app(int argc, char** argv) {
    GtkApplication* app = gtk_application_new("Dice.Roller", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(configurate_app), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
