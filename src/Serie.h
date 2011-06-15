/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: Serie.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */


#ifndef Serie_H_
#define Serie_H_

#include <gtk/gtk.h>
#include "support.h"
int config_uart(struct xcomdata *xcomdata);

void check_port(struct xcomdata *xcomdata);
int open_uart(struct xcomdata *xcomdata);
int write_uart(char *buf, int len);
int read_uart(void);
int hex_send(char * text);
void save_vte_data_to_file(char *ch, char *path);
int char_type(char ch);
unsigned char change(char *str);
char *getlast(char *str);

void clean_count();
int save_fopen(char *file, int w);
void save_fclose(void);
void do_log(int log);
void is_hex_show_data(void);
void send_uboot(struct xcomdata *xcomdata);

#endif //Serie_H_


