/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: MainWindow.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "support.h"
#include "MainWindow.h"
#include "FootFace.h"
#include "MenuFace.h"
#include "RightVboxFace.h"
#include "LeftVboxFace.h"

GtkWidget* create_Xgcom (struct xcomdata *xcomdata)
{
	GtkWidget *main_window;
	GdkPixbuf *Xgcom_icon_pixbuf;
	GtkWidget *main_vbox;
/*-------------------------main_menubar---------------------*/
	GtkWidget *main_menubar;
/*-------------------------body_hbox------------------------*/
	GtkWidget *body_hbox;
	
	GtkWidget *left_vbox;
/*------------------------right_vbox-------------------------*/
	GtkWidget *right_vbox;
/*------------------------foot_hbox--------------------------*/
	GtkWidget *foot_hbox;
	GtkAccelGroup *accel_group;

	accel_group = gtk_accel_group_new ();

	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//gtk_widget_set_size_request (main_window, 600, 700);
	GTK_WIDGET_SET_FLAGS (main_window, GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (main_window, GTK_CAN_DEFAULT);
	gtk_window_set_title (GTK_WINDOW (main_window), _("XGCom (Xiyou-Linux-Group)"));
	//gtk_window_set_default_size (GTK_WINDOW (main_window), 600, 700);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (main_window), TRUE);
	gtk_window_set_position (GTK_WINDOW (main_window), GTK_WIN_POS_CENTER);
	Xgcom_icon_pixbuf = create_pixbuf ("xgcom.png");
	if (Xgcom_icon_pixbuf){
		gtk_window_set_icon (GTK_WINDOW (main_window), Xgcom_icon_pixbuf);
		gdk_pixbuf_unref (Xgcom_icon_pixbuf);
	}

	main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (main_vbox);	
	gtk_container_add (GTK_CONTAINER (main_window), main_vbox);
	
/*------------------------main_menubar-----------------------*/
	main_menubar = create_menu(main_window, main_vbox, accel_group, xcomdata);

/*------------------------body_hbox--------------------------*/
	body_hbox = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (body_hbox);
	gtk_box_pack_start (GTK_BOX (main_vbox), body_hbox, TRUE, TRUE, 0);
	
/*-------------------------create_leftvbox-------------------*/
	left_vbox = create_leftvbox(main_window, body_hbox, accel_group, xcomdata);
	
/*-------------------------create_rightvbox------------------*/
	right_vbox = create_rightvbox(main_window, body_hbox, accel_group, xcomdata);
	
/*-------------------------create_foot-----------------------*/
	foot_hbox = create_foot(main_window, main_vbox, xcomdata);

	g_signal_connect ((gpointer) main_window, "delete_event",
		G_CALLBACK (on_Xgcom_delete_event), NULL);

	gtk_widget_grab_focus (main_window);
	gtk_widget_grab_default (main_window);
	gtk_window_add_accel_group (GTK_WINDOW (main_window), accel_group);

	xcomdata->gmain = main_window;
	debug_p("baud: %d \n", xcomdata->comcfg.baud);
	
	return main_window;
}

gboolean
on_Xgcom_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	debug_p("bye world;\n");
	close_uart();
	gtk_main_quit();
	
	return FALSE;
}
