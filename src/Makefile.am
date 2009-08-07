## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = xgcom

xgcom_SOURCES = \
	main.c \
	support.c support.h \
	MainWindow.c MainWindow.h \
	FootFace.c FootFace.h \
	MenuFace.c MenuFace.h \
	MenuCall.c MenuCall.h \
	RightVboxFace.c RightVboxFace.h \
	LeftVboxFace.c LeftVboxFace.h \
	LeftVboxCall.c LeftVboxCall.h \
	About.c About.h \
	CfgFace.c Cfg.h \
	Serie.c Serie.h \
	SendFile.c SendFile.h \
	Funs.c Fun.h

xgcom_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

