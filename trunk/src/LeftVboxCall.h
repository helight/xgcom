/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: LeftVboxCall.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifndef LeftVboxCall_H_
#define LeftVboxCall_H_
#include <gtk/gtk.h>
#include "support.h"

void
on_conf_button_clicked (GtkButton *button, gpointer user_data);

void
on_save_conf_clicked (GtkButton *button, gpointer user_data);

void
on_open_uart_clicked (GtkButton *button, gpointer user_data);

void
on_load_conf_clicked (GtkButton *button, gpointer user_data);

void
on_hex_show_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_new_count_clicked (GtkButton *button, gpointer user_data);

void
on_clean_rcv_buff_clicked  (GtkButton *button, gpointer user_data);

void
on_save_data_clicked (GtkButton *button, gpointer user_data);

void
on_choose_file_clicked (GtkButton *button, gpointer user_data);

void
on_send_file_clicked (GtkButton *button, gpointer user_data);

void
on_clean_send_buff_clicked (GtkButton *button, gpointer user_data);

void
on_send_data_clicked (GtkButton *button, gpointer user_data);

void
on_hex_send_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_keep_send_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_add_save_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_cover_save_toggled (GtkToggleButton *togglebutton, gpointer user_data);

#endif //LeftVboxCall_H_
