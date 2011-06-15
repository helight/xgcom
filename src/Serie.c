/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: Serie.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include <termios.h>
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
#include <vte/vte.h>
#include <pthread.h>
#include <glib.h>

#include "Serie.h"
#include "Funs.h"
#include "SendFile.h"

static int ufd = -1;
static int uart_stat = 0;
static guint callback_handler;
static struct termios termios_save;

static int is_save_vte_data = 0;
static int is_hex_show = 0;
static long data_sum = 0;
static long send_sum = 0;
static FILE *save_data_fd = NULL;

GtkWidget *rcv_num = NULL;
GtkWidget *send_num = NULL;

int open_uart(struct xcomdata *xcomdata)
{
	ufd = open(xcomdata->comcfg.port, O_RDWR | O_NOCTTY | O_NDELAY );

        if (ufd  < 0) {
                perror("Open com error:\n");
                char buff[512];
                snprintf(buff, 512, "<b>Open com error!</b>\n\n"
                "<b>Please: chmod 666 %s or make sure it's ok!</b>", xcomdata->comcfg.port);
                create_xgcom_msg(xcomdata->gmain, buff);
                return -1;
        }
        uart_stat = 1;
	printf("Open %s \n", xcomdata->comcfg.port);
	rcv_num = xcomdata->grcv_num_show;
	send_num = xcomdata->gsend_num_show;

	return 0;	
}

void check_port(struct xcomdata *xcomdata)
{
	if (ufd != -1) {
		if (uart_stat) {
			gtk_input_remove(callback_handler);
			uart_stat = 0;
		}
		tcflush(ufd, TCOFLUSH);  
		tcflush(ufd, TCIFLUSH);
		tcsetattr(ufd, TCSANOW, &termios_save);
		tcflush(ufd, TCOFLUSH);  
		tcflush(ufd, TCIFLUSH);
		close(ufd);
		ufd = -1;
	}
}

int config_uart(struct xcomdata *xcomdata)
{
	int   status, ret = 0; 
	struct termios termios_p; 
	struct comcfg *config = &(xcomdata->comcfg);
	
	check_port(xcomdata);
	ret = open_uart(xcomdata);
	if (ret < 0 )
		return -1;
	switch (config->baud) {
		case 300:
			termios_p.c_cflag =  B300;
			break;
		case 600:
			termios_p.c_cflag =  B600;
			break;
		case 1200:
			termios_p.c_cflag =  B1200;
			break;
		case 2400:
			termios_p.c_cflag =  B2400;
			break;
		case 4800:
			termios_p.c_cflag =  B4800;
			break;
		case 9600:
			termios_p.c_cflag =  B9600;
			//cfsetispeed(&termios_p, B9600);  
			//cfsetospeed(&termios_p, B9600); 
			break;
		case 19200:
			termios_p.c_cflag =  B19200;
			break;
		case 38400:
			termios_p.c_cflag =  B38400;
			break;
		case 57600:
			termios_p.c_cflag =  B57600;
			break;
		case 115200:
			termios_p.c_cflag =  B115200;
			break;
		default:
			termios_p.c_cflag =  B9600;
			break;
	}
	
	switch (config->databit) {
		case 5:
			termios_p.c_cflag |= CS5;
			break;
		case 6:
			termios_p.c_cflag |= CS6;
			break;
		case 7:
			termios_p.c_cflag |= CS7;
			break;
		case 8:
			termios_p.c_cflag |= CS8;
			break;
		default:
			termios_p.c_cflag |= CS8;
			break;
	}
	switch (config->parity) {
		case 0:
			termios_p.c_cflag &= ~PARENB; /* Clear parity enable */
			termios_p.c_iflag &= ~INPCK; /* Enable parity checking */ 
			break;
		case 1:
			termios_p.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
			//termios_p.c_iflag |= INPCK; /* Disnable parity checking */ 
			break;
		case 2:
			termios_p.c_cflag |= PARENB; /* Enable parity */
			//termios_p.c_cflag &= ~PARODD; /* 转换为偶效验*/
			//termios_p.c_iflag |= INPCK; /* Disnable parity checking */
			break;
		default:
			//termios_p.c_cflag &= ~PARENB; /* Clear parity enable */
			//termios_p.c_iflag &= ~INPCK; /* Enable parity checking */ 
			break;
	}
	switch (config->stopbit) {
		case 1:
			termios_p.c_cflag &= ~CSTOPB; 
			break;
		case 2:
			termios_p.c_cflag |= CSTOPB; 
			break;
		default:
			termios_p.c_cflag &= ~CSTOPB; 
			break;
	}
	termios_p.c_cflag |= CREAD;
	termios_p.c_iflag = IGNPAR | IGNBRK;
	
	switch (config->flow) {
		case 1:
			termios_p.c_iflag |= (IXON | IXOFF | IXANY); //Enable Software Flow Control
			break;
		case 2:
			termios_p.c_cflag |= CRTSCTS;  //Enable hardware flow control
			break;
		default:
			//termios_p.c_cflag = 0;
			termios_p.c_cflag |= CLOCAL;
			break;
	}
	
	termios_p.c_oflag = 0;
	termios_p.c_lflag = 0;
	termios_p.c_cc[VTIME] = 0;
	termios_p.c_cc[VMIN] = 1;
	
	tcsetattr(ufd, TCSANOW, &termios_p);
	tcflush(ufd, TCOFLUSH);  
	tcflush(ufd, TCIFLUSH);
	
	callback_handler = gtk_input_add_full(ufd, GDK_INPUT_READ, 
			(GdkInputFunction)read_uart, NULL, NULL, NULL);
	uart_stat = 1;

	return 0;  
}

