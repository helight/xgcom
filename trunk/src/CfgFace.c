/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: CfgFace.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "support.h"
#include "Funs.h"
#include "Serie.h"

#define NUMBER_OF_DEVICES 16

gchar *devices_list[NUMBER_OF_DEVICES] = {
  "/dev/ttyS0",
  "/dev/ttyS1",
  "/dev/ttyS2",
  "/dev/ttyS3",
  "/dev/tts/0",
  "/dev/tts/1",
  "/dev/tts/2",
  "/dev/tts/3",
  "/dev/ttyUSB0",
  "/dev/ttyUSB1",
  "/dev/ttyUSB2",
  "/dev/ttyUSB3",
  "/dev/usb/tts/0",
  "/dev/usb/tts/1",
  "/dev/usb/tts/2",
  "/dev/usb/tts/3"
};

static GtkWidget *cfg_dialog;
static GtkWidget *com_port;
static GtkWidget *com_rate;
static GtkWidget *com_dbits;
static GtkWidget *com_sbits;
static GtkWidget *com_parity;
static GtkWidget *com_flow;

void on_save_button_clicked (GtkButton *button, gpointer user_data);
void on_ok_button_clicked (GtkButton *button, gpointer user_data);

GtkWidget* create_configuration_dialog (struct xcomdata *xcomdata)
{
	int i = 0;
	struct stat my_stat;

	GdkPixbuf *cfg_dialog_icon_pixbuf;
	GtkWidget *dialog_vbox;
	GtkWidget *setuo_frame;
	GtkWidget *alignment2;
	GtkWidget *setup_tablel;
	GtkWidget *label_port;
	GtkWidget *label_rate;
	GtkWidget *label_dbits;
	GtkWidget *label_sbits;
	GtkWidget *label_parity;
	GtkWidget *label_control;

	GtkWidget *setup_label;
	GtkWidget *dialog_action_area1;
	GtkWidget *cancel_button;
	GtkWidget *save_button;
	GtkWidget *ok_button;

	cfg_dialog = gtk_dialog_new ();
	gtk_widget_set_size_request (cfg_dialog, 240, 260);
	gtk_window_set_title (GTK_WINDOW (cfg_dialog), _("configuration"));
	gtk_window_set_position (GTK_WINDOW (cfg_dialog), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (cfg_dialog), TRUE);
	cfg_dialog_icon_pixbuf = create_pixbuf ("xgcom.png");
	if (cfg_dialog_icon_pixbuf) {
		gtk_window_set_icon (GTK_WINDOW (cfg_dialog), cfg_dialog_icon_pixbuf);
		gdk_pixbuf_unref (cfg_dialog_icon_pixbuf);
	}
	gtk_window_set_type_hint (GTK_WINDOW (cfg_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_gravity (GTK_WINDOW (cfg_dialog), GDK_GRAVITY_CENTER);

	dialog_vbox = GTK_DIALOG (cfg_dialog)->vbox;
	gtk_widget_show (dialog_vbox);

	setuo_frame = gtk_frame_new (NULL);
	gtk_widget_show (setuo_frame);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), setuo_frame, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (setuo_frame), 4);
	gtk_frame_set_label_align (GTK_FRAME (setuo_frame), 0.04, 0.51);

	alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment2);
	gtk_container_add (GTK_CONTAINER (setuo_frame), alignment2);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment2), 0, 0, 12, 0);

	setup_tablel = gtk_table_new (6, 2, FALSE);
	gtk_widget_show (setup_tablel);
	gtk_container_add (GTK_CONTAINER (alignment2), setup_tablel);
	gtk_container_set_border_width (GTK_CONTAINER (setup_tablel), 3);

	label_port = gtk_label_new (_("Port"));
	gtk_widget_show (label_port);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_port, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_widget_set_size_request (label_port, 90, -1);
	gtk_misc_set_alignment (GTK_MISC (label_port), 0, 0.5);

	label_rate = gtk_label_new (_("Baud rate"));
	gtk_widget_show (label_rate);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_rate, 0, 1, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label_rate), 0, 0.5);

	label_dbits = gtk_label_new (_("Data bits"));
	gtk_widget_show (label_dbits);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_dbits, 0, 1, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label_dbits), 0, 0.5);

	label_sbits = gtk_label_new (_("Stop bits"));
	gtk_widget_show (label_sbits);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_sbits, 0, 1, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label_sbits), 0, 0.5);

	label_parity = gtk_label_new (_("Parity"));
	gtk_widget_show (label_parity);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_parity, 0, 1, 4, 5,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label_parity), 0, 0.5);

	label_control = gtk_label_new (_("Flow control"));
	gtk_widget_show (label_control);
	gtk_table_attach (GTK_TABLE (setup_tablel), label_control, 0, 1, 5, 6,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_misc_set_alignment (GTK_MISC (label_control), 0, 0.5);

	com_port = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_port);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_port, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_port, 100, -1);

	for (i = 0; i < NUMBER_OF_DEVICES; i++) {
		if(stat(devices_list[i], &my_stat) == 0)
			//liste = g_list_append(liste, devices_list[i]);
			gtk_combo_box_append_text (GTK_COMBO_BOX (com_port),devices_list[i]);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_port), 0);
	//gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_port)->child), FALSE);	

	com_rate = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_rate);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_rate, 1, 2, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_rate, 100, -1);
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("300"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("600"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("1200"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("2400"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("4800"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("9600"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("19200"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("38400"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("57600"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_rate), _("115200"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_rate), 5);
	gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_rate)->child), FALSE);	 

	com_dbits = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_dbits);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_dbits, 1, 2, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_dbits, 100, -1);
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_dbits), _("5"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_dbits), _("6"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_dbits), _("7"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_dbits), _("8"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_dbits), 3);
	gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_dbits)->child), FALSE);  

	com_sbits = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_sbits);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_sbits, 1, 2, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_sbits, 100, -1);
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_sbits), _("1"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_sbits), _("2"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_sbits), 0);
	gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_sbits)->child), FALSE);   

	com_parity = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_parity);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_parity, 1, 2, 4, 5,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_parity, 100, -1);
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_parity), _("None"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_parity), _("Odd"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_parity), _("Even"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_parity), _("Space"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_parity), 0);
	gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_parity)->child), FALSE);   

	com_flow = gtk_combo_box_entry_new_text ();
	gtk_widget_show (com_flow);
	gtk_table_attach (GTK_TABLE (setup_tablel), com_flow, 1, 2, 5, 6,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_widget_set_size_request (com_flow, 100, -1);
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_flow), _("None"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_flow), _("Hardware"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (com_flow), _("Software"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(com_flow), 0);
	gtk_entry_set_editable(GTK_ENTRY(GTK_BIN(com_flow)->child), FALSE);   

	setup_label = gtk_label_new (_("\74b\76Setup\74\57b\76"));
	gtk_widget_show (setup_label);
	gtk_frame_set_label_widget (GTK_FRAME (setuo_frame), setup_label);
	gtk_label_set_use_markup (GTK_LABEL (setup_label), TRUE);

	dialog_action_area1 = GTK_DIALOG (cfg_dialog)->action_area;
	gtk_widget_show (dialog_action_area1);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

	save_button = gtk_button_new_with_mnemonic (_("Save Def")); 
	gtk_widget_show (save_button);
	gtk_dialog_add_action_widget (GTK_DIALOG (cfg_dialog), save_button, GTK_RESPONSE_OK);
	
	ok_button = gtk_button_new_with_mnemonic (_("Save Tmp"));
	gtk_widget_show (ok_button);
	gtk_dialog_add_action_widget (GTK_DIALOG (cfg_dialog), ok_button, GTK_RESPONSE_OK);
	GTK_WIDGET_SET_FLAGS (ok_button, GTK_CAN_DEFAULT);

	g_signal_connect ((gpointer) save_button, "clicked",
		G_CALLBACK (on_save_button_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) ok_button, "clicked",
		G_CALLBACK (on_ok_button_clicked),
		(gpointer)xcomdata);

	return cfg_dialog;
}

