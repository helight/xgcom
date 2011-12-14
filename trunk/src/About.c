/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: About.c
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <gtk/gtk.h>
#include "About.h"
void
on_close_ascii_clicked (GtkButton *button, gpointer user_data);


GtkWidget* create_about_xgcom (GtkWidget *main_window)
{
	GtkWidget *about_xgcom;
	GdkPixbuf *about_xgcom_icon_pixbuf;
	GtkWidget *dialog_vbox;
	GtkWidget *vbox_xgcom;
	GtkWidget *image_photo;
	GtkWidget *label_note;
	GtkWidget *label_author;
	GtkWidget *button_close;
	GtkWidget *dialog_action_area;
	GtkWidget *close_about;

	about_xgcom = gtk_dialog_new_with_buttons("About XGCom", 
	GTK_WINDOW(main_window), GTK_DIALOG_DESTROY_WITH_PARENT,NULL);
	gtk_window_set_type_hint (GTK_WINDOW (about_xgcom), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	about_xgcom_icon_pixbuf = create_pixbuf ("xgcom.png");
	if (about_xgcom_icon_pixbuf)
	{
		gtk_window_set_icon (GTK_WINDOW (about_xgcom), about_xgcom_icon_pixbuf);
		gdk_pixbuf_unref (about_xgcom_icon_pixbuf);
	}

	dialog_vbox = GTK_DIALOG (about_xgcom)->vbox;
	gtk_widget_show (dialog_vbox);

	vbox_xgcom = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox_xgcom);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), vbox_xgcom, TRUE, TRUE, 0);

	image_photo = create_pixmap (about_xgcom, "xgcom.png");
	gtk_widget_show (image_photo);
	gtk_box_pack_start (GTK_BOX (vbox_xgcom), image_photo, TRUE, TRUE, 0);

	label_note = gtk_label_new (_("<b>XGCom (0.04)</b>"));
	gtk_widget_show (label_note);
	gtk_box_pack_start (GTK_BOX (vbox_xgcom), label_note, FALSE, FALSE, 0);
	gtk_label_set_use_markup (GTK_LABEL (label_note), TRUE);

	label_author = gtk_label_new (_("XGCom is a open source software.\nLicensed under the GNU GPL v2\nCopyright     Helight.xu@gmail.com"));
	gtk_widget_show (label_author);
	gtk_box_pack_start (GTK_BOX (vbox_xgcom), label_author, FALSE, FALSE, 0);

	button_close = gtk_button_new_with_mnemonic (_("http://zhwen.org"));
	gtk_widget_show (button_close);
	gtk_box_pack_start (GTK_BOX (vbox_xgcom), button_close, FALSE, FALSE, 0);
	gtk_button_set_relief (GTK_BUTTON (button_close), GTK_RELIEF_NONE);

	dialog_action_area = GTK_DIALOG (about_xgcom)->action_area;
		gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_SPREAD);
	gtk_widget_show (dialog_action_area);

	close_about = gtk_button_new_from_stock ("gtk-close");
	gtk_widget_show (close_about);
	gtk_dialog_add_action_widget (GTK_DIALOG (about_xgcom), close_about, GTK_RESPONSE_CLOSE);
	GTK_WIDGET_SET_FLAGS (close_about, GTK_CAN_DEFAULT);

	g_signal_connect ((gpointer) button_close, "clicked",
		G_CALLBACK (on_button_link_clicked), NULL);
	g_signal_connect ((gpointer) close_about, "clicked",
		G_CALLBACK (on_close_about_clicked), about_xgcom);

	gtk_widget_grab_focus (button_close);
	return about_xgcom;
}

void
on_close_about_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_about = (GtkWidget *)user_data;
	gtk_widget_destroy(GTK_WIDGET(window_about));
}


void
on_button_link_clicked (GtkButton *button, gpointer user_data)
{
	gchar tmp[80];
	g_snprintf(tmp, 80, "firefox http://zhwen.org & >/dev/null");
	system(tmp);
}

