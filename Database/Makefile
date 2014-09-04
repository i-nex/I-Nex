#!/usr/bin/make -f

include ../i-nex.mk

install: database-cpu-logos \
	 database-dist-logos \
	 database-cpu-json \
	 database-i2c-json
	 
database-cpu-logos:
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database/Logos
	 $(INSTALL) 0755 $(DATABASE_CPU_LOGOS) $(DESTDIR)$(sysconfdir)/$(PN)/Database/Logos/
	 
database-dist-logos:
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database/Distlogos
	 $(INSTALL) 0755 $(DATABASE_DIST_LOGOS) $(DESTDIR)$(sysconfdir)/$(PN)/Database/Distlogos/
	 
database-cpu-json:
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database
	 $(INSTALL) 0755 $(DATABASE_CPU_JSON) $(DESTDIR)$(sysconfdir)/$(PN)/Database/
	 
database-i2c-json:
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database
	 mkdir -p $(DESTDIR)$(sysconfdir)/$(PN)/Database/i2c
	 $(INSTALL) 0755 $(DATABASE_I2C_JSON) $(DESTDIR)$(sysconfdir)/$(PN)/Database/i2c/