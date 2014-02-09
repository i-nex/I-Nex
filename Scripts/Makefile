#!/usr/bin/make -f

include i-nex.mk

install-set-executables:
	chmod +x i-nex
	chmod +x i-nex-lspci
install: install-set-executables
	$(INSTALL) 0755 i-nex $(DESTDIR)$(PREFIX)$(bindir)
	$(INSTALL) 0755 i-nex-lspci $(DESTDIR)$(PREFIX)$(bindir)