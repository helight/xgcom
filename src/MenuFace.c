/*
 * XGCom (Xiyou Linux Group)
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
	GtkWidget *quit_file;

	GtkWidget *menuitem_edit;
	GtkWidget *menu_edit;
	GtkWidget *local_echo;
	GtkWidget *config;

	GtkWidget *menuitem_tool;
	GtkWidget *menu_tool;
	GtkWidget *ascii_talbe;
	
	GtkWidget *menuitem_help;
	GtkWidget *menu_help;
	GtkWidget *help_xgcom;
	GtkWidget *about_xgcom;
	
	struct xcomdata *xcomdata = (struct xcomdata *)data;
	
	main_menubar = gtk_menu_bar_new ();
	gtk_widget_show (main_menubar);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_menubar, FALSE, FALSE, 0);

	menuitem_file = gtk_menu_item_new_with_mnemonic (_("_File"));
	gtk_widget_show (menuitem_file);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_file);

	menu_file = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_file), menu_file);

	quit_file = gtk_image_menu_item_new_from_stock ("gtk-quit", accel_group);
	gtk_widget_show (quit_file);
	gtk_container_add (GTK_CONTAINER (menu_file), quit_file);

	menuitem_edit = gtk_menu_item_new_with_mnemonic (_("_Edit"));
	gtk_widget_show (menuitem_edit);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_edit);

	menu_edit = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_edit), menu_edit);

	local_echo = gtk_menu_item_new_with_mnemonic (_("_Local_Echo"));
	gtk_widget_show (local_echo);
	gtk_container_add (GTK_CONTAINER (menu_edit), local_echo);
	
	config = gtk_menu_item_new_with_mnemonic (_("_Configure"));
	gtk_widget_show (config);
	gtk_container_add (GTK_CONTAINER (menu_edit), config);

	menuitem_tool = gtk_menu_item_new_with_mnemonic (_("_Tools"));
	gtk_widget_show (menuitem_tool);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_tool);

	menu_tool = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_tool), menu_tool);
	
	ascii_talbe = gtk_menu_item_new_with_mnemonic (_("_ASCII"));
	gtk_widget_show (ascii_talbe);
	gtk_container_add (GTK_CONTAINER (menu_tool), ascii_talbe);

	menuitem_help = gtk_menu_item_new_with_mnemonic (_("_Help"));
	gtk_widget_show (menuitem_help);
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_help);

	menu_help = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_help), menu_help);

	help_xgcom = gtk_menu_item_new_with_mnemonic (_("_Help"));
	gtk_widget_show (help_xgcom);
	gtk_container_add (GTK_CONTAINER (menu_help), help_xgcom);
	
	about_xgcom = gtk_menu_item_new_with_mnemonic (_("_About"));
	gtk_widget_show (about_xgcom);
	gtk_container_add (GTK_CONTAINER (menu_help), about_xgcom);
	
	g_signal_connect ((gpointer) quit_file, "activate",
		G_CALLBACK (on_quit_file_activate),
		NULL);
	g_signal_connect ((gpointer) local_echo, "activate",
		G_CALLBACK (on_local_echo_activate),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) config, "activate",
		G_CALLBACK (on_config_activate),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) ascii_talbe, "activate",
		G_CALLBACK (on_ascii_talbe_activate),
		(gpointer)main_windown);
	g_signal_connect ((gpointer) help_xgcom, "activate",
		G_CALLBACK (on_help_xgcom_activate),
		(gpointer)main_windown);	
	g_signal_connect ((gpointer) about_xgcom, "activate",
		G_CALLBACK (on_about_xgcom_activate),
		(gpointer)main_windown);
	
	return main_menubar;
}
