#!/bin/bash
#if [ -e /proc/modules ]; then
#    X=`cat /proc/modules | sed -e "s/ .*$//"`
#    echo "Modules Loaded         "$X
#fi
BINUTILS=("Binutils $(ld -v | egrep -o '[0-9]+\.[0-9\.]+')")
LNXCLIB=$(sed -n -e '/^.*\/libc-\([^/]*\)\.so$/{s//\1/;p;q}' < /proc/self/maps)
GNUMAKE=$(make --version 2>&1 | awk -F, '{print $1}' | awk '/GNU Make/{print $NF}')
PPP=$(pppd --version 2>&1| grep version | awk 'NR==1{print $3}')
#Dynamic linker (ldd)
DYNAMIC_LINKER=$(ldd -v > /dev/null 2>&1 && ldd -v || ldd --version |head -n 1 | awk 'NR==1{print $NF}')
NETTOOLS=$(ifconfig --version 2>&1 | grep tools | awk 'NR==1{print $NF}')
WIRELESS_TOOLS=$(iwconfig --version 2>&1 | awk '(NR==1 && ($3 == "version")) {print $4}')
# ---------------- PRINT ALL TO FILE
echo $BINUTILS > ~/.i-nex/Binutils.conf
echo $LNXCLIB > ~/.i-nex/Lnxclib.conf
echo $GNUMAKE > ~/.i-nex/GNUMAKE.conf
echo $PPP > ~/.i-nex/PPP.conf
echo $DYNAMIC_LINKER > ~/.i-nex/DYNAMIC_LINKER.conf
echo $NETTOOLS > ~/.i-nex/NETTOOLS.conf
echo $WIRELESS_TOOLS > ~/.i-nex/WIRELESS_TOOLS.conf