/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: main.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "MainWindow.h"
#include "support.h"
#include "Funs.h"

static int sta = 0;

void callback_icon(GtkStatusIcon *status_icon,gpointer data);
void init_xcomdata(struct xcomdata *xcomdata);
void init_from_config_file(struct xcomdata *xcomdata);
void show_uart_param(struct xcomdata *xcomdata);

int main (int argc, char *argv[])
{
	GdkPixbuf *panel_icon_pixbuf;
	GtkWidget *main_windown;
	GtkStatusIcon* icon;
	
	struct xcomdata xcomdata;

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	gtk_set_locale ();
	gtk_init (&argc, &argv);

	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
	add_pixmap_directory ("./pixmaps");
	add_pixmap_directory ("../pixmaps");
	
	init_xcomdata(&xcomdata);
	
	main_windown = create_Xgcom (&xcomdata);
	
	panel_icon_pixbuf = create_pixbuf ("xgcom.png");
	icon = gtk_status_icon_new_from_pixbuf (panel_icon_pixbuf);
	gtk_status_icon_set_tooltip(icon,"Xcomtool");
	g_signal_connect((gpointer)icon, "activate", G_CALLBACK(callback_icon), main_windown);
	
	gtk_widget_show (main_windown);

	init_from_config_file(&xcomdata);
	show_uart_param(&xcomdata);

	gtk_main(); 
 	return 0;
}

void callback_icon(GtkStatusIcon *status_icon,gpointer data)
{
	GtkWidget *main = (GtkWidget *)data;
	if (sta == 0) {
		gtk_widget_hide(main);
		sta = 1;
	} else {
		gtk_widget_show (main);
		sta = 0;
	}
}

void init_xcomdata(struct xcomdata *xcomdata)
{
	xcomdata->fd = -1;
	xcomdata->local_echo = 0;
	xcomdata->ishex_send = 0;
	xcomdata->com_stat = 0;
	xcomdata->rcv_num = 0;
	xcomdata->send_num = 0;
	xcomdata->save_vte = 0;
	xcomdata->save_format = 0;
	xcomdata->keep_send = 0;
	xcomdata->interval = 100;
	xcomdata->choose_file = -1;
		
	xcomdata->comcfg.baud = 9600;
	xcomdata->comcfg.databit = 8;
	xcomdata->comcfg.stopbit = 1;
	xcomdata->comcfg.parity = None;
	xcomdata->comcfg.flow = None;
	
	memset(xcomdata->comcfg.port, '\0', sizeof(xcomdata->comcfg.port));
	strcpy(xcomdata->comcfg.port, "/dev/ttyS0");
	memset(xcomdata->cfg_file, '\0', sizeof(xcomdata->cfg_file));
	memset(xcomdata->send_file, '\0', sizeof(xcomdata->send_file));
	memset(xcomdata->save_file, '\0', sizeof(xcomdata->save_file));
	sprintf(xcomdata->save_file, "%s/data", getenv("HOME"));
	
	xcomdata->gmain = NULL;
	xcomdata->grcv_text = NULL;
	xcomdata->gsend_text = NULL;
	xcomdata->button_save_vte = NULL;
	xcomdata->button_open_uart = NULL;
	xcomdata->ghex_show = NULL;
	xcomdata->ghex_send = NULL;
	xcomdata->grcv_num_show = NULL;
	xcomdata->gsend_num_show = NULL;
	xcomdata->gconf_parameter = NULL;
	xcomdata->gcom_stat = NULL;
	xcomdata->gbutton_send_data = NULL;
	xcomdata->gbutton_send_file = NULL;
	xcomdata->gkeep_send = NULL;
	xcomdata->ginterval = NULL;
}

void init_from_config_file(struct xcomdata *xcomdata)
{
	struct stat my_stat;
	char path[256] = {0};
	
	sprintf(path, "%s/.xgcom/.xgcom.conf", getenv("HOME"));
	printf("path: %s \n", path);
	if(stat(path, &my_stat) == 0)
		do_read_config(xcomdata, path);
	return;
}
