#!/usr/bin/make -f
include ../i-nex.mk 
install: install-doc compress-doc

install-doc:
	@echo -e '\033[1;32mCreate directory...\033[0m'
	mkdir -p $(DESTDIR)$(PREFIX)$(DOCSDIR)
	@echo -e '\033[1;32mInstalling Docs...\033[0m'
	install -Dm644 copyright "$(DESTDIR)$(PREFIX)$(DOCSDIR)/copyright"
	install -Dm644 I-Nex.LICENSE "$(DESTDIR)$(PREFIX)$(DOCSDIR)/I-Nex.LICENSE"
	install -Dm644 Pastebinit.LICENSE "$(DESTDIR)$(PREFIX)$(DOCSDIR)/Pastebinit.LICENSE"
	
compress-doc:
	@echo -e '\033[1;32mCompress Docs...\033[0m'
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/copyright"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/I-Nex.LICENSE"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/Pastebinit.LICENSE"