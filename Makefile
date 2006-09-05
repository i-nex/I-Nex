# ZSH OR DIE, PUNKS

edid-decode: edid-decode.c
	gcc -O2 -Wall -o $@ $<

clean:
	-echo rm -f edid-decode **/*.jx | zsh -s
