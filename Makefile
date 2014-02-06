#!/usr/bin/make -f
include i-nex.mk
make: build-inex
build-inex:
	cd ./src && ./configure --bindir=$(bindir)
	$(MAKE) -C pixmaps
	$(MAKE) -C JSON
	$(MAKE) -C src
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
	chmod +x i-nex-edid
	chmod +x i-nex-cpuid
	chmod +x i-nex-usage
	chmod +x i-nex-cpusage
	chmod +x i-nex-glinfo
	chmod +x i-nex-uname
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	$(INSTALL) 0755 i-nex inex$(bindir)
	$(INSTALL) 0755 i-nex-edid inex$(bindir)
	$(INSTALL) 0755 i-nex-cpuid inex$(bindir)
	$(INSTALL) 0755 i-nex-usage inex$(bindir)
	$(INSTALL) 0755 i-nex-cpusage inex$(bindir)
	$(INSTALL) 0755 i-nex-glinfo inex$(bindir)
	$(INSTALL) 0755 i-nex-uname inex$(bindir)
	$(INSTALL) 0755 src/i-nex/i-nex.gambas inex$(bindir)
	$(INSTALL) 0755 pixmaps/i-nex-128.png inex/usr/share/pixmaps/
	$(INSTALL) 0755 debian/i-nex.desktop inex/usr/share/applications/
	$(INSTALL) 0755 debian/check_kernel inex/usr/bin/
	$(INSTALL) 0755 debian/i-nex-lspci inex/usr/bin/
	$(INSTALL) 0755 pastebin.d/* inex/usr/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit inex/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml inex/usr/share/i-nex/pastebinit/
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

distclean: clean
clean:

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
	$(MAKE) -C src distclean
	$(MAKE) -C pixmaps clean
	$(MAKE) -C JSON clean
	
install:
	mkdir -p $(DESTDIR)$(bindir)
	mkdir -p $(DESTDIR)/usr/share/pixmaps/
	mkdir -p $(DESTDIR)/usr/share/applications/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	chmod +x i-nex
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	$(INSTALL) 0755 i-nex $(DESTDIR)$(bindir)
	$(INSTALL) 0755 debian/i-nex.desktop $(DESTDIR)/usr/share/applications/
	$(INSTALL) 0755 debian/check_kernel $(DESTDIR)/usr/bin/
	$(INSTALL) 0755 debian/i-nex-lspci $(DESTDIR)/usr/bin/
	$(INSTALL) 0755 pastebin.d/* $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 README $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf $(DESTDIR)/usr/share/i-nex/pastebinit/
	$(MAKE) -C pixmaps install
	$(MAKE) -C changelogs install
	$(MAKE) -C manpages install
	$(MAKE) -C docs install
	$(MAKE) -C JSON install
	$(MAKE) -C src install 
	
uninstall:

	rm $(DESTDIR)$(bindir)/i-nex
	rm $(DESTDIR)$(bindir)/i-nex-edid
	rm $(DESTDIR)$(bindir)/i-nex-cpuid
	rm $(DESTDIR)$(bindir)/i-nex-usage
	rm $(DESTDIR)$(bindir)/i-nex-cpusage
	rm $(DESTDIR)$(bindir)/i-nex-glinfo
	rm $(DESTDIR)$(bindir)/i-nex-uname
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