#!/usr/bin/make -f

include i-nex.mk
make: build-inex build-json build-pixmaps

install: install-create-dirs install-pastebinit-and-other \
	 install-pixmaps install-changelogs install-manpages \
	 install-docs install-json install-inex install-scripts
	 
clean: clean-pixmaps clean-json clean-inex clean-all

distclean: clean

sysclean: uninstall rmgambas

build-inex:
	@echo -e '\033[1;32mBuild I-Nex...\033[0m'
	$(MAKE) -C src
build-json:
	@echo -e '\033[1;32mBuild JSON...\033[0m'
	$(MAKE) -C JSON
build-pixmaps:
	@echo -e '\033[1;32mBuild Pixmaps...\033[0m'
	$(MAKE) -C pixmaps
	
install-create-dirs:
	mkdir -p $(DESTDIR)$(bindir)
	mkdir -p $(DESTDIR)$(PREFIX)/share/pixmaps/
	mkdir -p $(DESTDIR)$(PREFIX)/share/applications/
	mkdir -p $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	mkdir -p $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/pastebin.d/
	
install-pastebinit-and-other:
	@echo -e '\033[1;32mInstall pastebinit and other...\033[0m'
	$(INSTALL) 0755 debian/i-nex.desktop $(DESTDIR)$(PREFIX)/share/applications/
	$(INSTALL) 0755 pastebin.d/* $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/pastebin.d/
	$(INSTALL) 0755 pastebinit $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	
install-pixmaps:
	@echo -e '\033[1;32mInstall pixmaps...\033[0m'
	$(MAKE) -C pixmaps install
	
install-changelogs:
	@echo -e '\033[1;32mInstall changelogs...\033[0m'
	$(MAKE) -C changelogs install
	
install-manpages:
	@echo -e '\033[1;32mInstall manpages...\033[0m'
	$(MAKE) -C manpages install
	
install-docs:
	@echo -e '\033[1;32mInstall docs...\033[0m'
	$(MAKE) -C docs install
	
install-json:
	@echo -e '\033[1;32mInstall JSON...\033[0m'
	$(MAKE) -C JSON install
	
install-inex:
	@echo -e '\033[1;32mInstall I-Nex...\033[0m'
	$(MAKE) -C src install

install-scripts:
	@echo -e '\033[1;32mInstall Scripts...\033[0m'
	$(MAKE) -C Scripts install
	 
clean-pixmaps: 
	$(MAKE) -C pixmaps clean
	
clean-json:
	$(MAKE) -C JSON clean
	
clean-inex:
	if test -f "src/Makefile" ; then $(MAKE) -C src distclean ; fi
	
clean-all:
	$(RM_COM) $(RMDIR_OPT) `find . -name ".gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name ".directory"`
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
	
uninstall:
	rm $(DESTDIR)$(bindir)/i-nex
	rm $(DESTDIR)$(bindir)/i-nex-edid
	rm $(DESTDIR)$(bindir)/i-nex-cpuid
	rm $(DESTDIR)$(bindir)/i-nex-usage
	rm $(DESTDIR)$(bindir)/i-nex-cpusage
	rm $(DESTDIR)$(bindir)/i-nex-glinfo
	rm $(DESTDIR)$(bindir)/i-nex-uname
	rm $(DESTDIR)$(bindir)/i-nex.gambas
	rm $(DESTDIR)$(PREFIX)/share/pixmaps/i-nex.xpm
	rm $(DESTDIR)$(PREFIX)/share/applications/i-nex.desktop
	rm $(DESTDIR)$(bindir)/check_kernel
	rm $(DESTDIR)$(bindir)/i-nex-lspci
	$(RM_COM) $(RMDIR_OPT) $(DESTDIR)$(PREFIX)/share/doc/i-nex
	$(RM_COM) $(RMDIR_OPT) $(DESTDIR)$(PREFIX)/share/i-nex
	
rmgambas:
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/bin/gbx3
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/bin/gbr3
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.debug.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.desktop.gambas
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.desktop.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.draw.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.eval.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.form.gambas
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.form.stock.gambas
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.geom.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.gtk.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.gui.base.gambas
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.gui.opengl.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.gui.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.image.so
	$(RM_COM) $(RMFILE_OPT) $(PREFIX)/lib/gambas3/gb.qt4.so