gchar buffer[] = {
		"Decimal	Hex	Binary	      Value\n"
		"000          000    00000000      NUL\n"
		"001          001    00000001      SOH\n"
		"002          002    00000010      STX\n"
		"003          003    00000011      ETX\n"
		"004          004    00000100      EOT\n"
		"005          005    00000101      ENQ\n"
		"006          006    00000110      ACK\n"
		"007          007    00000111      BEL\n"
		"008          008    00001000      BS \n"
		"009          009    00001001  HT \n"
		"010          00A    00001010  LF \n"
		"011          00B 	00001011  VT \n"
		"012          00C 	00001100  FF \n"
		"013          00D 	00001101  CR \n"
		"014          00E 	00001110  SO \n"
		"015          00F 	00001111  SI \n"
		"016          010    00010000       DLE \n"
		"017          011    00010001      DC1\n"
		"018          012    00010010      DC2 \n"
		"019          013    00010011      DC3\n"
		"020          014    00010100      DC4 \n"
		"021          015    00010101      NAK \n"
		"022          016    00010110      SYN \n"
		"023          017    00010111      ETB \n"
		"024          018    00011000      CAN \n"
		"025          019    00011001      EM \n"
		"026          01A 	00011010      SUB \n"
		"027          01B 	00011011      ESC \n"
		"028          01C 	00011100      FS \n"
		"029          01D 	00011101      GS \n"
		"030          01E 	00011110      RS \n"
		"031          01F 	00011111      US \n"
		"032          020    00100000      SP \n"
		"033          021    00100001      ! \n"
		"034          022    00100010      \" \n"
		"035          023    00100011      # \n"
		"036          024    00100100      $ \n"
		"037          025    00100101      % \n"
		"038          026    00100110      & \n"
		"039          027    00100111      ' \n"
		"040          028    00101000      ( \n"
		"041          029    00101001      ) \n"
		"042          02A 	00101010      * \n"
		"043          02B 	00101011      + \n"
		"044          02C 	00101100      , \n"
		"045          02D 	00101101      - \n"
		"046          02E 	00101110      . \n"
		"047          02F 	00101111  / \n"
		"048          030    00110000      0\n"
		"049          031    00110001      1\n"
		"050          032    00110010      2\n"
		"051          033    00110011      3\n"
		"052          034    00110100  4\n"
		"053          035    00110101  5\n"
		"054          036    00110110  6\n"
		"055          037    00110111  7\n"
		"056          038    00111000  8\n"
		"057          039    00111001  9\n"
		"058          03A 	00111010  :\n"
		"059          03B 	00111011  ;\n"
		"060          03C 	00111100  <\n"
		"061          03D 	00111101  =\n"
		"062          03E 	00111110  >\n"
		"063          03F 	00111111  ?\n"
		"064          040    01000000  @\n"
		"065          041    01000001  A\n"
		"066          042    01000010  B\n"
		"067          043    01000011  C\n"
		"068          044    01000100  D\n"
		"069          045    01000101  E\n"
		"070          046    01000110  F\n"
		"071          047    01000111  G\n"
		"072          048    01001000  H\n"
		"073          049    01001001  I\n"
		"074          04A 	01001010  J\n"
		"075          04B 	01001011  K\n"
		"076          04C 	01001100  L\n"
		"077          04D 	01001101  M\n"
		"078          04E 	01001110  N\n"
		"079          04F 	01001111  O\n"
		"080          050    01010000  P\n"
		"081          051    01010001  Q\n"
		"082          052    01010010  R\n"
		"083          053    01010011  S\n"
		"084          054    01010100  T\n"
		"085          055    01010101  U\n"
		"086          056    01010110  V\n"
		"087          057    01010111  W\n"
		"088          058    01011000  X\n"
		"089          059    01011001  Y\n"
		"090          05A 	01011010  Z\n"
		"091          05B 	01011011  [ \n"
		"092          05C 	01011100  \ \n"
		"093          05D 	01011101  ] \n"
		"094          05E 	01011110  ^ \n"
		"095          05F 	01011111  _ \n"
		"096          060    01100000  `\n"
		"097          061    01100001  a\n"
		"098          062    01100010  b\n"
		"099          063    01100011  c\n"
		"100          064    01100100  d\n"
		"101          065    01100101  e\n"
		"102          066    01100110  f\n"
		"103          067    01100111  g\n"
		"104          068    01101000  h\n"
		"105          069    01101001  i\n"
		"106          06A 	01101010  j\n"
		"107          06B 	01101011  k\n"
		"108          06C 	01101100  l\n"
		"109          06D 	01101101  m\n"
		"110          06E 	01101110  n\n"
		"111          06F 	01101111      o\n"
		"112          070    01110000  p\n"
		"113          071    01110001  q\n"
		"114          072    01110010  r\n"
		"115          073    01110011  s\n"
		"116          074    01110100  t\n"
		"117          075    01110101  u\n"
		"118          076    01110110  v\n"
		"119          077    01110111  w\n"
		"120          078    01111000  x\n"
		"121          079    01111001  y\n"
		"122          07A 	01111010  z\n"
		"123          07B 	01111011  { \n"
		"124          07C 	01111100  | \n"
		"125          07D 	01111101  } \n"
		"126          07E 	01111110  ~ \n"
		"127          07F 	01111111  DEL\n"
	};

