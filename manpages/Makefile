#!/usr/bin/make -f

include ../i-nex.mk 
MANPAGE_FILES=$(wildcard *.1)

install: install-man compress-man
install-man:

	@echo -e '\033[1;32mInstalling Man pages 1...\033[0m'
	mkdir -p "$(DESTDIR)$(PREFIX)$(MANDIR)/"
	install -Dm644 $(MANPAGE_FILES) "$(DESTDIR)$(PREFIX)$(MANDIR)/"
	
compress-man:
	@echo -e '\033[1;32mCompress Man pages 1...\033[0m'
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpuid.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpusage.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-edid.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-lspci.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-usage.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.gambas.1"
