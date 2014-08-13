#!/usr/bin/make -f

include ../i-nex.mk

CHANGELOG_FILES=$(wildcard changelog-*)

install: install-changelogs compress-changelogs

install-changelogs:

	@echo -e '\033[1;32mInstalling Changelogs...\033[0m'
	mkdir -p $(DESTDIR)$(PREFIX)$(DOCSDIR)
	install -Dm644 $(CHANGELOG_FILES) $(DESTDIR)$(PREFIX)$(DOCSDIR)

compress-changelogs:

	@echo -e '\033[1;32mCompress Changelogs...\033[0m'
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.6
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8.1
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.0
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.1
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.2
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.4
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.6
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.8
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.0
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.2
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.4
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.6
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-7.0.0
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-7.2.0
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-7.2.1
	${COMPRESS} $(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-7.4.0