/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: LeftVboxFace.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#include "LeftVboxFace.h"
#include "LeftVboxCall.h"

GtkWidget*
create_leftvbox (GtkWidget *main_window, GtkWidget *body_hbox, 
	GtkAccelGroup *accel_group, struct xcomdata *xcomdata)
{
	GtkWidget *left_vbox;
	GtkWidget *left_top_vbox;
	GtkWidget *left_foot_vbox;
	
	GtkWidget *table_conf;
	GtkWidget *conf_button;
	GtkWidget *save_conf;
	GtkWidget *open_uart;
	GtkWidget *load_conf;
	GtkWidget *fixed1;
	GtkWidget *fixed2;
	GtkWidget *fixed3;
	GtkWidget *fixed4;
	GtkWidget *fixed5;
	GtkWidget *fixed6;
	GtkWidget *fixed7;
	GtkWidget *fixed8;
	GtkWidget *table_hex;
	GtkWidget *hex_show;
	GtkWidget *hbox_send;
	GtkWidget *send_num_label;
	GtkWidget *send_num;
	GtkWidget *hbox_rcv;
	GtkWidget *rcv_num_label;
	GtkWidget *rcv_num;
	GtkWidget *fixed9;
	GtkWidget *fixed10;
	GtkWidget *fixed11;
	GtkWidget *fixed12;
	GtkWidget *fixed13;
	GtkWidget *fixed14;
	GtkWidget *table_flush;
	GtkWidget *new_count;
	GtkWidget *clean_rcv_buff;
	GtkWidget *save_data;
	GtkWidget *fixed15;
	GtkWidget *fixed16;
	GtkWidget *frame_save;
	GtkWidget *alignment3;
	GtkWidget *vbox_frame_save;
	GtkWidget *add_save;
	GSList *add_save_group = NULL;
	GtkWidget *cover_save;
	GtkWidget *save_label;
	GtkWidget *table_send_file;
	GtkWidget *choose_file;
	GtkWidget *send_file;
	GtkWidget *clean_send_buff;
	GtkWidget *send_data;
	GtkWidget *fixed21;
	GtkWidget *fixed22;
	GtkWidget *fixed23;
	GtkWidget *fixed24;
	GtkWidget *fixed25;
	GtkWidget *fixed26;
	GtkWidget *fixed27;
	GtkWidget *fixed28;
	GtkWidget *table_free_space;
	GtkWidget *fixed_free_space;
	GtkWidget *table_hex_send;
	GtkWidget *hex_send;
	GtkWidget *keep_send;
	GtkWidget *hbox_interval;
	GtkWidget *time_label;
	GtkWidget *time_interval;
	GtkWidget *fixed29;
	GtkWidget *fixed30;
	GtkWidget *fixed31;
	GtkWidget *fixed32;
	GtkWidget *fixed33;
	GtkWidget *fixed34;	
	GtkWidget *left_top;
	GtkWidget *left_bottom;
	GtkWidget *button1;
  
	left_top = gtk_fixed_new();
	gtk_widget_show(left_top);
	left_vbox = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start(GTK_BOX(left_vbox), left_top, FALSE, TRUE, 0);
	//gtk_widget_set_size_request (table_conf, 120, 30);
	
	gtk_widget_show (left_vbox);
	gtk_box_pack_start (GTK_BOX (body_hbox), left_vbox, FALSE, TRUE	, 0);
	gtk_widget_set_size_request (left_vbox, 120, -1);

	left_top_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (left_top_vbox);
	gtk_box_pack_start (GTK_BOX (left_vbox), left_top_vbox, FALSE, TRUE, 0);
	
	table_conf = gtk_table_new (5, 3, FALSE);
	gtk_widget_show (table_conf);
	gtk_box_pack_start (GTK_BOX (left_top_vbox), table_conf, FALSE, FALSE, 0);
	//gtk_widget_set_size_request (table_conf, 110, 165);

	conf_button = gtk_button_new_with_mnemonic (_("Configure"));
	gtk_widget_show (conf_button);
	gtk_table_attach (GTK_TABLE (table_conf), conf_button, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (conf_button), 2);

	save_conf = gtk_button_new_with_mnemonic (_("Save Conf"));
	gtk_widget_show (save_conf);
	gtk_table_attach (GTK_TABLE (table_conf), save_conf, 1, 2, 1, 2,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (save_conf), 2);

	load_conf = gtk_button_new_with_mnemonic (_("Load Conf"));
	gtk_widget_show (load_conf);
	gtk_table_attach (GTK_TABLE (table_conf), load_conf, 1, 2, 2, 3,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (load_conf), 2);
	
	open_uart = gtk_button_new_with_mnemonic (_("Open Com"));
	gtk_widget_show (open_uart);
	gtk_table_attach (GTK_TABLE (table_conf), open_uart, 1, 2, 3, 4,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (open_uart), 2);

	clean_rcv_buff = gtk_button_new_with_mnemonic (_("Clear Rcv"));
	gtk_widget_show (clean_rcv_buff);
	gtk_table_attach (GTK_TABLE (table_conf), clean_rcv_buff, 1, 2, 4, 5,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (clean_rcv_buff), 2);
	
	fixed1 = gtk_fixed_new ();
	gtk_widget_show (fixed1);
	gtk_table_attach (GTK_TABLE (table_conf), fixed1, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed2 = gtk_fixed_new ();
	gtk_widget_show (fixed2);
	gtk_table_attach (GTK_TABLE (table_conf), fixed2, 0, 1, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed3 = gtk_fixed_new ();
	gtk_widget_show (fixed3);
	gtk_table_attach (GTK_TABLE (table_conf), fixed3, 0, 1, 2, 3,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed4 = gtk_fixed_new ();
	gtk_widget_show (fixed4);
	gtk_table_attach (GTK_TABLE (table_conf), fixed4, 0, 1, 3, 4,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (GTK_FILL), 0, 0);
		
	gtk_table_attach (GTK_TABLE (table_conf), fixed4, 0, 1, 4, 5,
		(GtkAttachOptions) (GTK_FILL), 
		(GtkAttachOptions) (GTK_FILL), 0, 0);
		
	fixed5 = gtk_fixed_new ();
	gtk_widget_show (fixed5);
	gtk_table_attach (GTK_TABLE (table_conf), fixed5, 2, 3, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed6 = gtk_fixed_new ();
	gtk_widget_show (fixed6);
	gtk_table_attach (GTK_TABLE (table_conf), fixed6, 2, 3, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed7 = gtk_fixed_new ();
	gtk_widget_show (fixed7);
	gtk_table_attach (GTK_TABLE (table_conf), fixed7, 2, 3, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed8 = gtk_fixed_new ();
	gtk_widget_show (fixed8);
	gtk_table_attach (GTK_TABLE (table_conf), fixed8, 2, 3, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
		
	gtk_table_attach (GTK_TABLE (table_conf), fixed8, 2, 3, 4, 5,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
		
	table_hex = gtk_table_new (3, 3, FALSE);
	gtk_widget_show (table_hex);
	gtk_box_pack_start (GTK_BOX (left_top_vbox), table_hex, FALSE, FALSE, 0);

	hex_show = gtk_check_button_new_with_mnemonic (_("HEX Show"));
	gtk_widget_show (hex_show);
	gtk_table_attach (GTK_TABLE (table_hex), hex_show, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (hex_show), 2);

	hbox_send = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox_send);
	gtk_table_attach (GTK_TABLE (table_hex), hbox_send, 1, 2, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	send_num_label = gtk_label_new (_("S:"));
	gtk_widget_show (send_num_label);
	gtk_box_pack_start (GTK_BOX (hbox_send), send_num_label, FALSE, FALSE, 0);

	send_num = gtk_entry_new ();
	gtk_widget_show (send_num);
	gtk_box_pack_start (GTK_BOX (hbox_send), send_num, TRUE, TRUE, 0);
	gtk_widget_set_size_request (send_num, 40, -1);
	gtk_entry_set_invisible_char (GTK_ENTRY (send_num), 9679);
	gtk_entry_set_editable(GTK_ENTRY(send_num), FALSE);
	gtk_entry_append_text (GTK_ENTRY (send_num), "0");
	
	hbox_rcv = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox_rcv);
	gtk_table_attach (GTK_TABLE (table_hex), hbox_rcv, 1, 2, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	rcv_num_label = gtk_label_new (_("R:"));
	gtk_widget_show (rcv_num_label);
	gtk_box_pack_start (GTK_BOX (hbox_rcv), rcv_num_label, FALSE, FALSE, 0);

	rcv_num = gtk_entry_new ();
	gtk_widget_show (rcv_num);
	gtk_box_pack_start (GTK_BOX (hbox_rcv), rcv_num, TRUE, TRUE, 0);
	gtk_widget_set_size_request (rcv_num, 40, -1);
	gtk_entry_set_invisible_char (GTK_ENTRY (rcv_num), 9679);
	gtk_entry_set_editable(GTK_ENTRY(rcv_num), FALSE);
	gtk_entry_append_text (GTK_ENTRY (rcv_num), "0");

	fixed9 = gtk_fixed_new ();
	gtk_widget_show (fixed9);
	gtk_table_attach (GTK_TABLE (table_hex), fixed9, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed10 = gtk_fixed_new ();
	gtk_widget_show (fixed10);
	gtk_table_attach (GTK_TABLE (table_hex), fixed10, 2, 3, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed11 = gtk_fixed_new ();
	gtk_widget_show (fixed11);
	gtk_table_attach (GTK_TABLE (table_hex), fixed11, 0, 1, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed12 = gtk_fixed_new ();
	gtk_widget_show (fixed12);
	gtk_table_attach (GTK_TABLE (table_hex), fixed12, 2, 3, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed13 = gtk_fixed_new ();
	gtk_widget_show (fixed13);
	gtk_table_attach (GTK_TABLE (table_hex), fixed13, 2, 3, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed14 = gtk_fixed_new ();
	gtk_widget_show (fixed14);
	gtk_table_attach (GTK_TABLE (table_hex), fixed14, 0, 1, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	table_flush = gtk_table_new (1, 3, FALSE);
	gtk_widget_show (table_flush);
	gtk_box_pack_start (GTK_BOX (left_top_vbox), table_flush, TRUE, TRUE, 0);
	//gtk_widget_set_size_request (table_flush, 110, 20);

	new_count = gtk_button_new_with_mnemonic (_("Recount"));
	gtk_widget_show (new_count);
	gtk_table_attach (GTK_TABLE (table_flush), new_count, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (new_count), 2);


	fixed15 = gtk_fixed_new ();
	gtk_widget_show (fixed15);
	gtk_table_attach (GTK_TABLE (table_flush), fixed15, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	
	fixed16 = gtk_fixed_new ();
	gtk_widget_show (fixed16);
	gtk_table_attach (GTK_TABLE (table_flush), fixed16, 2, 3, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
	
	frame_save = gtk_frame_new (NULL);
	gtk_widget_show (frame_save);
	gtk_box_pack_start (GTK_BOX (left_top_vbox), frame_save, FALSE, FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (frame_save), 2);
	//gtk_widget_set_size_request (frame_save, 110, 100);
	
	alignment3 = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment3);
	gtk_container_add (GTK_CONTAINER (frame_save), alignment3);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment3), 0, 0, 12, 0);
	
	vbox_frame_save = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox_frame_save);
	gtk_container_add (GTK_CONTAINER (alignment3), vbox_frame_save);

	save_data = gtk_button_new_with_mnemonic (_("Log Data"));
	gtk_widget_show (save_data);
	gtk_box_pack_start (GTK_BOX (vbox_frame_save), save_data, FALSE, FALSE, 0);
	gtk_widget_set_size_request (save_data, 50, -1);
	
	add_save = gtk_radio_button_new_with_mnemonic (NULL, _("Append"));
	gtk_widget_show (add_save);
	gtk_box_pack_start (GTK_BOX (vbox_frame_save), add_save, FALSE, FALSE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (add_save), add_save_group);
	add_save_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (add_save));

	cover_save = gtk_radio_button_new_with_mnemonic (NULL, _("Rewrite"));
	gtk_widget_show (cover_save);
	gtk_box_pack_start (GTK_BOX (vbox_frame_save), cover_save, FALSE, FALSE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (cover_save), add_save_group);
	add_save_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (cover_save));

	save_label = gtk_label_new (_("Log Data"));
	gtk_widget_show (save_label);
	gtk_frame_set_label_widget (GTK_FRAME (frame_save), save_label);
	gtk_label_set_use_markup (GTK_LABEL (save_label), TRUE);

	left_foot_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (left_foot_vbox);
	gtk_box_pack_start (GTK_BOX (left_vbox), left_foot_vbox, TRUE, FALSE, 0);
  
	table_free_space = gtk_table_new (1, 1, FALSE);
	gtk_widget_show (table_free_space);
	gtk_box_pack_start (GTK_BOX (left_foot_vbox), table_free_space, FALSE, FALSE, 0);
	
	fixed_free_space = gtk_fixed_new ();
	gtk_widget_show (fixed_free_space);
	gtk_table_attach (GTK_TABLE (fixed_free_space), fixed_free_space, 1, 1, 1, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);
		
	table_send_file = gtk_table_new (4, 3, FALSE);
	gtk_widget_show (table_send_file);
	gtk_box_pack_start (GTK_BOX (left_foot_vbox), table_send_file, FALSE, FALSE, 0);
	//gtk_widget_set_size_request (table_send_file, 110, 130);
	
	choose_file = gtk_button_new_with_mnemonic (_("Select File"));
	gtk_widget_show (choose_file);
	gtk_table_attach (GTK_TABLE (table_send_file), choose_file, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (choose_file), 2);

	send_file = gtk_button_new_with_mnemonic (_("Send File"));
	gtk_widget_show (send_file);
	gtk_table_attach (GTK_TABLE (table_send_file), send_file, 1, 2, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (send_file), 2);

	send_data = gtk_button_new_with_mnemonic (_("Send Data"));
	gtk_widget_show (send_data);
	gtk_table_attach (GTK_TABLE (table_send_file), send_data, 1, 2, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (send_data), 2);

	clean_send_buff = gtk_button_new_with_mnemonic (_("Clear Send"));
	gtk_widget_show (clean_send_buff);
	gtk_table_attach (GTK_TABLE (table_send_file), clean_send_buff, 1, 2, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);
	gtk_container_set_border_width (GTK_CONTAINER (clean_send_buff), 2);
	
	fixed21 = gtk_fixed_new ();
	gtk_widget_show (fixed21);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed21, 2, 3, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed22 = gtk_fixed_new ();
	gtk_widget_show (fixed22);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed22, 2, 3, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed23 = gtk_fixed_new ();
	gtk_widget_show (fixed23);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed23, 2, 3, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed24 = gtk_fixed_new ();
	gtk_widget_show (fixed24);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed24, 2, 3, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed25 = gtk_fixed_new ();
	gtk_widget_show (fixed25);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed25, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed26 = gtk_fixed_new ();
	gtk_widget_show (fixed26);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed26, 0, 1, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed27 = gtk_fixed_new ();
	gtk_widget_show (fixed27);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed27, 0, 1, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed28 = gtk_fixed_new ();
	gtk_widget_show (fixed28);
	gtk_table_attach (GTK_TABLE (table_send_file), fixed28, 0, 1, 3, 4,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	table_hex_send = gtk_table_new (3, 3, FALSE);
	gtk_widget_show (table_hex_send);
	gtk_box_pack_start (GTK_BOX (left_foot_vbox), table_hex_send, FALSE, FALSE, 0);
	//gtk_widget_set_size_request (table_hex_send, 110, 50);
	
	hex_send = gtk_check_button_new_with_mnemonic (_("HEX Send"));
	gtk_widget_show (hex_send);
	gtk_table_attach (GTK_TABLE (table_hex_send), hex_send, 1, 2, 0, 1,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);

	keep_send = gtk_check_button_new_with_mnemonic (_("Continual"));
	gtk_widget_show (keep_send);
	gtk_table_attach (GTK_TABLE (table_hex_send), keep_send, 1, 2, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (0), 0, 0);

	hbox_interval = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox_interval);
	//gtk_table_attach (GTK_TABLE (table_hex_send), hbox_interval, 1, 2, 2, 3,
	//	(GtkAttachOptions) (GTK_FILL),
	//	(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	gtk_table_attach (GTK_TABLE (table_hex_send), hbox_interval, 1, 2, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	time_label = gtk_label_new (_("Interval:"));
	gtk_widget_show (time_label);
	gtk_box_pack_start (GTK_BOX (hbox_interval), time_label, FALSE, FALSE, 0);

	time_interval = gtk_entry_new ();
	gtk_widget_show (time_interval);
	gtk_box_pack_start (GTK_BOX (hbox_interval), time_interval, TRUE, TRUE, 0);
	gtk_widget_set_size_request (time_interval, 40, -1);
	gtk_entry_set_invisible_char (GTK_ENTRY (time_interval), 9679);
	gtk_entry_append_text (GTK_ENTRY (time_interval), "100");

	fixed29 = gtk_fixed_new ();
	gtk_widget_show (fixed29);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed29, 0, 1, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed30 = gtk_fixed_new ();
	gtk_widget_show (fixed30);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed30, 0, 1, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed31 = gtk_fixed_new ();
	gtk_widget_show (fixed31);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed31, 0, 1, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed32 = gtk_fixed_new ();
	gtk_widget_show (fixed32);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed32, 2, 3, 0, 1,
		(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed33 = gtk_fixed_new ();
	gtk_widget_show (fixed33);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed33, 2, 3, 1, 2,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	fixed34 = gtk_fixed_new ();
	gtk_widget_show (fixed34);
	gtk_table_attach (GTK_TABLE (table_hex_send), fixed34, 2, 3, 2, 3,
		(GtkAttachOptions) (GTK_FILL),
		(GtkAttachOptions) (GTK_FILL), 0, 0);

	left_bottom = gtk_fixed_new();
	gtk_widget_show(left_bottom);
	gtk_box_pack_start(GTK_BOX(left_foot_vbox), left_bottom, TRUE, TRUE, 0);

	g_signal_connect ((gpointer) conf_button, "clicked",
		G_CALLBACK (on_conf_button_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) save_conf, "clicked",
		G_CALLBACK (on_save_conf_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) open_uart, "clicked",
		G_CALLBACK (on_open_uart_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) load_conf, "clicked",
		G_CALLBACK (on_load_conf_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) hex_show, "toggled",
		G_CALLBACK (on_hex_show_toggled),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) new_count, "clicked",
		G_CALLBACK (on_new_count_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) clean_rcv_buff, "clicked",
		G_CALLBACK (on_clean_rcv_buff_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) save_data, "clicked",
		G_CALLBACK (on_save_data_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) add_save, "toggled",
		G_CALLBACK (on_add_save_toggled),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) cover_save, "toggled",
		G_CALLBACK (on_cover_save_toggled),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) choose_file, "clicked",
		G_CALLBACK (on_choose_file_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) send_file, "clicked",
		G_CALLBACK (on_send_file_clicked),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) clean_send_buff, "clicked",
		G_CALLBACK (on_clean_send_buff_clicked), 
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) send_data, "clicked",
		G_CALLBACK (on_send_data_clicked), 
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) hex_send, "toggled",
		G_CALLBACK (on_hex_send_toggled),
		(gpointer)xcomdata);
	g_signal_connect ((gpointer) keep_send, "toggled",
		G_CALLBACK (on_keep_send_toggled),
		(gpointer)xcomdata);

	xcomdata->ghex_show = hex_show;
	xcomdata->grcv_num_show = rcv_num;
	xcomdata->gsend_num_show = send_num;
	xcomdata->button_save_vte = save_data;
	xcomdata->button_open_uart = open_uart;
	xcomdata->gbutton_send_data = send_data;
	xcomdata->gbutton_send_file = send_file;
	xcomdata->gkeep_send = keep_send;
	xcomdata->ginterval = time_interval;
	gtk_widget_set_sensitive(GTK_WIDGET(send_data), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(send_file), FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(keep_send), FALSE);
	
	//struct xcomdata *xcomdata = (struct xcomdata *)user_data;
	debug_p("left_vbox baud: %d \n", xcomdata->comcfg.baud);
	return left_vbox;
}