GtkWidget* create_ascii_table (void)
{
	GtkWidget *ascii_table;
	GtkWidget *ascii_vbox;
	GtkWidget *scrolledwindow_ascii;
	GtkWidget *text_ascii;
	GtkWidget *dialog_action_area;
	GtkWidget *close_ascii;
	GtkTextBuffer *buff = NULL;

	ascii_table = gtk_dialog_new ();
	gtk_widget_set_size_request (ascii_table, 320, 400);
	gtk_window_set_title (GTK_WINDOW (ascii_table), _("ASCII --- TABLE"));
	gtk_window_set_destroy_with_parent (GTK_WINDOW (ascii_table), TRUE);
	gtk_window_set_type_hint (GTK_WINDOW (ascii_table), GDK_WINDOW_TYPE_HINT_DIALOG);

	ascii_vbox = GTK_DIALOG (ascii_table)->vbox;
	gtk_widget_show (ascii_vbox);

	scrolledwindow_ascii = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolledwindow_ascii);
	gtk_box_pack_start (GTK_BOX (ascii_vbox), scrolledwindow_ascii, TRUE, TRUE, 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow_ascii), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow_ascii), GTK_SHADOW_IN);

	text_ascii = gtk_text_view_new ();
	gtk_widget_show (text_ascii);
	gtk_container_add (GTK_CONTAINER (scrolledwindow_ascii), text_ascii);

	dialog_action_area = GTK_DIALOG (ascii_table)->action_area;
	gtk_widget_show (dialog_action_area);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

	close_ascii = gtk_button_new_from_stock ("gtk-close");
	gtk_widget_show (close_ascii);
	gtk_dialog_add_action_widget (GTK_DIALOG (ascii_table), close_ascii, GTK_RESPONSE_CLOSE);
	GTK_WIDGET_SET_FLAGS (close_ascii, GTK_CAN_DEFAULT);

	g_signal_connect ((gpointer) close_ascii, "clicked",
		    G_CALLBACK (on_close_ascii_clicked),
		    ascii_table);

	buff = gtk_text_view_get_buffer((GtkTextView *)text_ascii);
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buff), buffer, -1);
	return ascii_table;
}
void
on_close_ascii_clicked (GtkButton *button, gpointer user_data)
{
	GtkWidget *window_about = (GtkWidget *)user_data;
	gtk_widget_destroy(GTK_WIDGET(window_about));
}
