/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: About.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifndef About_H_
#define About_H_

#include <gtk/gtk.h>
#include "support.h"

GtkWidget *create_about_xnote (GtkWidget *mainwindow);
GtkWidget* create_ascii_table (void);

void
on_close_about_clicked (GtkButton *button, gpointer user_data);

void
on_button_link_clicked (GtkButton *button, gpointer user_data);

void 
on_button_close_clicked (GtkButton *button, gpointer user_data);

#endif //About_H_
