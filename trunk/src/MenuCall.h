/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: MenuCall.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef MenuCall_H_
#define MenuCall_H_
#include <gtk/gtk.h>
#include "support.h"

void
on_send_uboot_activate(GtkMenuItem *menuitem, gpointer user_data);

void 
on_send_data_activate(GtkMenuItem *menuitem, gpointer user_data);

void
on_local_echo_activate(GtkMenuItem *menuitem, gpointer user_data);

void
on_send_break_activate(GtkMenuItem *menuitem, gpointer user_data);

void
on_quit_file_activate (GtkMenuItem	*menuitem, gpointer user_data);

void
on_config_activate (GtkMenuItem *menuitem, gpointer user_data);

void
on_ascii_talbe_activate (GtkMenuItem *menuitem, gpointer user_data);

void
on_tools_item_activate (GtkMenuItem *menuitem, gpointer user_data);

void
on_help_xgcom_activate (GtkMenuItem *menuitem, gpointer user_data);

void
on_about_xgcom_activate (GtkMenuItem *menuitem, gpointer user_data);

#endif //MenuCall_H_