int write_uart(char *buf, int len)
{
	int ret = 0;
	char num[32] = {0};
	
	ret = write(ufd, buf, len);
	if (ret < 0)
			perror("write:");
	debug_p("write_uart: ret = %d ufd: %d\n", ret, ufd);
	send_sum += ret;
	sprintf(num, "%d", send_sum);
	gtk_entry_set_text(GTK_ENTRY(send_num), num);
	return ret;
}

//gboolean
//read_uart (GIOChannel *source, GIOCondition condition, gpointer data)
//void read_uart(gpointer data, gint source, GdkInputCondition condition)
//void *read_uart(void *data)
int read_uart(void)
{	
	int len = 0;
	unsigned char frame[1024] = {0};	
	char num[32] = {0};

	len = read(ufd, frame, 1024);
	if (len < 0) {
		perror("read error:\n");
		return -1;
	}
	debug_p("read_uart frame:%s len: %d\n", frame, len);
	if (uart_stat == 0) return -1;
	if (is_hex_show)
		put_hexadecimal(frame, len);
	else
		put_text(frame, len);		
	if (is_save_vte_data) {
		fwrite(frame, len, 1, save_data_fd);
	}
	memset(frame,'\0',len);
	data_sum += len;
	sprintf(num, "%d", data_sum);
	gtk_entry_set_text(GTK_ENTRY(rcv_num), num);

	return 0; 
}

void close_uart()
{
	int ret = 0;
	if (callback_handler)
		gtk_input_remove(callback_handler);
	if (ufd)
		ret =close(ufd);
	debug_p("close uart 00: %d \n", ret);
	ufd = -1;
	uart_stat = 0;
	//g_source_remove (callback_handler);
	//g_io_channel_shutdown (gio, TRUE, NULL);
	//g_io_channel_unref(gio);		
}


int char_type(char ch)
{
	if (ch >='0' && ch <= '9')
		return 1;
	else if (ch >= 'a' && ch <= 'f')
		return 2;
	else if (ch >= 'A' && ch <= 'F')
		return 3;
	return 0;
}

unsigned char change(char *str)
{
	int i = 0;
	char *temp = str;
	unsigned char result;
	char ch[2];

	if (strlen(temp) == 1) {
		switch(char_type(temp[0])) {
			case 1:result = 0x0 | (*temp & 0x0f); break;
			case 2:result = 0x0 | (*temp - 87); break;
			case 3:result = 0x0 | (*temp - 55); break;
			default:result = 0x00; break;
		}
	} else {
		while (*temp) {
			switch(char_type(*temp)) {
				case 1:ch[i] = (*temp & 0x0f); break;
				case 2:ch[i] = (*temp - 87);break;
				case 3:ch[i] = (*temp - 55);break;
				default:ch[i] = 0x00; break;
			}
			temp ++;
			i++;
		}
		result = (ch[0] << 4) | ch[1];
	}
	return result;
}

int hex_send(char *text)
{
	int ret = 0; 
	unsigned char ch;
	char *ptr = text;
	char *temp = NULL;
	
	while (ptr) {
		temp = strchr(ptr, ' ');//如果有多个空格，可换成while循环
		if (temp) {
			*temp++ = '\0';
		}
		if (strlen(ptr) > 2) ptr[2] = '\0';
		ch = change(ptr);	
		ret = write_uart(&ch, 1);
		debug_p("%s:%02x\n", ptr, ch);
		ptr = temp;
	}
	return ret;
}
static inline int Send_crlf(void)
{
	char crlf_seq[2] = {'\r', '\n'};

	if (write_uart(crlf_seq, 2) != 2)
		return (-1);
	else
		return 1;
}

