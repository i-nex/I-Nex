#!/bin/bash

# System Report script for Gambas
# Joshua Higgins
# GPL'd

# 20/01/2010 - Integration into Gambas IDE
# 17/01/2011 - Add detected desktop
# 05/09/2011 - Support for LXDE

# echo "System Report for Gambas"

# ---------------- DETECT DISTRIBUTION VERSION

# Detection of following distro's is supported
# To add dectection of your favourite distro, format as follows:
# distroshortname:/path/to/version/file
# (generic:/etc/issue should be the LAST entry in the list, as this is the fallback)

distros="lsb-release:/etc/lsb-release \
	 vector:/etc/vector-version \
	 slackware:/etc/slackware-version \
	 debian:/etc/debian_version \
	 redhat:/etc/redhat-release \
	 arch:/etc/arch-release \
	 SuSE:/etc/SuSE-release \
	 gentoo:/etc/gentoo-release \
	 conectiva:/etc/conectiva-release \
	 mandriva:/etc/mandriva-release \
	 mandrake:/etc/mandrake-release \
	 pardus:/etc/pardus-release \
	 kanotix:/etc/kanotix-release \
	 generic-undetected:/etc/issue"

for distro in $distros
do

  path="`echo $distro  | awk -F: '{print $2}'`"
  vendor="`echo $distro | awk -F: '{print $1}'`"
  
  # Ubuntu and Mandriva now give lsb-release files, which needs the info extracting from
  
  if [ "$vendor" = "lsb-release" ]; then
    release="`cat $path 2>/dev/null | grep DESCRIPTION | awk -F= '{print $2}'`"
    # this is a bit ugly, because we overwrite the vendor variable, but I can't see any other way
    vendor="`cat $path 2>/dev/null | grep DISTRIB_ID | awk -F= '{print $2}'`"
  else
    release="`cat $path 2>/dev/null`"
  fi
  
  if [ "$release" = "" ]; then
    message="Still not here..."
    # Check if we've missed Arch
    if [ -e /etc/arch-release ]; then
      vendor="arch"
      release="n/a"
      #echo "Detected distro: $vendor"
      break
    fi
  else
    #echo "Found distro information at $path!"
    #echo "Detected distro: $vendor"
    break
  fi
  
done
BINUTILS=("Binutils $(ld -v | egrep -o '[0-9]+\.[0-9\.]+')")
LNXCLIB=$(sed -n -e '/^.*\/libc-\([^/]*\)\.so$/{s//\1/;p;q}' < /proc/self/maps)
# ---------------- PRINT ALL TO FILE
echo $LNXCLIB > ~/.i-nex/Lnxclib.conf
echo $BINUTILS > ~/.i-nex/Binutils.conf
echo $vendor > ~/.i-nex/DistributionVendor.conf
echo $release > ~/.i-nex/DistributionRelease.conf