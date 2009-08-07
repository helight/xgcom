/*
 * Xcomtool (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: About.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <gtk/gtk.h>
#include "About.h"

GtkWidget* create_about_xcomtool (GtkWidget *main_window)
{
	GtkWidget *about_xcomtool;
	GdkPixbuf *about_xcomtool_icon_pixbuf;
	GtkWidget *dialog_vbox;
	GtkWidget *vbox_xcomtool;
	GtkWidget *image_photo;
	GtkWidget *label_note;
	GtkWidget *label_author;
	GtkWidget *button_close;
	GtkWidget *dialog_action_area;
	GtkWidget *close_about;

	about_xcomtool = gtk_dialog_new_with_buttons("About XGCom", 
	GTK_WINDOW(main_window), GTK_DIALOG_DESTROY_WITH_PARENT,NULL);
	gtk_window_set_type_hint (GTK_WINDOW (about_xcomtool), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	about_xcomtool_icon_pixbuf = create_pixbuf ("zhwen.png");
	if (about_xcomtool_icon_pixbuf)
	{
		gtk_window_set_icon (GTK_WINDOW (about_xcomtool), about_xcomtool_icon_pixbuf);
		gdk_pixbuf_unref (about_xcomtool_icon_pixbuf);
	}

	dialog_vbox = GTK_DIALOG (about_xcomtool)->vbox;
	gtk_widget_show (dialog_vbox);

	vbox_xcomtool = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox_xcomtool);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), vbox_xcomtool, TRUE, TRUE, 0);

	image_photo = create_pixmap (about_xcomtool, "zhwen.png");
	gtk_widget_show (image_photo);
	gtk_box_pack_start (GTK_BOX (vbox_xcomtool), image_photo, TRUE, TRUE, 0);

	label_note = gtk_label_new (_("<b>XGCom (0.01)</b>"));
	gtk_widget_show (label_note);
	gtk_box_pack_start (GTK_BOX (vbox_xcomtool), label_note, FALSE, FALSE, 0);
	gtk_label_set_use_markup (GTK_LABEL (label_note), TRUE);

	label_author = gtk_label_new (_("XGCom is a open source software.\nCopyright \302\251 Helight.xu@gmail.com"));
	gtk_widget_show (label_author);
	gtk_box_pack_start (GTK_BOX (vbox_xcomtool), label_author, FALSE, FALSE, 0);

	button_close = gtk_button_new_with_mnemonic (_("http://zhwen.org"));
	gtk_widget_show (button_close);
	gtk_box_pack_start (GTK_BOX (vbox_xcomtool), button_close, FALSE, FALSE, 0);
	gtk_button_set_relief (GTK_BUTTON (button_close), GTK_RELIEF_NONE);

	dialog_action_area = GTK_DIALOG (about_xcomtool)->action_area;
		gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_SPREAD);
	gtk_widget_show (dialog_action_area);

	close_about = gtk_button_new_from_stock ("gtk-close");
	gtk_widget_show (close_about);
	gtk_dialog_add_action_widget (GTK_DIALOG (about_xcomtool), close_about, GTK_RESPONSE_CLOSE);
	GTK_WIDGET_SET_FLAGS (close_about, GTK_CAN_DEFAULT);

	g_signal_connect ((gpointer) button_close, "clicked",
		G_CALLBACK (on_button_link_clicked), NULL);
	g_signal_connect ((gpointer) close_about, "clicked",
		G_CALLBACK (on_close_about_clicked), about_xcomtool);

	gtk_widget_grab_focus (button_close);
	return about_xcomtool;
}

void
on_close_about_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_about = (GtkWidget *)user_data;
	gtk_widget_destroy(GTK_WIDGET(window_about));
}


void
on_button_link_clicked (GtkButton *button, gpointer user_data)
{
	gchar tmp[80];
	g_snprintf(tmp,80,"firefox http://zhwen.org & >/dev/null");
	system(tmp);
}
