#!/usr/bin/make -f

include ../i-nex.mk

install: install-changelogs compress-changelogs

install-changelogs:
	@echo -e '\033[1;32mInstalling Changelogs...\033[0m'
	install -Dm644 changelog-0.4.6 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.6"
	install -Dm644 changelog-0.4.8 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8"
	install -Dm644 changelog-0.4.8.1 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.4.8.1"
	install -Dm644 changelog-0.5.0 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.0"
	install -Dm644 changelog-0.5.1 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.1"
	install -Dm644 changelog-0.5.2 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.2"
	install -Dm644 changelog-0.5.4 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.4"
	install -Dm644 changelog-0.5.6 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.6"
	install -Dm644 changelog-0.5.8 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.5.8"
	install -Dm644 changelog-0.6.0 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.0"
	install -Dm644 changelog-0.6.2 "$(DESTDIR)$(PREFIX)$(DOCSDIR)/changelog-0.6.2"

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