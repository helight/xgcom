/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License.
 *
 * file name: MenuFace.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifndef MenuFace_H_
#define MenuFace_H_

#include <stdlib.h>
#include <gtk/gtk.h>
#include "support.h"

GtkWidget* create_menu (GtkWidget *Xcomtool, GtkWidget *main_vbox, 
			GtkAccelGroup *accel_group, gpointer data);
			
#endif /* MenuFace_H_ */
