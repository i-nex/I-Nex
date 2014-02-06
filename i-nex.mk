#!/usr/bin/make -f
GIT_RV = 			$(shell git rev-list HEAD | wc -l)
BUILD_PACKAGE = 		$(shell ./build-deb)
LSB_CS = 			$(shell lsb_release -cs)
CC_OPTS_LIBCPUID = 		$(shell pkg-config libcpuid --cflags --libs)
libgl = 			$(shell pkg-config gl --cflags --libs)
libx11 = 			$(shell pkg-config x11 --cflags --libs)
libxext = 			$(shell pkg-config xext --cflags --libs)
ARCH=				$(shell uname -m)
GBC = 				/usr/bin/gbc3
GBCOPTS = 			-eagtpm
GBA = 				gba3
CC = 				gcc
PKG_INSTALL = 			apt-get install
AS_ROOT = 			sudo
CFLAGS = 			-g -Wall
bindir ?= 			/usr/bin
INSTALL = 			install -m
BUILD_SELF_EXECUTABLE = 	./build-selfexecutable
RM_COM = 			rm
RMFILE_OPT = 			-f
RMDIR_OPT = 			-Rf
COMPRESSION_SELF_LEVEL = 	9
MAKESELF = 			./makeself.sh
MAKESELF_OPT = 			--nowait
APP_NAME= 			I-Nex
INSTALL_SELF_SCRIPT = 		./install-self
ifeq ($(ARCH),x86)
additional_confflags := 	--disable-sse2
endif
ifeq ($(ARCH),x86_64)
additional_confflags := 	-O2
endif
ifeq ($(LSB_CS),precise)
CC_OPTS_LIBPROCPS = 		-lproc
else
CC_OPTS_LIBPROCPS = 		$(shell pkg-config libprocps --cflags --libs)
endif
dependency_build ?= git \
		    devscripts \
		    pkg-config \
		    dpkg-dev \
		    gambas3-dev \
		    gambas3-gb-image \
		    gambas3-gb-gtk \
		    gambas3-gb-form \
		    gambas3-gb-desktop \
		    gambas3-gb-form-stock \
		    dpkg \
		    grep \
		    mount \
		    procps \
		    x11-xserver-utils \
		    lsb-release \
		    bash \
		    coreutils \
		    sed \
		    pciutils \
		    x11-utils \
		    mesa-utils \
		    hostname \
		    libcpuid11 \
		    libprocps0-dev 
