/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: LeftVboxCall.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <vte/vte.h>
#include <pthread.h>
#include <glib.h>

#include "LeftVboxCall.h"
#include "RightVboxFace.h"
#include "Cfg.h"
#include "Serie.h"
#include "SendFile.h"

static int is_hex_send = 0;
static int is_open = 0;
static int is_keep_send = 0;
static int save_format = 0;

void
on_conf_button_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_cfg = create_configuration_dialog (user_data);
	gtk_widget_show (window_cfg);
}

void
on_save_conf_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_file_choose;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	xcomdata->choose_file = 2;	
	window_file_choose = (GtkWidget *)create_file_choose(xcomdata);
	gtk_widget_show (window_file_choose);
}

void
on_load_conf_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_file_choose;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;	
	
	xcomdata->choose_file = 0;
	window_file_choose = (GtkWidget *)create_file_choose(xcomdata);
	gtk_widget_show (window_file_choose);
}

void
on_open_uart_clicked (GtkButton *button, gpointer user_data)
{
	int ret = 0;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	debug_p("left_vbox baud: %d \n", xcomdata->comcfg.baud);
	
	if (xcomdata->com_stat) {		
		check_port(xcomdata);
		xcomdata->com_stat = 0;
		gtk_label_set_text(GTK_LABEL (xcomdata->gcom_stat), "close");
		gtk_button_set_label(GTK_BUTTON (xcomdata->button_open_uart), "Open Com");
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gbutton_send_data), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gbutton_send_file), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gkeep_send), FALSE);
		debug_p("hide uart\n");
	} else {
		ret = config_uart(xcomdata);	
		if(ret < 0)
			return;
		xcomdata->com_stat = 1;
		gtk_label_set_text(GTK_LABEL (xcomdata->gcom_stat), "open");
		gtk_button_set_label(GTK_BUTTON (xcomdata->button_open_uart), "Close Com");
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gbutton_send_data), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gbutton_send_file), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(xcomdata->gkeep_send), TRUE);
	}
}

void
on_hex_show_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	is_hex_show_data();
}

void
on_new_count_clicked (GtkButton *button, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	clean_count();
	gtk_entry_set_text(GTK_ENTRY(xcomdata->grcv_num_show), "0");
	gtk_entry_set_text(GTK_ENTRY(xcomdata->gsend_num_show), "0");
}


void
on_clean_rcv_buff_clicked (GtkButton *button, gpointer user_data)
{
	clear_display();
}

void
on_save_data_clicked (GtkButton *button, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	int ret = 0;
	
	debug_p("save_vte_data\n");
	if (xcomdata->save_vte) {
		xcomdata->save_vte = 0;
		gtk_button_set_label(GTK_BUTTON (xcomdata->button_save_vte), "Log Data");
		do_log(0);
		save_fclose();
	} else {
		debug_p("path:%s\n", xcomdata->save_file);
		unsigned char logpath[1024] = {0};
		time_t timep;
        struct tm *p;
        time(&timep);
        p=localtime(&timep);

		snprintf(logpath, sizeof(logpath), "log to:%s_%s_%d%d%d%d", xcomdata->save_file, 
			getlast(xcomdata->comcfg.port), (1+p->tm_mon), p->tm_mday,p->tm_hour, p->tm_min);
		debug_p("%s\n", logpath + 7);
		if(save_format)
			ret = save_fopen(logpath + 7, 1);
		else
			ret = save_fopen(logpath + 7, 0);
		if (ret)
			create_xgcom_msg(xcomdata->gmain, "<b>Cann't Open the file!!!</b>");
		else {
			xcomdata->save_vte = 1;
			create_xgcom_msg(xcomdata->gmain, logpath);
			gtk_button_set_label(GTK_BUTTON (xcomdata->button_save_vte), "Stop Log");
			do_log(1);
		}
	}
}


void
on_choose_file_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_file_choose;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	xcomdata->choose_file = 1;
	window_file_choose = (GtkWidget *)create_file_choose(xcomdata);
	gtk_widget_show (window_file_choose);
}


void
on_send_file_clicked (GtkButton *button, gpointer user_data)
{
	FILE *fd = NULL;
	int ret = 0, len = 0;
	struct stat my_stat;
	unsigned char frame[1024] = {0};
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	if (stat(xcomdata->send_file, &my_stat) == 0) {
		fd = fopen(xcomdata->send_file, "r");
		
		do{
			fgets(frame, sizeof(frame), fd);
			if (feof(fd) != 0)
				break;
			printf("send: %s \n", frame);
			len = strlen(frame);
			ret = write_uart(frame, len);
			if (ret < 0)
				perror("write error:\n");
			memset(frame,'\0',sizeof(frame));
		}while(1);//end while
		
		fclose(fd);
		create_xgcom_msg(xcomdata->gmain, "finish sending file!!!\n");
	} else {
		create_xgcom_msg(xcomdata->gmain, "<b>Cann't Open the file!!!</b>");
	}
}

void
on_clean_send_buff_clicked (GtkButton *button, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	GtkTextBuffer *buff = NULL;

	buff = gtk_text_view_get_buffer((GtkTextView *)xcomdata->gsend_text);
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buff), _(""), -1);
}

void *send_data(struct xcomdata *xcomdata)
{
	int len = 0, ret = 0;
	GtkTextIter start,end;
	GtkTextBuffer *buff = NULL;
	gchar *text = NULL;
	
	if (!xcomdata->com_stat) {
		create_xgcom_msg(xcomdata->gmain, "<b>Uart doesn't open!!!</b>");
		return;
	}
	buff = gtk_text_view_get_buffer((GtkTextView *)xcomdata->gsend_text);
	gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER(buff), &start, &end);
	text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buff), &start, &end, FALSE);
	len = strlen(text);
	if (len) {
		if (is_hex_send == 0) {
			ret = write_uart(text, len);
		} else {
			ret = hex_send(text);
		}
		if (ret < 0)
			create_xgcom_msg(xcomdata->gmain,
							"<b>write:: Input/output error</b>");
	} else {
		create_xgcom_msg(xcomdata->gmain, "<b>No words to be send!!!</b>");
	}
	debug_p("data: %s len:%d \n", text, len);
}

void
on_send_data_clicked	 (GtkButton *button, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	send_data(xcomdata);
}


void
on_hex_send_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	if(is_hex_send == 0)
		is_hex_send = 1;
	else 
		is_hex_send = 0;
}

void *keep_send(struct xcomdata *xcomdata)
{	
	send_data(xcomdata);
	debug_p("keep send\n");	
}

void
on_keep_send_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{	
	static guint time_handl;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	if(is_keep_send){
		if (time_handl)
			gtk_timeout_remove(time_handl);	
		is_keep_send =0;
	} else {
		xcomdata->interval = atoi(gtk_entry_get_text(GTK_ENTRY(xcomdata->ginterval)));
		if(xcomdata->interval < 50)
			xcomdata->interval = 50;
		time_handl = gtk_timeout_add(xcomdata->interval, (GtkFunction) keep_send, xcomdata);
		is_keep_send = 1;
	}
}

void
on_add_save_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	if(GTK_TOGGLE_BUTTON(togglebutton)->active){
		save_format = xcomdata->save_format = 0;
		debug_p("add\n");
	}
}

void
on_cover_save_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	if(GTK_TOGGLE_BUTTON(togglebutton)->active){
		save_format = xcomdata->save_format = 1;
		debug_p("cover\n");
	}
}


