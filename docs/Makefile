#!/usr/bin/make -f
include ../i-nex.mk 
install: install-doc

install-doc: install_i_nex_LICENSE \
	     install_Pastebinit_LICENSE

install_i_nex_LICENSE:
	@echo -e '\033[1;32mCreate directory...\033[0m'
	${MKDIR_P} $(DESTDIR)$(PREFIX)$(DOCSDIR)
	@echo -e '\033[1;32mInstalling Docs I-Nex.LICENSE...\033[0m'
	${INSTALL_DM}644 I-Nex.LICENSE "$(DESTDIR)$(PREFIX)$(DOCSDIR)/I-Nex.LICENSE"
install_Pastebinit_LICENSE:
	@echo -e '\033[1;32mCreate directory...\033[0m'
	${MKDIR_P} $(DESTDIR)$(PREFIX)$(DOCSDIR)
	@echo -e '\033[1;32mInstalling Docs Pastebinit.LICENSE...\033[0m'
	${INSTALL_DM}644 Pastebinit.LICENSE "$(DESTDIR)$(PREFIX)$(DOCSDIR)/Pastebinit.LICENSE"
