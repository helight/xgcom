/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: RightVboxFace.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef RightVboxFace_H_
#define RightVboxFace_H_

#include <gtk/gtk.h>
#include "support.h"

GtkWidget* create_rightvbox (GtkWidget *main_window, GtkWidget *body_hbox, 
			GtkAccelGroup *accel_group, gpointer data);
void put_text(gchar *string, guint size);
void put_hexadecimal(gchar *string, guint size);
void clear_display(void);
void save_vte_data();		
int Send_chars(char *string, int length);	
void set_local_echo();
void clean_local_echo();
#endif //#ifndef RightVboxFace_H_
