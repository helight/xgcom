/*
 * Xcomtool (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: MenuCall.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#include "MenuCall.h"

void
on_save_conf_activate (GtkMenuItem *menuitem, gpointer user_data)
{

}


void
on_save_as_conf_activate (GtkMenuItem *menuitem, gpointer user_data)
{

}


void
on_quit_file_activate (GtkMenuItem	*menuitem, gpointer user_data)
{
	printf("bey world;\n");
	gtk_main_quit();
}


void
on_config_activate (GtkMenuItem *menuitem, gpointer user_data)
{

}


void
on_about_xcomtool_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget *window_about;

	window_about = create_about_xcomtool ((GtkWidget *)user_data);
	gtk_widget_show (window_about);
}
