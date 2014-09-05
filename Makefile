#!/usr/bin/make -f

include i-nex.mk
make: build-inex build-json build-pixmaps

install: install-pastebinit-and-other \
	 install-pixmaps install-changelogs install-manpages \
	 install-docs install-json install-inex install-scripts \
	 install-udev-rule link-inex install-database install-siv
	 
clean: clean-pixmaps clean-json clean-inex clean-all

distclean: clean

sysclean: uninstall rmgambas

build-inex:

	@echo -e '\033[1;32mBuild I-Nex...\033[0m'
	$(MAKE) -C I-Nex
	
build-json:

	@echo -e '\033[1;32mBuild JSON...\033[0m'
	$(MAKE) -C JSON
	
build-pixmaps:

	@echo -e '\033[1;32mBuild Pixmaps...\033[0m'
	$(MAKE) -C pixmaps
	
install-pastebinit-and-other:
	@echo -e '\033[1;32mCreate nedded dirs...\033[0m'
	mkdir -p $(DESTDIR)$(PREFIX)/share/applications
	mkdir -p $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit
	mkdir -p $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/pastebin.d
	@echo -e '\033[1;32mInstall pastebinit and other...\033[0m'
	$(INSTALL) 0755 debian/i-nex.desktop $(DESTDIR)$(PREFIX)/share/applications/
	$(INSTALL) 0755 debian/i-nex-library.desktop $(DESTDIR)$(PREFIX)/share/applications/
	$(INSTALL) 0755 pastebinit $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 pastebinit.xml $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	$(INSTALL) 0755 release.conf $(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/
	$(MAKE) -C pastebin.d install
	
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
	$(MAKE) -C I-Nex install

install-scripts:

	@echo -e '\033[1;32mInstall Scripts...\033[0m'
	$(MAKE) -C Scripts install

install-database:
	@echo -e '\033[1;32mInstall database files...\033[0m'
	$(MAKE) -C Database install

install-siv:
	@echo -e '\033[1;32mInstall SIV files...\033[0m'
	$(MAKE) -C SIV install
	
clean-pixmaps:

	$(MAKE) -C pixmaps clean
	
clean-json:

	$(MAKE) -C JSON clean
	
clean-inex:

	if test -f "I-Nex/Makefile" ; then $(MAKE) -C I-Nex distclean ; fi

install-udev-rule:

	$(INSTALL_DM) 600 i2c_smbus.rules $(DESTDIR)$(UDEV_RULES_DIR)/i2c_smbus.rules

clean-all:

	$(RM_COM) $(RMDIR_OPT) `find . -name ".gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name "*.gambas"`
	$(RM_COM) $(RMDIR_OPT) `find . -name ".directory"`
	$(RM_COM) $(RMFILE_OPT) I-Nex/i-nex/.lang/*.pot
	$(RM_COM) $(RMFILE_OPT) I-Nex/i-nex/.lang/*.po
	$(RM_COM) $(RMFILE_OPT) I-Nex/i-nex/.lang/*.mo
	$(RM_COM) $(RMDIR_OPT) I-Nex/i-nex/.gambas
	$(RM_COM) $(RMDIR_OPT) debian/files
	$(RM_COM) $(RMDIR_OPT) debian/i-nex
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.debhelper.log
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.postinst.debhelper
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.postrm.debhelper
	$(RM_COM) $(RMDIR_OPT) debian/i-nex.substvars
	$(RM_COM) $(RMDIR_OPT) debian/changelog1
	$(RM_COM) $(RMDIR_OPT) I-Nex/autom4te.cache
	$(RM_COM) $(RMDIR_OPT) I-Nex/config.log
	$(RM_COM) $(RMDIR_OPT) I-Nex/config.status
	$(RM_COM) $(RMDIR_OPT) I-Nex/configure
	$(RM_COM) $(RMDIR_OPT) I-Nex/install-sh
	$(RM_COM) $(RMDIR_OPT) I-Nex/missing


link-inex:
	ln -s /usr/bin/i-nex.gambas $(DESTDIR)$(bindir)/i-nex