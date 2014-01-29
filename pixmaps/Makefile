#include ../buildsys.mk
INSTALL = install
MKDIR_P = mkdir -p
datarootdir = /usr/share
make: 

	convert i-nex.png -resize 16x16 i-nex-16.png
	convert i-nex.png -resize 32x32 i-nex-32.png
	convert i-nex.png -resize 128x128 i-nex-128.png
	
install:
	${MKDIR_P} ${DESTDIR}${datarootdir}/pixmaps
	${INSTALL} -m 644 i-nex.png "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 i-nex-16.png "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 i-nex-32.png "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 i-nex-128.png "${DESTDIR}${datarootdir}/pixmaps/"
	
uninstall:

	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex-16.png" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex-16.png" ; fi
	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex-32.png" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex-32.png" ; fi
	if test -f "${DESTDIR}${datarootdir}/pixmaps/i-nex-128.png" ; then ${RM} "${DESTDIR}${datarootdir}/pixmaps/i-nex-128.png" ; fi
	
clean:
	
	rm i-nex-16.png
	rm i-nex-32.png
	rm i-nex-128.png
