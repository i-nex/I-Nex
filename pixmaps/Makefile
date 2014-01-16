#include ../buildsys.mk
INSTALL = install
MKDIR_P = mkdir -p
datarootdir = /usr/share
make: 
	${MKDIR_P} 16x16  
	${MKDIR_P} 32x32
	${MKDIR_P} pixmaps
	convert i-nex.xpm -resize 16x16 16x16/i-nex.xpm
	convert i-nex.xpm -resize 32x32 32x32/i-nex.xpm
	convert i-nex.xpm -resize 32x32 pixmaps/i-nex.xpm
	
install:
	${MKDIR_P} ${DESTDIR}${datarootdir}/pixmaps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps

	${INSTALL} -m 644 32x32/i-nex.xpm "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 16x16/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/16x16/apps/"
	${INSTALL} -m 644 32x32/i-nex.xpm "${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps/"

uninstall:
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
clean:
	
	rm -Rf pixmaps
	rm -Rf 16x16  
	rm -Rf 32x32