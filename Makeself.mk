#!/usr/bin/make -f
include i-nex.mk
self:
	$(BUILD_SELF_EXECUTABLE)
	mkdir -p inex
	mkdir -p inex$(bindir)
	mkdir -p inex$(PREFIX)/lib/gambas3/
	mkdir -p inex$(PREFIX)/share/pixmaps/
	mkdir -p inex$(PREFIX)/share/applications/
	mkdir -p inex$(PREFIX)/share/doc/i-nex/
	mkdir -p inex$(PREFIX)/share/i-nex/pastebinit/
	mkdir -p inex$(PREFIX)/share/i-nex/pastebinit/pastebin.d/
	chmod +x i-nex
	chmod +x i-nex-edid
	chmod +x i-nex-cpuid
	chmod +x i-nex-usage
	chmod +x i-nex-cpusage
	chmod +x i-nex-glinfo
	chmod +x i-nex-uname
	chmod +x debian/i-nex-lspci
	$(INSTALL) 0755 i-nex inex$(bindir)
	$(INSTALL) 0755 i-nex-edid inex$(bindir)
	$(INSTALL) 0755 i-nex-cpuid inex$(bindir)
	$(INSTALL) 0755 i-nex-usage inex$(bindir)
	$(INSTALL) 0755 i-nex-cpusage inex$(bindir)
	$(INSTALL) 0755 i-nex-glinfo inex$(bindir)
	$(INSTALL) 0755 i-nex-uname inex$(bindir)
	$(INSTALL) 0755 src/i-nex/i-nex.gambas inex$(bindir)
	$(INSTALL) 0755 pixmaps/i-nex-128.png inex$(PREFIX)/share/pixmaps/
	$(INSTALL) 0755 debian/i-nex.desktop inex$(PREFIX)/share/applications/
	$(INSTALL) 0755 debian/check_kernel inex$(PREFIX)/bin/
	$(INSTALL) 0755 debian/i-nex-lspci inex$(PREFIX)/bin/
	$(INSTALL) 0755 pastebin.d/* inex$(PREFIX)/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit inex$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml inex$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf inex$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0775 usr/bin/gbx3 inex$(PREFIX)/bin/gbx3
	$(INSTALL) 0775 usr/bin/gbr3 inex$(PREFIX)/bin/gbr3
	$(INSTALL) 0775 usr/lib/gambas3/gb.debug.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.desktop.gambas inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.desktop.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.draw.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.eval.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.form.gambas inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.form.stock.gambas inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.geom.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gtk.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.base.gambas inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.opengl.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.gui.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.image.so inex$(PREFIX)/lib/gambas3/
	$(INSTALL) 0775 usr/lib/gambas3/gb.qt4.so inex$(PREFIX)/lib/gambas3/
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
	$(RM_COM) $(RMDIR_OPT) `find . -name ".gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.deb"`
	$(RM_COM) $(RMFILE_OPT) index.html
	$(RM_COM) $(RMFILE_OPT) i-nex.run
	$(RM_COM) $(RMDIR_OPT) inex
	$(RM_COM) $(RMDIR_OPT) usr
	
deb: build-pixmaps
	$(AS_ROOT) $(PKG_INSTALL) $(dependency_build)
	$(BUILD_PACKAGE)