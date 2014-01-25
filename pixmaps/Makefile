#include ../buildsys.mk
INSTALL = install
MKDIR_P = mkdir -p
datarootdir = /usr/share
make: 
	${MKDIR_P} 16x16
	${MKDIR_P} 22x22
	${MKDIR_P} 32x32
	${MKDIR_P} 48x48
	${MKDIR_P} pixmaps
	convert i-nex.png -resize 16x16 16x16/i-nex.xpm
	convert i-nex.png -resize 32x32 32x32/i-nex.xpm
	convert i-nex.png -resize 22x22 22x22/i-nex.xpm
	convert i-nex.png -resize 48x48 48x48/i-nex.xpm
	convert i-nex.png -resize 96x96 pixmaps/i-nex.xpm
	
install:
	${MKDIR_P} ${DESTDIR}${datarootdir}/pixmaps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps
	${INSTALL} -m 644 pixmaps/i-nex.xpm "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 16x16/i-nex.xpm "${DESTDIR}${datarootdir}/pixmaps/i-nex-16.xpm"
	${INSTALL} -m 644 32x32/i-nex.xpm "${DESTDIR}${datarootdir}/pixmaps/i-nex-32.xpm"
	${INSTALL} -m 644 16x16/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps/"
	${INSTALL} -m 644 22x22/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps/"
	${INSTALL} -m 644 32x32/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps/"
	${INSTALL} -m 644 48x48/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/"
	
uninstall:

	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex-16.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex-16.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex-32.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex-32.xpm" ; fi

clean:
	
	rm -Rf pixmaps
	rm -Rf 16x16
	rm -Rf 22x22
	rm -Rf 32x32
	rm -Rf 48x48