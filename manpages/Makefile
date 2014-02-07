DESTDIR =
PREFIX = /usr
MANDIR = $(PREFIX)/share/man/man1

install-man:
	@echo -e '\033[1;32mInstalling Man pages 1...\033[0m'
	install -Dm644 check_kernel.1 "$(DESTDIR)$(MANDIR)/check_kernel.1"
	install -Dm644 i-nex-cpuid.1 "$(DESTDIR)$(MANDIR)/i-nex-cpuid.1"
	install -Dm644 i-nex-cpusage.1 "$(DESTDIR)$(MANDIR)/i-nex-cpusage.1"
	install -Dm644 i-nex-edid.1 "$(DESTDIR)$(MANDIR)/i-nex-edid.1"
	install -Dm644 i-nex-lspci.1 "$(DESTDIR)$(MANDIR)/i-nex-lspci.1"
	install -Dm644 i-nex-usage.1 "$(DESTDIR)$(MANDIR)/i-nex-usage.1"
	install -Dm644 i-nex.1 "$(DESTDIR)$(MANDIR)/i-nex.1"
	install -Dm644 i-nex.gambas.1 "$(DESTDIR)$(MANDIR)/i-nex.gambas.1"
	@echo -e '\033[1;32mCompress Man pages 1...\033[0m'
	gzip -9 "$(DESTDIR)$(MANDIR)/check_kernel.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex-cpuid.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex-cpusage.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex-edid.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex-lspci.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex-usage.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex.1"
	gzip -9 "$(DESTDIR)$(MANDIR)/i-nex.gambas.1"

install: install-man
