#!/usr/bin/make -f
GIT_RV = $(shell git rev-list HEAD | wc -l)
BUILD_PACKAGE = $(shell ./build-deb)
PKG_INSTALL = apt-get install
AS_ROOT = sudo
CFLAGS = -g -Wall
LSB_CS = $(shell lsb_release -cs)
CC_OPTS_LIBCPUID = $(shell pkg-config libcpuid --cflags --libs)
GBC = /usr/bin/gbc3
GBCOPTS = -eagtpmv
GBA = gba3
CC = gcc
ARCH=$(shell uname -m)
bindir ?= /usr/bin
INSTALL = install -m
bzr_revision = 
BUILD_SELF_EXECUTABLE = ./build-selfexecutable
RM_COM = rm
RMFILE_OPT = -f
RMDIR_OPT = -Rf
COMPRESSION_SELF_LEVEL = 9
MAKESELF = ./makeself.sh
MAKESELF_OPT = --nowait
APP_NAME= I-Nex
INSTALL_SELF_SCRIPT = ./install-self
ifeq ($(ARCH),x86)
additional_confflags := --disable-sse2
endif
ifeq ($(ARCH),x86_64)
additional_confflags := -O2
endif
ifeq ($(LSB_CS),precise)
CC_OPTS_LIBPROCPS = -lproc
else
CC_OPTS_LIBPROCPS = $(shell pkg-config libprocps --cflags --libs)
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

make:
	@printf "\033[1;31mCompile edid-decode as inex-decode \033[0m$1\n"
	$(CC) -o inex-edid edid-decode.c $(CFLAGS) $(additional_confflags)
	$(CC) -o inex-cpuid cpu.c -static $(CC_OPTS_LIBCPUID) $(additional_confflags)
	$(CC) -o inex-usage free.c -static $(CC_OPTS_LIBPROCPS) $(additional_confflags)
	$(CC) -o inex-cpusage cpusage.c $(additional_confflags)
	$(CC) -o inex-glinfo glinfo.c -O2 -lX11 -lGL -lXext
	@printf "\033[1;31mCompile src/i-nex stage 1 \033[0m$1\n"
	$(GBC) $(GBCOPTS) src/i-nex
	@printf "\033[1;31mCompile src/i-nex stage 2 \033[0m$1\n"
	$(GBA) src/i-nex
	$(MAKE) -C pixmaps
	
deb:
	
	$(AS_ROOT) $(PKG_INSTALL) $(dependency_build)
	$(BUILD_PACKAGE)
	$(MAKE) -C pixmaps
	
