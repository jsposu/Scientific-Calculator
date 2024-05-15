#include <gtk/gtk.h>
#include <string>

using namespace std;

// Function declarations
static void on_button_clicked(GtkWidget *widget, gpointer data);
void create_buttons(GtkWidget *grid);
void update_display(const string& text);
void calculate_result();

static GtkWidget *display;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid to organize buttons and display
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the display
    display = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), display, 0, 0, 5, 1);

    // Create buttons
    create_buttons(grid);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void create_buttons(GtkWidget *grid) {
    const char *buttons[5][5] = {
        {"7", "8", "9", "/", "C"},
        {"4", "5", "6", "*", "("},
        {"1", "2", "3", "-", ")"},
        {"0", ".", "=", "+", "sqrt"},
        {"sin", "cos", "tan", "log", "exp"}
    };

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            GtkWidget *button = gtk_button_new_with_label(buttons[i][j]);
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)buttons[i][j]);
            gtk_grid_attach(GTK_GRID(grid), button, j, i + 1, 1, 1);
        }
    }
}

static string current_input = "";

void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *button_label = (const char *)data;
    string label(button_label);

    if (label == "C") {
        current_input = "";
    } else if (label == "=") {
        calculate_result();
        return;
    } else {
        current_input += label;
    }

    update_display(current_input);
}

void update_display(const string& text) {
    gtk_entry_set_text(GTK_ENTRY(display), text.c_str());
}

void calculate_result() {
    // Simple example: just evaluate as an arithmetic expression.
    // For a real scientific calculator, use a proper math library or parser.
    try {
        double result = stod(current_input); // Simplified: replace with real expression parsing
        current_input = to_string(result);
    } catch (...) {
        current_input = "Error";
    }
    update_display(current_input);
}
