/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: RightVboxFace.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include <string.h>
#include <vte/vte.h>
#include "RightVboxFace.h"

static gboolean show_index = FALSE;
static int bytes_per_line = 80;
static int total_bytes = 0;
static int local_echo_on = 0;
GtkWidget *rcv_text;
struct xcomdata *xcomdata;

static void Got_Input(VteTerminal *, gchar *, guint, gpointer);


GtkWidget* create_rightvbox (GtkWidget *main_window, GtkWidget *body_hbox, 
			GtkAccelGroup *accel_group, gpointer data)
{
	GtkWidget *right_vbox;
	GtkWidget *right_vpaned;
	GtkWidget *rcv_frame;
	GtkWidget *alignment2;
	GtkWidget *scrolledwindow2;
	GtkWidget *rcv_label;
	GtkWidget *send_frame;
	GtkWidget *alignment1;
	GtkWidget *scrolledwindow1;
	GtkWidget *send_text;
	GtkWidget *send_label;
	
	xcomdata = (struct xcomdata *)data;
	
	right_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (right_vbox);
	gtk_box_pack_start (GTK_BOX (body_hbox), right_vbox, TRUE, TRUE, 0);
	gtk_widget_set_size_request (right_vbox, 500, -1);

	right_vpaned = gtk_vpaned_new ();
	gtk_widget_show (right_vpaned);
	gtk_container_add (GTK_CONTAINER (right_vbox), right_vpaned);
  
	rcv_frame = gtk_frame_new (NULL);
	gtk_widget_show (rcv_frame);
	//gtk_box_pack_start (GTK_BOX (right_vbox), rcv_frame, TRUE, TRUE, 0);
	gtk_paned_pack1 (GTK_PANED (right_vpaned), rcv_frame, FALSE, TRUE);
	gtk_widget_set_size_request (rcv_frame, -1, 380);

	alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment2);
	gtk_container_add (GTK_CONTAINER (rcv_frame), alignment2);

	scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow2);
	gtk_container_add (GTK_CONTAINER (alignment2), scrolledwindow2);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2),  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_SHADOW_IN);

	rcv_text = vte_terminal_new();
	vte_terminal_set_backspace_binding(VTE_TERMINAL(rcv_text),
				     VTE_ERASE_ASCII_BACKSPACE);
	gtk_widget_show (rcv_text);
	gtk_container_add (GTK_CONTAINER (scrolledwindow2), rcv_text);
	
	rcv_label = gtk_label_new (_("Receive:"));
	gtk_widget_show (rcv_label);
	gtk_frame_set_label_widget (GTK_FRAME (rcv_frame), rcv_label);
	gtk_label_set_use_markup (GTK_LABEL (rcv_label), TRUE);

	send_frame = gtk_frame_new (NULL);
	gtk_widget_show (send_frame);
	//gtk_box_pack_start (GTK_BOX (right_vbox), send_frame, TRUE, TRUE, 0);
	gtk_paned_pack2 (GTK_PANED (right_vpaned), send_frame, FALSE, TRUE);

	alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment1);
	gtk_container_add (GTK_CONTAINER (send_frame), alignment1);

	scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow1);
	gtk_container_add (GTK_CONTAINER (alignment1), scrolledwindow1);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1),  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

	send_text = gtk_text_view_new ();
	gtk_widget_show (send_text);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (send_text), GTK_WRAP_CHAR);
	gtk_container_add (GTK_CONTAINER (scrolledwindow1), send_text);
	
	send_label = gtk_label_new (_("Send:"));
	gtk_widget_show (send_label);
	gtk_frame_set_label_widget (GTK_FRAME (send_frame), send_label);
	gtk_label_set_use_markup (GTK_LABEL (send_label), TRUE);
	
	g_signal_connect_after(GTK_OBJECT(rcv_text), "commit", G_CALLBACK(Got_Input), NULL);
	
	xcomdata->grcv_text = rcv_text;
	xcomdata->gsend_text = send_text;

	return right_vbox;
}

void put_hexadecimal(gchar *string, guint size)
{
	static gchar data[128];
	static gchar data_byte[6];
	static guint bytes;
	glong column, row;

	gint i = 0;

	if(size == 0)
	return;

	while(i < size) {  
		sprintf(data_byte, "%02X ", (guchar)string[i]);
		i++;
		vte_terminal_feed(VTE_TERMINAL(rcv_text), data_byte, 3);
	}
	
}

void put_text(gchar *string, guint size)
{
	int pos;
	GString *buffer_tmp;
	gchar *in_buffer;

	buffer_tmp =  g_string_new(string);
	in_buffer=buffer_tmp->str;
	in_buffer += size;
	
	for (pos = size; pos > 0; pos--) {
		in_buffer--;
		if(*in_buffer=='\r' && *(in_buffer+1) != '\n'){
			g_string_insert_c(buffer_tmp, pos, '\n');
			size += 1;
		}
		if(*in_buffer=='\n' && *(in_buffer-1) != '\r'){
			g_string_insert_c(buffer_tmp, pos-1, '\r');
			size += 1;
		}
	}
	vte_terminal_feed(VTE_TERMINAL(rcv_text), buffer_tmp->str, size);
}

void clear_display(void)
{
	if(rcv_text)
		vte_terminal_reset(VTE_TERMINAL(rcv_text), TRUE, TRUE);
}

gint send_serial(gchar *string, gint len)
{
	gint bytes_written;

	bytes_written = Send_chars(string, len);
	if(bytes_written > 0){
		if(local_echo_on)
			put_text(string, bytes_written);
	}

	return bytes_written;
}

static void Got_Input(VteTerminal *widget, gchar *text, guint length, gpointer ptr)
{
	if(xcomdata->com_stat)
		send_serial(text, length);
}

void set_local_echo()
{
	local_echo_on = 1;
	debug_p("local echo: %d \n", local_echo_on);
}

void clean_local_echo()
{
	local_echo_on = 0;	
	debug_p("local echo: %d \n", local_echo_on);
}
