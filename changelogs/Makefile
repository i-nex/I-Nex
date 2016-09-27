#!/usr/bin/make -f

include ../i-nex.mk

CHANGELOG_FILES=$(wildcard changelog-*)

install: install-changelogs
install-changelogs:

	@echo -e '\033[1;32mInstalling Changelogs...\033[0m'
	mkdir -p $(DESTDIR)$(PREFIX)$(DOCSDIR)
	install -Dm644 $(CHANGELOG_FILES) $(DESTDIR)$(PREFIX)$(DOCSDIR)
