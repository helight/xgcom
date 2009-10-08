/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: SendFile.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#include <string.h>
#include "SendFile.h"
#include "Funs.h"


void on_button_cancel_clicked (GtkButton *button, gpointer user_data);
void on_button_ok_clicked (GtkButton *button, gpointer user_data);
static GtkWidget *file_choose;


GtkWidget* create_file_choose (struct xcomdata *xcomdata)
{
	GtkWidget *dialog_vbox;
	GtkWidget *dialog_action_area;
	GtkWidget *button_cancel;
	GtkWidget *button_ok;

	if(xcomdata->choose_file < 2) {
		file_choose = gtk_file_chooser_dialog_new ("", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
		button_ok = gtk_button_new_from_stock ("gtk-open");
	} else {
		file_choose = gtk_file_chooser_dialog_new ("", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, NULL);
		button_ok = gtk_button_new_from_stock ("gtk-save");
	}
	gtk_window_set_type_hint (GTK_WINDOW (file_choose), GDK_WINDOW_TYPE_HINT_DIALOG);

	dialog_vbox = GTK_DIALOG (file_choose)->vbox;
	gtk_widget_show (dialog_vbox);

	dialog_action_area = GTK_DIALOG (file_choose)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	button_cancel = gtk_button_new_from_stock ("gtk-cancel");
	gtk_widget_show (button_cancel);
	gtk_dialog_add_action_widget (GTK_DIALOG (file_choose), button_cancel, GTK_RESPONSE_CANCEL);
	GTK_WIDGET_SET_FLAGS (button_cancel, GTK_CAN_DEFAULT);

	gtk_widget_show (button_ok);
	gtk_dialog_add_action_widget (GTK_DIALOG (file_choose), button_ok, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (button_ok, GTK_CAN_DEFAULT);

	g_signal_connect ((gpointer) button_cancel, "clicked",
		    G_CALLBACK (on_button_cancel_clicked),
		    xcomdata);
	g_signal_connect ((gpointer) button_ok, "clicked",
		    G_CALLBACK (on_button_ok_clicked),
		    xcomdata);
	gtk_widget_grab_default (button_ok);

	return file_choose;
}

void on_button_cancel_clicked (GtkButton *button, gpointer user_data)
{
	gtk_widget_destroy(GTK_WIDGET(file_choose));
}


void on_button_ok_clicked (GtkButton *button, gpointer user_data)
{
	char *filename = NULL;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_choose));
	switch (xcomdata->choose_file ){	
		case 0:
			strcpy(xcomdata->cfg_file, filename);
			debug_p("load cfg file : %s \n", filename);
			read_config(xcomdata);
			break;
		case 1:
			strcpy(xcomdata->send_file, filename);
			debug_p("file name :%s \n", xcomdata->send_file);
			break;
		case 2:
			strcpy(xcomdata->cfg_file, filename);
			debug_p("save cfg file : %s \n", filename);
			save_cfg_file(xcomdata);
			break;
		case 3:
			break;
		default:
			break;
			
	}
	gtk_widget_destroy(GTK_WIDGET(file_choose));
}

