/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: FootFace.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include "FootFace.h"

GtkWidget*
create_foot (GtkWidget *main_window, GtkWidget *main_vbox, struct xcomdata *xcomdata)
{
	GtkWidget *foot_hbox;
	GtkWidget *conf_label;
	GtkWidget *conf_parameter;
	GtkWidget *com_label;
	GtkWidget *com_stat;
	
	foot_hbox = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (foot_hbox);
	gtk_box_pack_start (GTK_BOX (main_vbox), foot_hbox, FALSE, FALSE, 0);

	conf_label = gtk_label_new (_("Parameter: "));
	gtk_widget_show (conf_label);
	gtk_box_pack_start (GTK_BOX (foot_hbox), conf_label, FALSE, FALSE, 0);
	gtk_widget_set_size_request (conf_label, 80, 20);

	conf_parameter = gtk_label_new (_("com"));
	gtk_widget_show (conf_parameter);
	gtk_box_pack_start (GTK_BOX (foot_hbox), conf_parameter, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (conf_parameter), 0, 0.5);
	gtk_widget_set_size_request (conf_parameter, -1, 20);
	
	com_label = gtk_label_new (_("State: "));
	gtk_widget_show (com_label);
	gtk_box_pack_start (GTK_BOX (foot_hbox), com_label, FALSE, FALSE, 0);
	gtk_widget_set_size_request (com_label, 50, 20);
	gtk_label_set_line_wrap (GTK_LABEL (com_label), TRUE);

	com_stat = gtk_label_new (_("close"));
	gtk_widget_show (com_stat);
	gtk_box_pack_start (GTK_BOX (foot_hbox), com_stat, FALSE, FALSE, 0);
	gtk_widget_set_size_request (com_stat, 60, 20);
	
	xcomdata->gconf_parameter = conf_parameter;
	xcomdata->gcom_stat = com_stat;
	return foot_hbox;
}
