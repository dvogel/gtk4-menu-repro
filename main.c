#include <stdio.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

#ifdef CUSTOM_WIDGETS
GtkWidget *menu_item_widget_new(
		const char *text
		)
{
	GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *label = gtk_label_new(text);
	gtk_box_append(GTK_BOX(layout), label);
	gtk_widget_set_visible(layout, true);
	return layout;
}
#endif

int main(
		int argc,
		char **argv
		)
{
	gtk_init();

	GMenu *main_menu = g_menu_new();
	GtkWidget *menubar = gtk_popover_menu_bar_new_from_model(G_MENU_MODEL(main_menu));

	GMenu *file_menu = g_menu_new();
	GMenuItem *file_item = g_menu_item_new_submenu("File", G_MENU_MODEL(file_menu));
	g_menu_insert_item(G_MENU(gtk_popover_menu_bar_get_menu_model(GTK_POPOVER_MENU_BAR(menubar))), 0, file_item);

	GMenu *recent_menu = g_menu_new();
	GMenuItem *recent_item = g_menu_item_new_submenu("Recent", G_MENU_MODEL(recent_menu));

	GMenuItem *filename_item = g_menu_item_new("File.txt", NULL);
#ifdef CUSTOM_WIDGETS
	g_menu_item_set_attribute(filename_item, "custom", "s", "filename");
#endif
	g_menu_insert_item(recent_menu, 0, filename_item);
#ifdef CUSTOM_WIDGETS
	GtkWidget *filename_widget = menu_item_widget_new("CustomFile.txt");
	gtk_popover_menu_bar_add_child(GTK_POPOVER_MENU_BAR(menubar), filename_widget, "filename");
#endif

	g_menu_insert_item(file_menu, 0, recent_item);

	GMenuItem *exit_item = g_menu_item_new("Exit", NULL);
#ifdef CUSTOM_WIDGETS
	g_menu_item_set_attribute(exit_item, "custom", "s", "exit");
#endif
	g_menu_insert_item(file_menu, 1, exit_item);
#ifdef CUSTOM_WIDGETS
	GtkWidget *exit_widget = menu_item_widget_new("Custom Exit");
	gtk_popover_menu_bar_add_child(GTK_POPOVER_MENU_BAR(menubar), exit_widget, "exit");
#endif

	g_free(exit_item);
	g_free(file_item);
	g_free(filename_item);
	g_free(recent_item);

    GtkWidget *mainwin = gtk_window_new();
	GtkWidget *win_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_box_append(GTK_BOX(win_layout), menubar);
	gtk_window_set_child(GTK_WINDOW(mainwin), win_layout);
	gtk_window_present(GTK_WINDOW(mainwin));

	while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0)
		g_main_context_iteration(NULL, TRUE);

	return 0;
}
