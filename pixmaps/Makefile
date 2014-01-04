#include ../buildsys.mk
INSTALL = install
MKDIR_P = mkdir -p
datarootdir = /usr/share
make: 
	${MKDIR_P} 128x128  
	${MKDIR_P} 16x16  
	${MKDIR_P} 192x192  
	${MKDIR_P} 22x22  
	${MKDIR_P} 24x24  
	${MKDIR_P} 256x256
	${MKDIR_P} 32x32
	${MKDIR_P} 36x36
	${MKDIR_P} 48x48  
	${MKDIR_P} 512x512
	${MKDIR_P} 64x64
	${MKDIR_P} 72x72
	${MKDIR_P} 96x96
	convert i-nex.xpm -resize 128x128 128x128/i-nex.png
	convert i-nex.xpm -resize 16x16 16x16/i-nex.png
	convert i-nex.xpm -resize 192x192 192x192/i-nex.png
	convert i-nex.xpm -resize 22x22 22x22/i-nex.png
	convert i-nex.xpm -resize 24x24 24x24/i-nex.png
	convert i-nex.xpm -resize 256x256 256x256/i-nex.png
	convert i-nex.xpm -resize 32x32 32x32/i-nex.png
	convert i-nex.xpm -resize 36x36 36x36/i-nex.png
	convert i-nex.xpm -resize 48x48 48x48/i-nex.png
	convert i-nex.xpm -resize 512x512 512x512/i-nex.png
	convert i-nex.xpm -resize 64x64 64x64/i-nex.png
	convert i-nex.xpm -resize 72x72 72x72/i-nex.png
	convert i-nex.xpm -resize 96x96 96x96/i-nex.png
	
install:
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/24x24/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/36x36/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/64x64/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/72x72/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/96x96/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/128x128/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/256x256/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/192x192/apps
	${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/512x512/apps
	#${MKDIR_P} ${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps

	${INSTALL} -m 644 22x22/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/22x22/apps/"
	${INSTALL} -m 644 32x32/i-nex.png "${DESTDIR}${datarootdir}/pixmaps/"
	${INSTALL} -m 644 24x24/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/24x24/apps/"
	${INSTALL} -m 644 32x32/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/32x32/apps/"
	${INSTALL} -m 644 36x36/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/36x36/apps/"
	${INSTALL} -m 644 48x48/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/"
	${INSTALL} -m 644 64x64/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/64x64/apps/"
	${INSTALL} -m 644 72x72/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/72x72/apps/"
	${INSTALL} -m 644 96x96/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/96x96/apps/"
	${INSTALL} -m 644 128x128/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/128x128/apps/"
	${INSTALL} -m 644 256x256/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/256x256/apps/"
	${INSTALL} -m 644 192x192/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/192x192/apps/"
	${INSTALL} -m 644 512x512/i-nex.png "${DESTDIR}${datarootdir}/icons/hicolor/512x512/apps/"

uninstall:
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/48x48/apps/i-nex.xpm" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
	if test -f "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; then ${RM} "${DESTDIR}${datarootdir}/icons/hicolor/scalable/apps/i-nex.svg" ; fi
clean:
	
	rm -Rf 128x128  
	rm -Rf 16x16  
	rm -Rf 192x192  
	rm -Rf 22x22  
	rm -Rf 24x24  
	rm -Rf 256x256
	rm -Rf 32x32
	rm -Rf 36x36
	rm -Rf 48x48  
	rm -Rf 512x512
	rm -Rf 64x64
	rm -Rf 72x72
	rm -Rf 96x96