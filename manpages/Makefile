#!/usr/bin/make -f

include ../i-nex.mk 

install-man:
	@echo -e '\033[1;32mInstalling Man pages 1...\033[0m'
	install -Dm644 i-nex-cpuid.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpuid.1"
	install -Dm644 i-nex-cpusage.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpusage.1"
	install -Dm644 i-nex-edid.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-edid.1"
	install -Dm644 i-nex-lspci.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-lspci.1"
	install -Dm644 i-nex-usage.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-usage.1"
	install -Dm644 i-nex.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.1"
	install -Dm644 i-nex.gambas.1 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.gambas.1"
	
compress-man:
	@echo -e '\033[1;32mCompress Man pages 1...\033[0m'
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpuid.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-cpusage.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-edid.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-lspci.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex-usage.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(MANDIR)/i-nex.gambas.1"
	
install: install-man compress-man
