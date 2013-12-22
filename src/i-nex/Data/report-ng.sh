#!/bin/bash
BINUTILS=("Binutils $(ld -v | egrep -o '[0-9]+\.[0-9\.]+')")
LNXCLIB=$(sed -n -e '/^.*\/libc-\([^/]*\)\.so$/{s//\1/;p;q}' < /proc/self/maps)
# ---------------- PRINT ALL TO FILE
echo $LNXCLIB > ~/.i-nex/Lnxclib.conf
echo $BINUTILS > ~/.i-nex/Binutils.conf