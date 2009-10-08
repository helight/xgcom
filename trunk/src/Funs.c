/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: Funs.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>

#include "Funs.h"
static int read_line(int fd, char *bufv);
static int do_setconfig(struct xcomdata *xcomdata, char *bufv);


void do_save_cfg_file(struct comcfg *comcfg, char *path)
{
	FILE *fd;
	
	debug_p("path:%s\n", path);
	fd = fopen(path, "w+");
	if (fd == NULL)
		perror("open file");
	fprintf(fd, "port %s\n", comcfg->port);
	fprintf(fd, "speed %d\n", comcfg->baud);
	fprintf(fd, "databit %d\n", comcfg->databit);
	fprintf(fd, "stopbit %d\n", comcfg->stopbit);
	fprintf(fd, "parity %d\n", comcfg->parity);
	fprintf(fd, "flow %d\n", comcfg->flow);
	fclose(fd);
}
void save_cfg_file(struct xcomdata *xcomdata)
{
	struct comcfg *comcfg = &(xcomdata->comcfg);
	
	debug_p("path:%s\n", xcomdata->cfg_file);
	do_save_cfg_file(comcfg, xcomdata->cfg_file);
}

int do_read_config(struct xcomdata *xcomdata, char *path)
{
	int fd = 0;
	int ret = 0;
	char bufv[256];
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return -1;
	ret = read_line(fd, bufv);
	while(ret != EOF){
		if(ret == 1){
			do_setconfig(xcomdata, bufv);
		}
		ret =  read_line(fd, bufv);
	}
	return 0;
}
int read_config(struct xcomdata *xcomdata)
{
	do_read_config(xcomdata, xcomdata->cfg_file);
	return 0;
}

void show_uart_param(struct xcomdata *xcomdata)
{
	gchar parameter[64];
	sprintf(parameter, "%s B:%d D:%d S:%d P:%d F: %d\n", 
		xcomdata->comcfg.port,
		xcomdata->comcfg.baud,
		xcomdata->comcfg.databit,
		xcomdata->comcfg.stopbit,
		xcomdata->comcfg.parity,
		xcomdata->comcfg.flow);
	debug_p(parameter);
	gtk_label_set_text(GTK_LABEL (xcomdata->gconf_parameter), parameter);
}

void message_box_for_notice(GtkWidget *window,gchar *message)
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window), 0,
				GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


static int read_line(int fd, char *bufv)
{
	int ret = 0;
	int i = 0;
	char ch = '\0';
	memset(bufv, '\0', sizeof(bufv));
	if((ret = read(fd, &ch, 1)) == 0)
		return EOF;
	while(ch != '\n' && ret != 0){
		if (ch == '#' ) {	/*if it is a comment line,skip it over*/
			while (ch != '\n' ) {
				if ((ret = read(fd,&ch,1))  == 0) {
					break;
				}
			}
			ret = read(fd,&ch,1);
		} else if (ch == ' ') {	/*if it is a space,skip to the next character*/
			if (i != 0) {
				bufv[i++] = ch;
			}
			ret = read(fd,&ch,1);
		} else if (ret != 0){	/*a valuable character,store it*/
			bufv[i++] = ch;
			ret = read(fd,&ch,1);
		}
	}
	if (ret == 0 ) {	/*end of the line,also the end of the file,return EOF*/
		bufv[i] = '\0';
		return EOF;
	} else if (i != 0) {		/*end of an valuable line*/
		bufv[i] = '\0';
		return 1;
	}
	return 0;
}

static int do_setconfig(struct xcomdata *xcomdata, char *bufv)
{
	char *ch = NULL;
	struct comcfg *comcfg = &(xcomdata->comcfg);
	
	ch = strchr(bufv, ' ');
	*ch = '\0';
	ch++;
	debug_p("%s:%s\n", bufv, ch);
	if(strcmp(bufv,"port") == 0){
		struct stat stats;
		if(stat(ch, &stats) == 0){
			strncpy(comcfg->port, ch, strlen(ch));
		} else {
			strncpy(comcfg->port, "/dev/ttyS0", strlen("/dev/ttyS0"));
		}
	}else if(strcmp(bufv,"speed") == 0){
		comcfg->baud = atoi(ch);
	}else if(strcmp(bufv,"databit") == 0){
		comcfg->databit = atoi(ch);
	}else if(strcmp(bufv,"stopbit") == 0){
		comcfg->stopbit = atoi(ch);
	}else if(strcmp(bufv,"parity") == 0){
		comcfg->parity = atoi(ch);
	}else if(strcmp(bufv,"flow") == 0){
		comcfg->flow = atoi(ch);
	}
	show_uart_param(xcomdata);
	return 0;
}
