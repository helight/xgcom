/*
 * Xcomtool (Xiyou Linux Group)
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
GtkWidget *rcv_text;

GtkWidget* create_rightvbox (GtkWidget *main_window, GtkWidget *body_hbox, 
			GtkAccelGroup *accel_group, gpointer data)
{
	GtkWidget *right_vbox;
	GtkWidget *rcv_frame;
	GtkWidget *alignment2;
	GtkWidget *scrolledwindow2;
	GtkWidget *rcv_label;
	GtkWidget *send_frame;
	GtkWidget *alignment1;
	GtkWidget *scrolledwindow1;
	GtkWidget *send_text;
	GtkWidget *send_label;
	
	struct xcomdata *xcomdata = (struct xcomdata *)data;
	
	right_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (right_vbox);
	gtk_box_pack_start (GTK_BOX (body_hbox), right_vbox, TRUE, TRUE, 0);
	gtk_widget_set_size_request (right_vbox, 320, -1);

	rcv_frame = gtk_frame_new (NULL);
	gtk_widget_show (rcv_frame);
	gtk_box_pack_start (GTK_BOX (right_vbox), rcv_frame, TRUE, TRUE, 0);

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
	
	rcv_label = gtk_label_new (_("\74b\76\346\216\245\346\224\266\345\214\272\74\57b\76"));
	gtk_widget_show (rcv_label);
	gtk_frame_set_label_widget (GTK_FRAME (rcv_frame), rcv_label);
	gtk_label_set_use_markup (GTK_LABEL (rcv_label), TRUE);

	send_frame = gtk_frame_new (NULL);
	gtk_widget_show (send_frame);
	gtk_box_pack_start (GTK_BOX (right_vbox), send_frame, TRUE, TRUE, 0);

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
	
	send_label = gtk_label_new (_("\74b\76\345\217\221\351\200\201\345\214\272\72\74\57b\76"));
	gtk_widget_show (send_label);
	gtk_frame_set_label_widget (GTK_FRAME (send_frame), send_label);
	gtk_label_set_use_markup (GTK_LABEL (send_label), TRUE);
	
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
/*  
		while(gtk_events_pending()) gtk_main_iteration();
		vte_terminal_get_cursor_position(VTE_TERMINAL(rcv_text), &column, &row);

		if(show_index) {
			if(column == 0){//First byte on line 			
				sprintf(data, "%6d: ", size);
				vte_terminal_feed(VTE_TERMINAL(rcv_text), data, strlen(data));
				bytes = 0;
			}
		} else {
			if(column == 0)
				bytes = 0;
		}

		// Print hexadecimal characters 
		data[0] = 0;

		while(bytes < bytes_per_line && i < size) {
			gint avance=0;
			gchar ascii[1];

			sprintf(data_byte, "%02X ", (guchar)string[i]);
			vte_terminal_feed(VTE_TERMINAL(rcv_text), data_byte, 3);

			avance = (bytes_per_line - bytes) * 3 + bytes + 2;

			// Move forward 
			sprintf(data_byte, "%c[%dC", 27, avance);
			vte_terminal_feed(VTE_TERMINAL(rcv_text), data_byte, strlen(data_byte));

			// Print ascii characters 	  
			ascii[0] = (string[i] > 0x1F) ? string[i] : '.';
			vte_terminal_feed(VTE_TERMINAL(rcv_text), ascii, 1);

			// Move backward 	      
			sprintf(data_byte, "%c[%dD", 27, avance + 1);
			vte_terminal_feed(VTE_TERMINAL(rcv_text), data_byte, strlen(data_byte));

			if(bytes == bytes_per_line / 2 - 1)
				vte_terminal_feed(VTE_TERMINAL(rcv_text), "- ", strlen("- "));

			bytes++;
			i++;

			// End of line ? 
			if(bytes == bytes_per_line){
				vte_terminal_feed(VTE_TERMINAL(rcv_text), "\r\n", 2);
				total_bytes += bytes;
			}

		}     
*/
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
	
	for (pos=size; pos>0; pos--) {
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
