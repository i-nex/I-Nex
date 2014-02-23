#!/usr/bin/make -f

include ../i-nex.mk 
PASTEBINITCONF_FILES=$(wildcard *.conf)

install: install-pastebinit-conf
install-pastebinit-conf:

	@echo -e '\033[1;32mInstalling Pastebinit Config files...\033[0m'
	mkdir -p "$(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/pastebin.d/"
	install -Dm755 $(PASTEBINITCONF_FILES) "$(DESTDIR)$(PREFIX)/share/i-nex/pastebinit/pastebin.d/"
