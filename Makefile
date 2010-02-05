# ZSH OR DIE, PUNKS

bindir ?= /usr/bin

edid-decode: edid-decode.c
	gcc -g -Wall -o $@ $<

clean:
	rm -f edid-decode
	-echo rm -f edid-decode **/*.jx | zsh -s

install:
	install -m 0755 edid-decode $(DESTDIR)$(bindir)