int Send_chars(char *string, int length)
{
	char *buffer, *start_buffer;
	int i, size_written, buf_length;
	int bytes_written = 0;

	/* Normally it never happens, but it is better not to segfault ;) */
	if (length == 0)
		return 0;

	buffer=string;

	if (length == 1) {
		if(*string == '\n' ) { //|| *string == '\r'){
			bytes_written = Send_crlf();
		} else	{
			bytes_written = write_uart(string, length);
		}
	} else {
		start_buffer = buffer;
		buf_length = 1;
		for (i = 0; i < length; i++) {
			if (*buffer == '\n' && *(buffer - 1) != '\r') {
				size_written = write_uart(start_buffer, buf_length - 1);

				if(size_written == -1)
					return bytes_written;

				size_written = Send_crlf();
				if(size_written == -1)
					return bytes_written;

				start_buffer = buffer + 1;
				buf_length = 0;
			} else if (*(buffer - 1) == '\r' && *buffer != '\n') {
				if (buf_length > 2)
					size_written = write_uart(start_buffer, buf_length - 2);
				else
					size_written =0;

				if (size_written == -1)
					return bytes_written;

				size_written = Send_crlf();
				if (size_written == -1)
					return bytes_written;

				start_buffer = buffer;
				buf_length = 1;
			}
			buffer++;
			buf_length++;
		}
		if (buf_length>1)
			bytes_written += write_uart(start_buffer, buf_length-1);
		if (start_buffer[buf_length-2] == '\r')
			bytes_written += write_uart("\n", 1);
	}

	return bytes_written;
}


void sendbreak(void)
{
	if(ufd == -1)
		return;
	else
		tcsendbreak(ufd, 0);
} 

void clean_count(void)
{
	data_sum = 0;
	send_sum = 0;
}

int save_fopen(char *file, int w)
{
	if (w)
		save_data_fd = fopen(file, "w");
	else
		save_data_fd = fopen(file, "a+");
	if (save_data_fd == NULL)
		return -1;
	return 0;
}

void save_fclose(void)
{
	fclose(save_data_fd);
}

void do_log(int log)
{
	if (log)
		is_save_vte_data = 1;
	else
		is_save_vte_data = 0;
}

void is_hex_show_data(void)
{
	if (is_hex_show) {
		is_hex_show = 0;
	} else {
		is_hex_show = 1;
	}
}

static int set_uart_tmp(struct xcomdata *xcomdata)
{
	struct termios newset;
	
	close_uart();
	
	if ((ufd = open(xcomdata->comcfg.port, O_RDWR)) == -1) 
		return -1;
		
	newset.c_cflag &= ~CBAUD;
	newset.c_cflag |= B115200;	
	
	newset.c_cflag &= ~CSIZE;
	newset.c_cflag |= CS8;
	
	newset.c_cflag &= ~CSTOPB;
	
	newset.c_cflag &= ~PARENB;
	newset.c_iflag &= INPCK;
		
	newset.c_cflag &= ~CBAUD;
	newset.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
	newset.c_oflag &= ~OPOST;
	newset.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	newset.c_cflag &= ~(CSIZE | PARENB);
	
	tcflush(ufd, TCIFLUSH);
	if (tcsetattr(ufd, TCSANOW, &newset) != 0) {
		fprintf(stderr, "Warning: set serial port error\n");
		return -1;
	}

}

static int set_uart_back(struct xcomdata *xcomdata)
{
	int ret = 0;
	
	check_port(xcomdata);

	ret = config_uart(xcomdata);	
	if (ret < 0) {
		create_xgcom_msg(xcomdata->gmain, "open com error\n");
		return ret;
	}
	return 0;
}

void send_uboot(struct xcomdata *xcomdata)
{
	GtkWidget *window_file_choose;
	unsigned char buf[256];
	char *name;
	char *last_words = "Finish sending uboot!!!\n";
	struct stat fs;
	unsigned long size;
	unsigned long i;
	int fd;
	int ret;
	
	//xcomdata->choose_file = 1;
	//window_file_choose = (GtkWidget *)create_file_choose(xcomdata);
	//gtk_widget_show (window_file_choose);
	debug_p("send_uboot file name :%s \n", xcomdata->send_file);

	set_uart_tmp(xcomdata);
	
	if ((fd = open(xcomdata->send_file, O_RDONLY)) == -1) {
		fprintf(stderr, "open file \"%s\"error\n", name);
		create_xgcom_msg(xcomdata->gmain, "open file error\n");
		return;
	}
	if (fstat(fd, &fs) == -1) {
		fprintf(stderr, "read file information error\n");
		create_xgcom_msg(xcomdata->gmain, "read file information error\n");
		return;
	}
	size = fs.st_size;
	fprintf(stderr, "size = %lu\n", size);
	int len;
	for (i = 0; i < size;) {
		memset(buf, '\0', 256);
		len = read(fd, (unsigned char *)buf, 256 - 1);
		if (len == -1) {
			fprintf(stderr, "read file error\n");
			create_xgcom_msg(xcomdata->gmain, "read file error\n");
			return;
		} else {
			write(ufd, (unsigned char *)buf, len);
		}
		i += len;
		//debug_p(buf);
	}

	fprintf(stderr, "exit i = %lu\n", i);
	close(fd);
	
	set_uart_back(xcomdata);

	debug_p(last_words);
	create_xgcom_msg(xcomdata->gmain, last_words);
}

char *getlast(char *str)
{
	char *p, *tmp;
	p = str;
	while(strchr(p, '/')){
			tmp = strchr(p, '/');
			p = tmp + 1;
	};
	return p;
}
