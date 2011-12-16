/*
 * XGCom (Xiyou Linux Group)
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

#include "Cfg.h"
#include "Serie.h"
#include "MenuCall.h"
#include "LeftVboxFace.h"
#include "RightVboxFace.h"

void
on_send_uboot_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	send_uboot(xcomdata);
	debug_p("send_uboot\n");
}
void 
on_send_data_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	static time_t send_time = 0, tmp = 0;
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
		
	if(send_time == 0)
		time(&send_time);
	time(&tmp);	
	if ((tmp - send_time) > 1){
		debug_p("send_data by Ctrl + Enter\n");
		send_data(xcomdata);
		send_time = tmp;
	}	
}

void
on_quit_file_activate (GtkMenuItem	*menuitem, gpointer user_data)
{
	debug_p("bye world;\n");
	close_uart();
	gtk_main_quit();
}

void
on_send_break_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	sendbreak();
	debug_p("send_break\n");
}

void
on_local_echo_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	
	debug_p("local echo\n");
	if(xcomdata->local_echo){
		xcomdata->local_echo = 0;
		clean_local_echo();
		debug_p("clean local echo\n");
	} else {
		xcomdata->local_echo = 1;
		set_local_echo();
		debug_p("set local echo\n");
	}
}

void
on_config_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	GtkWidget *window_cfg = create_configuration_dialog (user_data);
	
	gtk_widget_show (window_cfg);
}

void
on_ascii_talbe_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget *window_ascii = (GtkWidget *)create_ascii_table();
	gtk_widget_show (window_ascii);
}

void
on_tools_item_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	char *ch = (char *)user_data;
	
	debug_p("on_tools_item_activate: %s\n", ch);
}

void
on_help_xgcom_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	gchar help_msg[1024];
	
	snprintf(help_msg, 1024, 
		"<b>Intro:</b>\n"
		"gui tool to help guys debug programs remotely by series port, like minicom.\n\n"
		"<b>Function</b>\n"
		"1.Send and Receive data by UART\n"
		"2.Setting up the UART(speed,data,stop,odd,data control)\n"
		"3.Save or Load the UART Setting to or from file\n"
		"4.Show data by HEX\n"
		"5.Count the date, receive or send(by bety)\n"
		"6.Save recevie date to file(append or recover)\n"
		"7.Send file by UART\n"
		"8.Send by HEX\n"
		"9.Send by interval, the time can be set\n"
		"10.Show or hide by tray\n"
		"11.Control like terminal\n"
		"12.Conf defalut configure file, xgcom start up by the defaule configure file\n"
		"13.Send data by Ctrl + Enter\n"
		"14.Echo show\n");

	create_xgcom_msg ((GtkWidget *)user_data, help_msg);
}

void
on_about_xgcom_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	GtkWidget *window_about;

	window_about = (GtkWidget *)create_about_xgcom ((GtkWidget *)user_data);
	gtk_widget_show (window_about);
}
