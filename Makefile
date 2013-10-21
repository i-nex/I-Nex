# ZSH OR DIE, PUNKS
bindir ?= /usr/bin
bzr_revision = 
dependency_build ?= bzr \
		    devscripts \
		    pkg-config \
		    dpkg-dev \
		    gambas3-dev \
		    gambas3-gb-image \
		    gambas3-gb-gtk \
		    gambas3-gb-form \
		    gambas3-gb-desktop \
		    gambas3-gb-form-dialog \
		    gambas3-gb-settings \
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
		    hostname

make:
	gcc edid-decode.c -g -Wall -o inex-edid
	/usr/bin/gbc3 -e -a -g -t -p -m  src/i-nex
	gba3 src/i-nex

deb:
	
	apt-get install $(dependency_build)
	./build-deb
	
clean:
	rm -f inex-edid
	rm -Rf `find . -name ".gambas"`
	rm -Rf `find . -name "*.gambas"`
	rm -Rf `find . -name "screenfetch-dev"`
	rm -Rf `find . -name ".directory"`
	rm -Rf debian/files
	rm -Rf debian/i-nex
	rm -Rf debian/i-nex.debhelper.log
	rm -Rf debian/i-nex.postinst.debhelper
	rm -Rf debian/i-nex.postrm.debhelper
	rm -Rf debian/i-nex.substvars
	rm -Rf debian/changelog1

	
install:
	mkdir -p $(DESTDIR)$(bindir)
	mkdir -p $(DESTDIR)/usr/share/pixmaps/
	mkdir -p $(DESTDIR)/usr/share/applications/
	mkdir -p $(DESTDIR)/etc/apport/crashdb.conf.d/
	mkdir -p $(DESTDIR)/usr/share/apport/package-hooks/
	mkdir -p $(DESTDIR)/usr/share/doc/i-nex/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/po/
	mkdir -p $(DESTDIR)/usr/share/i-nex/pastebinit/utils/
	chmod +x i-nex
	chmod +x inex-edid
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	install -m 0755 i-nex $(DESTDIR)$(bindir)
	install -m 0755 inex-edid $(DESTDIR)$(bindir)
	install -m 0755 src/i-nex/i-nex.gambas $(DESTDIR)$(bindir)
	install -m 0755 src/i-nex/logo/i-nex.0.4.x.png $(DESTDIR)/usr/share/pixmaps/
	install -m 0755 debian/i-nex.desktop $(DESTDIR)/usr/share/applications/
	install -m 0755 debian/check_kernel $(DESTDIR)/usr/bin/
	install -m 0755 debian/i-nex-lspci $(DESTDIR)/usr/bin/
	install -m 0755 debian/inex-crashdb.conf $(DESTDIR)/etc/apport/crashdb.conf.d/
	install -m 0755 debian/i-nex.py $(DESTDIR)/usr/share/apport/package-hooks/
	install -m 0755 debian/changelog-0.4.6 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8.1 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.0 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.1 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.2 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.4 $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 LICENSE $(DESTDIR)/usr/share/doc/i-nex/
	install -m 0755 COPYING $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 pastebin.d/* $(DESTDIR)/usr/share/i-nex/pastebinit/pastebin.d/
	install -m 0755 pastebinit $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 pastebinit.xml $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 po/* $(DESTDIR)/usr/share/i-nex/pastebinit/po/
	install -m 0755 README $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 release.conf $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 test.sh $(DESTDIR)/usr/share/i-nex/pastebinit/
	install -m 0755 utils/* $(DESTDIR)/usr/share/i-nex/pastebinit/utils/
	update-desktop-database
	update-menus
uninstall:

	rm $(bindir)/i-nex
	rm $(bindir)/inex-edid
	rm $(bindir)/i-nex.gambas
	rm /usr/share/pixmaps/i-nex.0.4.x.png
	rm /usr/share/applications/i-nex.desktop
	rm $(bindir)/check_kernel
	rm $(bindir)/i-nex-lspci
	rm /etc/apport/crashdb.conf.d/inex-crashdb.conf
	rm /usr/share/apport/package-hooks/i-nex.py
	rm -Rf /usr/share/doc/i-nex
	rm -Rf /usr/share/i-nex
	update-desktop-database
	update-menus