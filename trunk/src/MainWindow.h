/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: MainWindow.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef MainWindow_H_
#define MainWindow_H_

#include <gtk/gtk.h>
#include "support.h"
GtkWidget* create_Xgcom (struct xcomdata *xcomdata);
void open_config_uart(struct xcomdata *xcomdata);
void close_uart();

gboolean
on_Xgcom_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data);
#endif //MainWindow_H_
