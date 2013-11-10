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
	
self:

	./build-selfexecutable
	mkdir -p inex
	mkdir -p inex$(bindir)
	mkdir -p inex/usr/lib/gambas3/
	mkdir -p inex/usr/share/pixmaps/
	mkdir -p inex/usr/share/applications/
	mkdir -p inex/usr/share/doc/i-nex/
	mkdir -p inex/usr/share/i-nex/pastebinit/
	mkdir -p inex/usr/share/i-nex/pastebinit/pastebin.d/
	mkdir -p inex/usr/share/i-nex/pastebinit/po/
	mkdir -p inex/usr/share/i-nex/pastebinit/utils/
	chmod +x i-nex
	chmod +x inex-edid
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	install -m 0755 i-nex inex$(bindir)
	install -m 0755 inex-edid inex$(bindir)
	install -m 0755 src/i-nex/i-nex.gambas inex$(bindir)
	install -m 0755 src/i-nex/logo/i-nex.0.4.x.png inex/usr/share/pixmaps/
	install -m 0755 debian/i-nex.desktop inex/usr/share/applications/
	install -m 0755 debian/check_kernel inex/usr/bin/
	install -m 0755 debian/i-nex-lspci inex/usr/bin/
	install -m 0755 debian/changelog-0.4.6 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8.1 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.0 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.1 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.2 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.4 inex/usr/share/doc/i-nex/
	install -m 0755 LICENSE inex/usr/share/doc/i-nex/
	install -m 0755 COPYING inex/usr/share/i-nex/pastebinit/
	install -m 0755 pastebin.d/* inex/usr/share/i-nex/pastebinit/pastebin.d/
	install -m 0755 pastebinit inex/usr/share/i-nex/pastebinit/
	install -m 0755 pastebinit.xml inex/usr/share/i-nex/pastebinit/
	install -m 0755 po/* inex/usr/share/i-nex/pastebinit/po/
	install -m 0755 README inex/usr/share/i-nex/pastebinit/
	install -m 0755 release.conf inex/usr/share/i-nex/pastebinit/
	install -m 0755 test.sh inex/usr/share/i-nex/pastebinit/
	install -m 0755 utils/* inex/usr/share/i-nex/pastebinit/utils/
	install -m 0775 usr/bin/gbx3 inex/usr/bin/gbx3
	install -m 0775 usr/bin/gbr3 inex/usr/bin/gbr3
	install -m 0775 usr/lib/gambas3/gb.debug.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.desktop.gambas inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.desktop.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.draw.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.eval.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.form.gambas inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.form.stock.gambas inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.geom.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.gtk.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.gui.base.gambas inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.gui.opengl.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.gui.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.image.so inex/usr/lib/gambas3/
	install -m 0775 usr/lib/gambas3/gb.qt4.so inex/usr/lib/gambas3/
	install -m 0775 install-self inex/install-self 
	install -m 0775 install-self-inex inex/install-self-inex
	chmod +x inex/install-self
	chmod +x inex/install-self-inex
	./makeself.sh --nowait --nox11 ./inex i-nex.run I-Nex ./install-self
clean:
	rm -f inex-edid
	rm -Rf `find . -name ".gambas"`
	rm -Rf `find . -name "*.gambas"`
	rm -Rf `find . -name "screenfetch-dev"`
	rm -Rf `find . -name ".directory"`
	rm -Rf `find . -name "*.deb"`
	rm -f index.html
	rm -f i-nex.run
	rm -Rf debian/files
	rm -Rf debian/i-nex
	rm -Rf debian/i-nex.debhelper.log
	rm -Rf debian/i-nex.postinst.debhelper
	rm -Rf debian/i-nex.postrm.debhelper
	rm -Rf debian/i-nex.substvars
	rm -Rf debian/changelog1
	rm -Rf inex
	rm -Rf usr

	
install:
	mkdir -p inex$(bindir)
	mkdir -p inex/usr/share/pixmaps/
	mkdir -p inex/usr/share/applications/
	mkdir -p inex/usr/share/doc/i-nex/
	mkdir -p inex/usr/share/i-nex/pastebinit/
	mkdir -p inex/usr/share/i-nex/pastebinit/pastebin.d/
	mkdir -p inex/usr/share/i-nex/pastebinit/po/
	mkdir -p inex/usr/share/i-nex/pastebinit/utils/
	chmod +x i-nex
	chmod +x inex-edid
	chmod +x debian/check_kernel
	chmod +x debian/i-nex-lspci
	install -m 0755 i-nex inex$(bindir)
	install -m 0755 inex-edid inex$(bindir)
	install -m 0755 src/i-nex/i-nex.gambas inex$(bindir)
	install -m 0755 src/i-nex/logo/i-nex.0.4.x.png inex/usr/share/pixmaps/
	install -m 0755 debian/i-nex.desktop inex/usr/share/applications/
	install -m 0755 debian/check_kernel inex/usr/bin/
	install -m 0755 debian/i-nex-lspci inex/usr/bin/
	install -m 0755 debian/changelog-0.4.6 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.4.8.1 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.0 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.1 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.2 inex/usr/share/doc/i-nex/
	install -m 0755 debian/changelog-0.5.4 inex/usr/share/doc/i-nex/
	install -m 0755 LICENSE inex/usr/share/doc/i-nex/
	install -m 0755 COPYING inex/usr/share/i-nex/pastebinit/
	install -m 0755 pastebin.d/* inex/usr/share/i-nex/pastebinit/pastebin.d/
	install -m 0755 pastebinit inex/usr/share/i-nex/pastebinit/
	install -m 0755 pastebinit.xml inex/usr/share/i-nex/pastebinit/
	install -m 0755 po/* inex/usr/share/i-nex/pastebinit/po/
	install -m 0755 README inex/usr/share/i-nex/pastebinit/
	install -m 0755 release.conf inex/usr/share/i-nex/pastebinit/
	install -m 0755 test.sh inex/usr/share/i-nex/pastebinit/
	install -m 0755 utils/* inex/usr/share/i-nex/pastebinit/utils/
	
uninstall:

	rm $(bindir)/i-nex
	rm $(bindir)/inex-edid
	rm $(bindir)/i-nex.gambas
	rm /usr/share/pixmaps/i-nex.0.4.x.png
	rm /usr/share/applications/i-nex.desktop
	rm $(bindir)/check_kernel
	rm $(bindir)/i-nex-lspci
	rm -Rf /usr/share/doc/i-nex
	rm -Rf /usr/share/i-nex
	update-desktop-database
	update-menus