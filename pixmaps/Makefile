#!/usr/bin/make -f
include ../i-nex.mk
install:
	mkdir -p ${DESTDIR}$(PREFIX)/share/pixmaps
	${INSTALL} 644 i-nex.png $(DESTDIR)$(PREFIX)/share/pixmaps/
	${INSTALL} 644 i-nex-16.png $(DESTDIR)$(PREFIX)/share/pixmaps/
	${INSTALL} 644 i-nex-32.png $(DESTDIR)$(PREFIX)/share/pixmaps/
	${INSTALL} 644 i-nex-128.png $(DESTDIR)$(PREFIX)/share/pixmaps/
	
uninstall:

	if test -f $(DESTDIR)$(PREFIX)/share/pixmaps/i-nex-16.png ; then ${RM} $(DESTDIR)$(PREFIX)/share/pixmaps/i-nex-16.png ; fi
	if test -f ${DESTDIR}$(PREFIX)/share/pixmaps/i-nex-32.png ; then ${RM} $(DESTDIR)$(PREFIX)/share/pixmaps/i-nex-32.png ; fi
	if test -f ${DESTDIR}$(PREFIX)/share/pixmaps/i-nex-128.png ; then ${RM} $(DESTDIR)$(PREFIX)/share/pixmaps/i-nex-128.png ; fi
