# ZSH OR DIE, PUNKS

edid-decode: edid-decode.c
	gcc -g -Wall -o $@ $<

clean:
	rm -f edid-decode
	-echo rm -f edid-decode **/*.jx | zsh -s
