#!/usr/bin/make -f
include ../i-nex.mk 
create-dir:
	@echo -e '\033[1;32mCreate directory...\033[0m'
	mkdir -p $(DESTDIR)$(DOCDIR)

install-doc:
	@echo -e '\033[1;32mInstalling Docs...\033[0m'
	install -Dm644 copyright "$(DESTDIR)$(DOCDIR)/copyright"
	install -Dm644 I-Nex.LICENSE "$(DESTDIR)$(DOCDIR)/I-Nex.LICENSE"
	install -Dm644 Pastebinit.LICENSE "$(DESTDIR)$(DOCDIR)/Pastebinit.LICENSE"
	@echo -e '\033[1;32mCompress Docs...\033[0m'
	gzip -9 "$(DESTDIR)$(DOCDIR)/copyright"
	gzip -9 "$(DESTDIR)$(DOCDIR)/I-Nex.LICENSE"
	gzip -9 "$(DESTDIR)$(DOCDIR)/Pastebinit.LICENSE"

install: create-dir install-doc