void get_data_from_window(struct xcomdata *xcomdata)
{
	gchar *fp = NULL;
	int row = -1;
	
	fp = gtk_combo_box_get_active_text(GTK_COMBO_BOX(com_port));
	strcpy(xcomdata->comcfg.port, fp);
	fp = gtk_combo_box_get_active_text(GTK_COMBO_BOX(com_rate));
	xcomdata->comcfg.baud = atoi(fp);
	fp = gtk_combo_box_get_active_text(GTK_COMBO_BOX(com_dbits));
	xcomdata->comcfg.databit = atoi(fp);
	fp = gtk_combo_box_get_active_text(GTK_COMBO_BOX(com_sbits));
	xcomdata->comcfg.stopbit = atoi(fp);
	row = gtk_combo_box_get_active(GTK_COMBO_BOX(com_parity));
	xcomdata->comcfg.parity = row;
	row = gtk_combo_box_get_active(GTK_COMBO_BOX(com_flow));
	xcomdata->comcfg.flow = row;
}
void
on_save_button_clicked (GtkButton *button, gpointer user_data)
{	
	struct stat con_stat;
	char path[256] = {0};
	
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	sprintf(path, "%s/.xgcom", getenv("HOME"));
	debug_p("path: %s \n", path);
	if(stat(path, &con_stat) != 0)
		mkdir(path, 0755);
	sprintf(path, "%s/.xgcom/.xgcom.conf", getenv("HOME"));
	debug_p("path: %s \n", path);
	get_data_from_window(xcomdata);
	do_save_cfg_file(&(xcomdata->comcfg), path);
	show_uart_param(xcomdata);
	if(xcomdata->com_stat)
		config_uart(xcomdata);
	gtk_widget_destroy(GTK_WIDGET(cfg_dialog));
	
	return;
}


void
on_ok_button_clicked (GtkButton *button, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;

	get_data_from_window(xcomdata);
	show_uart_param(xcomdata);
	if(xcomdata->com_stat)
		config_uart(xcomdata);
	gtk_widget_destroy(GTK_WIDGET(cfg_dialog));
	
	return;
}
