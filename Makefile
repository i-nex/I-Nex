# ZSH OR DIE, PUNKS

edid-decode: edid-decode.c
	gcc -g -Wall -o $@ $<

clean:
	-echo rm -f edid-decode **/*.jx | zsh -s
