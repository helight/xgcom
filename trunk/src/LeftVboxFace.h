/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: LeftVboxFace.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifndef LeftVboxFace_H_
#define LeftVboxFace_H_

#include <gtk/gtk.h>
#include "support.h"

GtkWidget*
create_leftvbox (GtkWidget *main_window, GtkWidget *body_hbox, 
	GtkAccelGroup *accel_group, struct xcomdata *xcomdata);

			
#endif //#ifndef LeftVboxFace_H_
