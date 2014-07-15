#!/usr/bin/make -f
include ../i-nex.mk 
install: install-doc compress-doc

install-doc: install_copyright \
	     install_i_nex_LICENSE \
	     install_Pastebinit_LICENSE

compress-doc: compress-copyright \
	      compress_i_nex_LICENSE \
	      compress_Pastebinit_LICENSE

install_copyright:
	@echo -e '\033[1;32mCreate directory...\033[0m'
	${MKDIR_P} $(DESTDIR)$(PREFIX)$(DOCSDIR)
	@echo -e '\033[1;32mInstalling Docs copyright...\033[0m'
	${INSTALL_DM}644 copyright "$(DESTDIR)$(PREFIX)$(DOCSDIR)/copyright"
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

compress_copyright:
		@echo -e '\033[1;32mCompress Docs copyright...\033[0m'
		${COMPRESS} "$(DESTDIR)$(PREFIX)$(DOCSDIR)/copyright"
compress_i_nex_LICENSE:
		@echo -e '\033[1;32mCompress Docs I-Nex.LICENSE...\033[0m'
		${COMPRESS} "$(DESTDIR)$(PREFIX)$(DOCSDIR)/I-Nex.LICENSE"
compress_Pastebinit_LICENSE:
		@echo -e '\033[1;32mCompress Docs Pastebinit.LICENSE...\033[0m'
		${COMPRESS} "$(DESTDIR)$(PREFIX)$(DOCSDIR)/Pastebinit.LICENSE"