#!/usr/bin/make -f

include ../i-nex.mk

install: database-SIV
	 
database-SIV:
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/SIV
	 $(INSTALL) 0755 $(DATABASE_SIV) $(DESTDIR)$(sysconfdir)/$(PN)/SIV/