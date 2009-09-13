/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: FootFace.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef FootFace_H_
#define FootFace_H_

#include <gtk/gtk.h>
#include "support.h"


GtkWidget*
create_foot (GtkWidget *Xcomtool, GtkWidget *main_vbox, 
		struct xcomdata *xcomdata);
				
				
#endif /* FootFace_H_ */
