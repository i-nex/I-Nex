#!/usr/bin/make -f

PWD 			= 	$(shell pwd)
PN 			= 	i-nex
PREFIX			= 	/usr
DOCSDIR 		= 	/share/doc/i-nex
MANDIR			= 	/share/man/man1
APP_NAME		= 	$(PN)
GIT_RV 			= 	$(shell git rev-list HEAD | wc -l)
BUILD_PACKAGE 		= 	$(shell ./build-deb)
LSB_CS 			= 	$(shell lsb_release -cs)
CC_OPTS_LIBCPUID 	= 	$(shell pkg-config libcpuid --cflags --libs)
libgl 			= 	$(shell pkg-config gl --cflags --libs)
libx11 			= 	$(shell pkg-config x11 --cflags --libs)
libxext 		= 	$(shell pkg-config xext --cflags --libs)
ARCH			=	$(shell uname -m)
GBC 			= 	/usr/bin/gbc3
GBCOPTS 		= 	-eagtpm
GBA 			= 	gba3
CC 			= 	gcc
PKG_INSTALL 		= 	apt-get install
AS_ROOT 		= 	sudo
CFLAGS 			= 	-g -Wall
bindir 			= 	$(PREFIX)/bin
INSTALL 		= 	install -m
MKDIR_P			=	mkdir -p
BUILD_SELF_EXECUTABLE 	= 	./build-selfexecutable
RM_COM 			= 	rm
RMFILE_OPT 		= 	-f
RMDIR_OPT 		= 	-Rf
COMPRESSION_SELF_LEVEL 	= 	9
MAKESELF 		= 	./makeself.sh
MAKESELF_OPT 		= 	--nowait
INSTALL_SELF_SCRIPT 	= 	./install-self
STATIC 			= 	true

ifeq ($(STATIC),true)
YESNO_LINK 		= 	-static
else
YESNO_LINK 		= 
endif

ifeq ($(ARCH),x86)
additional_confflags 	:= 	--disable-sse2
endif
ifeq ($(ARCH),x86_64)
additional_confflags 	:= 	-O2
endif

ifeq ($(LSB_CS),precise)
CC_OPTS_LIBPROCPS 	= 	-lproc
else
CC_OPTS_LIBPROCPS 	= 	$(shell pkg-config libprocps --cflags --libs)
endif

NO_COLOR		=	\033[0m
OK_COLOR		=	\033[92m
ERROR_COLOR		=	\033[91m
WARN_COLOR		=	\033[93m
ACTION_COLOR		=	\033[95m
OK_STRING		=	$(OK_COLOR)✔
ERROR_STRING		=	$(ERROR_COLOR)✖
WARN_STRING		=	$(WARN_COLOR)⚑