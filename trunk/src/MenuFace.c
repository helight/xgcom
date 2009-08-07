/*
 * Xcomtool (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: MenuFace.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include "MenuFace.h"
#include "MenuCall.h"

GtkWidget* create_menu (GtkWidget *main_windown, GtkWidget *main_vbox, 
			GtkAccelGroup *accel_group, gpointer data)
{
	GtkWidget *main_menubar;
	GtkWidget *menuitem_file;
	GtkWidget *menu_file;
	GtkWidget *save_conf_file;
	GtkWidget *save_as_conf;
	GtkWidget *separatormenuitem_file;
	GtkWidget *quit_file;
	GtkWidget *menuitem_edit;
	GtkWidget *menu_edit;
	GtkWidget *config;
	GtkWidget *menuitem_view;
	GtkWidget *menu_view;
	GtkWidget *menuitem_help;
	GtkWidget *menu_help;
	GtkWidget *about_xcomtool;
	
	main_menubar = gtk_menu_bar_new ();
	gtk_widget_show (main_menubar);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_menubar, FALSE, FALSE, 0);

	menuitem_file = gtk_menu_item_new_with_mnemonic (_("\137File"));
	gtk_widget_show (menuitem_file);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_file);

	menu_file = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_file), menu_file);

	save_conf_file = gtk_image_menu_item_new_from_stock ("gtk-save", accel_group);
	gtk_widget_show (save_conf_file);
	gtk_container_add (GTK_CONTAINER (menu_file), save_conf_file);

	save_as_conf = gtk_image_menu_item_new_from_stock ("gtk-save-as", accel_group);
	gtk_widget_show (save_as_conf);
	gtk_container_add (GTK_CONTAINER (menu_file), save_as_conf);

	separatormenuitem_file = gtk_separator_menu_item_new ();
	gtk_widget_show (separatormenuitem_file);
	gtk_container_add (GTK_CONTAINER (menu_file), separatormenuitem_file);
	gtk_widget_set_sensitive (separatormenuitem_file, FALSE);

	quit_file = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
	gtk_widget_show (quit_file);
	gtk_container_add (GTK_CONTAINER (menu_file), quit_file);

	menuitem_edit = gtk_menu_item_new_with_mnemonic (_("\137Edit"));
	gtk_widget_show (menuitem_edit);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_edit);

	menu_edit = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_edit), menu_edit);

	config = gtk_image_menu_item_new_from_stock ("gtk-cut", accel_group);
	gtk_widget_show (config);
	gtk_container_add (GTK_CONTAINER (menu_edit), config);

	menuitem_view = gtk_menu_item_new_with_mnemonic (_("\137View"));
	gtk_widget_show (menuitem_view);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_view);

	menu_view = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_view), menu_view);

	menuitem_help = gtk_menu_item_new_with_mnemonic (_("\137Help"));
	gtk_widget_show (menuitem_help);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_help);

	menu_help = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_help), menu_help);

	about_xcomtool = gtk_menu_item_new_with_mnemonic (_("\137About"));
	gtk_widget_show (about_xcomtool);
	gtk_container_add (GTK_CONTAINER (menu_help), about_xcomtool);
	
	g_signal_connect ((gpointer) save_conf_file, "activate",
		G_CALLBACK (on_save_conf_activate),
		NULL);
	g_signal_connect ((gpointer) save_as_conf, "activate",
		G_CALLBACK (on_save_as_conf_activate),
		NULL);
	g_signal_connect ((gpointer) quit_file, "activate",
		G_CALLBACK (on_quit_file_activate),
		NULL);
	g_signal_connect ((gpointer) config, "activate",
		G_CALLBACK (on_config_activate),
		NULL);
	g_signal_connect ((gpointer) about_xcomtool, "activate",
		G_CALLBACK (on_about_xcomtool_activate),
		(gpointer)main_windown);
	
	return main_menubar;
}