self:
	$(BUILD_SELF_EXECUTABLE)
	mkdir -p inex
	mkdir -p inex$(bindir)
	mkdir -p inex/usr/lib/gambas3/
	mkdir -p inex/usr/share/pixmaps/
	mkdir -p inex/usr/share/applications/
	mkdir -p inex/usr/share/doc/i-nex/
	mkdir -p inex/usr/share/i-nex/pastebinit/
	mkdir -p inex/usr/share/i-nex/pastebinit/pastebin.d/
	chmod +x i-nex
	chmod +x inex-edid
	chmod +x inex-cpuid
	chmod +x inex-usage
	chmod +x inex-cpusage
	chmod +x inex-glinfo
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	$(INSTALL) 0755 i-nex inex$(bindir)
	$(INSTALL) 0755 inex-edid inex$(bindir)
	$(INSTALL) 0755 inex-cpuid inex$(bindir)
	$(INSTALL) 0755 inex-usage inex$(bindir)
	$(INSTALL) 0755 inex-cpusage inex$(bindir)
	$(INSTALL) 0755 inex-glinfo inex$(bindir)
	$(INSTALL) 0755 src/i-nex/i-nex.gambas inex$(bindir)
	$(INSTALL) 0755 pixmaps/pixmaps/i-nex.xpm inex/usr/share/pixmaps/
	$(INSTALL) 0755 debian/i-nex.desktop inex/usr/share/applications/
	$(INSTALL) 0755 debian/check_kernel inex/usr/bin/
	$(INSTALL) 0755 debian/i-nex-lspci inex/usr/bin/
	$(INSTALL) 0755 I-Nex.LICENSE inex/usr/share/doc/i-nex/
	$(INSTALL) 0755 Pastebinit.LICENSE inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebin.d/* inex/usr/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 README inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0775 usr/bin/gbx3 inex/usr/bin/gbx3
	$(INSTALL) 0775 usr/bin/gbr3 inex/usr/bin/gbr3
	$(INSTALL) 0775 usr/lib/gambas3/gb.debug.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.desktop.gambas inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.desktop.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.draw.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.eval.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.form.gambas inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.form.stock.gambas inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.geom.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gtk.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.base.gambas inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.opengl.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.image.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.qt4.so inex/usr/lib/gambas3/
	$(INSTALL) 0775 install-self inex/install-self 
	$(INSTALL) 0775 install-self-inex inex/install-self-inex
	chmod +x inex/install-self
	chmod +x inex/install-self-inex
	@if [ -e "/usr/bin/pbzip2" ];then \
	printf "\033[1;31m:: \033[0m$1\n" & $(MAKESELF) $(MAKESELF_OPT) --pbzip2 --complevel $(COMPRESSION_SELF_LEVEL) ./inex i-nex.$(ARCH)_git$(GIT_RV).pbzip2.run $(APP_NAME) $(INSTALL_SELF_SCRIPT); \
	fi
	
	@if [ -e "/usr/bin/compress" ];then \
	printf "\033[1;31m:: \033[0m$1\n" & $(MAKESELF) $(MAKESELF_OPT) --compress --complevel $(COMPRESSION_SELF_LEVEL) ./inex i-nex.$(ARCH)_git$(GIT_RV).unixcompress.run $(APP_NAME) $(INSTALL_SELF_SCRIPT); \
	fi
	
	@if [ -e "/usr/bin/xz" ];then \
	printf "\033[1;31m:: \033[0m$1\n" & $(MAKESELF) $(MAKESELF_OPT) --xz --complevel $(COMPRESSION_SELF_LEVEL) ./inex i-nex.$(ARCH)_git$(GIT_RV).xz.run $(APP_NAME) $(INSTALL_SELF_SCRIPT); \
	fi
	
	@if [ -e "/bin/gzip" ];then \
	printf "\033[1;31m:: \033[0m$1\n" & $(MAKESELF) $(MAKESELF_OPT) --gzip --complevel $(COMPRESSION_SELF_LEVEL) ./inex i-nex.$(ARCH)_git$(GIT_RV).gzip.run $(APP_NAME) $(INSTALL_SELF_SCRIPT); \
	fi
	
	@if [ -e "/bin/bzip2" ];then \
	printf "\033[1;31m:: \033[0m$1\n" & $(MAKESELF) $(MAKESELF_OPT) --bzip2 --complevel $(COMPRESSION_SELF_LEVEL) ./inex i-nex.$(ARCH)_git$(GIT_RV).bzip2.run $(APP_NAME) $(INSTALL_SELF_SCRIPT); \
	fi
	mv ./*.run ../
	
clean:

	$(RM_COM) $(RMFILE_OPT) inex-edid
	$(RM_COM) $(RMFILE_OPT) inex-cpuid
	$(RM_COM) $(RMFILE_OPT) inex-usage
	$(RM_COM) $(RMFILE_OPT) inex-cpusage
	$(RM_COM) $(RMFILE_OPT) inex-glinfo
	$(RM_COM) $(RMDIR_OPT) `find . -name ".gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name ".directory"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.deb"`
	$(RM_COM) $(RMFILE_OPT) index.html
	$(RM_COM) $(RMFILE_OPT) i-nex.run
	$(RM_COM) $(RMFILE_OPT) src/i-nex/.lang/*.pot
	$(RM_COM) $(RMFILE_OPT) src/i-nex/.lang/*.po
	$(RM_COM) $(RMFILE_OPT) src/i-nex/.lang/*.mo
	$(RM_COM) $(RMDIR_OPT) src/i-nex/.gambas
	$(RM_COM) $(RMDIR_OPT) debian/files
	$(RM_COM) $(RMDIR_OPT) debian/i-nex
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.debhelper.log
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.postinst.debhelper
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.postrm.debhelper
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.substvars
	$(RM_COM) $(RMDIR_OPT) debian/changelog1
	$(RM_COM) $(RMDIR_OPT) inex
	$(RM_COM) $(RMDIR_OPT) usr
	$(MAKE) -C pixmaps clean
	
install:
	mkdir -p $(DESTDIR)$(bindir)
	mkdir -p $(DESTDIR)/usr/share/pixmaps/
	mkdir -p $(DESTDIR)/usr/share/applications/
	mkdir -p $(DESTDIR)/usr/share/doc/i-nex/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	chmod +x i-nex
	chmod +x inex-edid
	chmod +x inex-cpuid
	chmod +x inex-usage
	chmod +x inex-cpusage
	chmod +x inex-glinfo
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	$(INSTALL) 0755 i-nex $(DESTDIR)$(bindir)
	$(INSTALL) 0755 inex-edid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 inex-cpuid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 inex-usage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 inex-cpusage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 src/i-nex/i-nex.gambas $(DESTDIR)$(bindir)
	$(INSTALL) 0755 debian/i-nex.desktop $(DESTDIR)/usr/share/applications/
	$(INSTALL) 0755 debian/check_kernel $(DESTDIR)/usr/bin/
	$(INSTALL) 0755 debian/i-nex-lspci $(DESTDIR)/usr/bin/
	$(INSTALL) 0755 I-Nex.LICENSE $(DESTDIR)/usr/share/doc/i-nex/
	$(INSTALL) 0755 Pastebinit.LICENSE $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebin.d/* $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 README $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(MAKE) -C pixmaps install
	$(MAKE) -C changelogs install
	
uninstall:

	rm $(DESTDIR)$(bindir)/i-nex
	rm $(DESTDIR)$(bindir)/inex-edid
	rm $(DESTDIR)$(bindir)/inex-cpuid
	rm $(DESTDIR)$(bindir)/inex-usage
	rm $(DESTDIR)$(bindir)/inex-cpusage
	rm $(DESTDIR)$(bindir)/inex-glinfo
	rm $(DESTDIR)$(bindir)/i-nex.gambas
	rm $(DESTDIR)/usr/share/pixmaps/i-nex.xpm
	rm $(DESTDIR)/usr/share/applications/i-nex.desktop
	rm $(DESTDIR)$(bindir)/check_kernel
	rm $(DESTDIR)$(bindir)/i-nex-lspci
	$(RM_COM) $(RMDIR_OPT) $(DESTDIR)/usr/share/doc/i-nex
	$(RM_COM) $(RMDIR_OPT) $(DESTDIR)/usr/share/i-nex
	
rmgambas:

	$(RM_COM) $(RMFILE_OPT) /usr/bin/gbx3
	$(RM_COM) $(RMFILE_OPT) /usr/bin/gbr3
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.debug.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.desktop.gambas
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.desktop.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.draw.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.eval.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.form.gambas
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.form.stock.gambas
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.geom.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.gtk.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.gui.base.gambas
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.gui.opengl.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.gui.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.image.so
	$(RM_COM) $(RMFILE_OPT) /usr/lib/gambas3/gb.qt4.so