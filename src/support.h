/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: Support.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef Support_H_
#define Support_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "debug.h"
/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  define Q_(String) g_strip_context ((String), gettext (String))
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define Q_(String) g_strip_context ((String), (String))
#  define N_(String) (String)
#endif


enum parity {
	None,
	Odd,
	Even,
	Make,
	Space,
};
enum flow {
	NOne,
	Hardware,
	Software,
};
/*
 * The struct for the com configuration
 */
struct comcfg{
	int 			baud;			//Baud rate
	int 			databit;		//Data bits
	int				stopbit;		//Stop bits
	char 			port[16];		//The port
	enum parity 	parity;			//Parity
	enum flow		flow;			//Flow control
};
/*
 * The struct for the whole configuration
 */
struct xcomdata{
	int fd;
	int local_echo;			//local echo
	int ishex_send;			//send by hex(1) or not(0)
	int com_stat;			//the stat of the com
	int rcv_num;			//how many byte has received
	int send_num;			//how many byte has send
	int save_vte;			//save the receive data
	int save_format;		//how to save data: add(1) or cover(0)
	int keep_send;			//keep sending(1) or not(0)
	int interval;			//interval of sending
	int choose_file;		//load conf file (0) load send fiel (1)
							//save conf data (2) save vte file (3)
	struct comcfg comcfg;
	gchar		cfg_file[256];	//the path of cfg file save or load
	gchar		send_file[256];	//the path of file you want to send
	gchar		save_file[356];	//the path of file you want to save 
								//the date form com
	GtkWidget *gmain;
	GtkWidget *grcv_text;
	GtkWidget *gsend_text;
	
	GtkWidget *button_save_vte;
	GtkWidget *button_open_uart;
	
	GtkWidget *ghex_show;
	GtkWidget *ghex_send;
	GtkWidget *grcv_num_show;		//the entry for show the rcv_num
	GtkWidget *gsend_num_show;		//the entry for show the send_num
	GtkWidget *gconf_parameter;		//the config parameter of the com
	GtkWidget *gcom_stat;			//to show the stat of com: open or close
	GtkWidget *gbutton_send_file;
	GtkWidget *gbutton_send_data;
	GtkWidget *gkeep_send;
	GtkWidget *ginterval;
	
};



/*
 * Public Functions.
 */

/*
 * Call it with the toplevel widget in the component (i.e. a window/dialog),
 * or alternatively any widget in the component, and the name of the widget
 * you want returned.
 */
GtkWidget*  lookup_widget (GtkWidget *widget, const gchar *widget_name);


/* Use this function to set the directory containing installed pixmaps. */
void add_pixmap_directory (const gchar *directory);


/*
 * Private Functions.
 */

/* This is used to create the pixmaps used in the interface. */
GtkWidget*  create_pixmap (GtkWidget *widget, const gchar *filename);

/* This is used to create the pixbufs used in the interface. */
GdkPixbuf*  create_pixbuf (const gchar *filename);

/* This is used to set ATK action descriptions. */
void glade_set_atk_action_description (AtkAction *action,
					const gchar *action_name,
					const gchar *description);
					
void create_xgcom_msg(GtkWidget *mainwindow, gchar *help_msg);

#endif //Support_H_
