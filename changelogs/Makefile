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
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.6"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.0"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.1"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.2"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.4"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.6"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.8"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.0"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.2"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.4"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.6"
	gzip -9 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-7.0.0"