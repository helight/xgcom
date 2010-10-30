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
 
#include <dirent.h>
#include <gdk/gdkkeysyms.h>

#include "MenuFace.h"
#include "MenuCall.h"

struct tools_item {
	GtkWidget *item;
	gchar	name[20];
};

GtkWidget* create_menu (GtkWidget *main_windown, GtkWidget *main_vbox, 
			GtkAccelGroup *accel_group, gpointer data)
{
	char path[256] = {0};
	char fname[20] = {0};
	DIR *dir;
	struct dirent *ptr;
	char *ch = NULL;
	int item_num = 0;
	
	GtkWidget *main_menubar;

	GtkWidget *menuitem_file;
	GtkWidget *menu_file;
	GtkWidget *send_uboot;
	GtkWidget *send_data;
	GtkWidget *quit_file;

	GtkWidget *menuitem_edit;
	GtkWidget *menu_edit;
	GtkWidget *local_echo;
	GtkWidget *send_break;
	GtkWidget *config;

	GtkWidget *menuitem_tool;
	GtkWidget *menu_tool;
	GtkWidget *ascii_talbe;
	
	struct tools_item tools[10];
	
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

	send_uboot = gtk_menu_item_new_with_mnemonic (_("_Send_Uboot"));
	gtk_widget_show (send_uboot);
	gtk_container_add (GTK_CONTAINER (menu_file), send_uboot);
	
	send_data = gtk_menu_item_new_with_mnemonic (_("_SendData"));
	gtk_widget_show (send_data);
	gtk_container_add (GTK_CONTAINER (menu_file), send_data);
	gtk_widget_add_accelerator (send_data, "activate", accel_group,
		GDK_Return, (GdkModifierType) GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
                            
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
	
	send_break = gtk_menu_item_new_with_mnemonic (_("_Send_Break"));
	gtk_widget_show (send_break);
	gtk_container_add (GTK_CONTAINER (menu_edit), send_break);
	
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
	
	g_signal_connect ((gpointer) send_uboot, "activate",
		G_CALLBACK (on_send_uboot_activate),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) send_data, "activate",
		G_CALLBACK (on_send_data_activate),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) quit_file, "activate",
		G_CALLBACK (on_quit_file_activate),
		NULL);
	g_signal_connect ((gpointer) local_echo, "activate",
		G_CALLBACK (on_local_echo_activate),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) send_break, "activate",
		G_CALLBACK (on_send_break_activate),
		NULL);
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

	sprintf(path, "%s/.xgcom", getenv("HOME"));
	debug_p("find plug tools: %s \n", path);
	
	if ((dir = opendir(path)) != NULL) {
		while((ptr = readdir(dir)) != NULL){
			ch = ptr->d_name;
			if(*ch != '.'){				
				sprintf(tools[item_num].name, "%s", ch);
				debug_p("file name:%s fname[]:%s\n",ch, tools[item_num].name);
				
				tools[item_num].item = gtk_menu_item_new_with_mnemonic (_(ch));
				gtk_widget_show (tools[item_num].item);
				gtk_container_add (GTK_CONTAINER (menu_tool), tools[item_num].item);
				g_signal_connect ((gpointer) tools[item_num].item, "activate",
					G_CALLBACK (on_tools_item_activate),
					(gpointer)tools[item_num].name);
				if(++item_num == 10)
					break;	
			}
			
		}
		debug_p("find plug tools\n");
		closedir(dir);
	}
	
	return main_menubar;
}
