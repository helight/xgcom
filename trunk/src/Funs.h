/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: Funs.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifndef Fun_H_
#define Fun_H_

#include <gtk/gtk.h>
#include "support.h"

void do_save_cfg_file(struct comcfg *comcfg, char *path);
void save_cfg_file(struct xcomdata *xcomdata);
int do_read_config(struct xcomdata *xcomdata, char *path);
int read_config(struct xcomdata *xcomdata);
void show_uart_param(struct xcomdata *xcomdata);
void message_box_for_notice(GtkWidget *window,gchar *message);
#endif //Fun_H_
