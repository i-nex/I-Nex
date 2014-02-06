# Maintainer: aaditya <aaditya_gnulinux[at]zoho[dot]com>

pkgname=i-nex
_prgname=I-Nex
pkgver=0.6.0
pkgrel=1
pkgdesc="System information tool like hardinfo, sysinfo"
arch=('i686' 'x86_64')
url="https://github.com/eloaders/I-Nex"
license=('LGPL3')
depends=('gambas3-gb-gtk' 'gambas3-gb-desktop' 'gambas3-gb-settings' 'gambas3-gb-form-dialog' 'gambas3-gb-qt4' 'gambas3-gb-form-mdi' 'gambas3-gb-form-stock' 'xorg-server-utils' 'lsb-release' 'mesa-demos')
makedepends=('gambas3-devel')
conflicts=('i-nex-bzr')
source=("https://github.com/eloaders/I-Nex/archive/master.zip")
sha1sums=('SKIP')

build() {
  cd "${_prgname}-master/src/i-nex"
  echo "Starting make..."
  gbc3 -eagtpmv
  gba3
  cd "../.."
  gcc edid-decode.c -g -Wall -o inex-edid
  gcc -o inex-cpuid cpu.c -static `pkg-config libcpuid --cflags --libs`
}

package() {
  cd "${_prgname}-master"
  sed -i 's|i-nex.gambas|i-nex|' debian/i-nex.desktop
  install -Dm755 inex-edid "$pkgdir/usr/bin/inex-edid"
  install -Dm755 inex-cpuid "$pkgdir/usr/bin/inex-cpuid"
  install -Dm755 src/i-nex/i-nex.gambas "$pkgdir/usr/bin/i-nex"
  install -Dm644 src/i-nex/logo/i-nex.0.4.x.png "$pkgdir/usr/share/pixmaps/i-nex.0.4.x.png"
  install -Dm644 debian/i-nex.desktop "$pkgdir/usr/share/applications/i-nex.desktop"
  install -dm755 "$pkgdir/usr/share/i-nex/pastebinit"
  cp -r pastebin.d pastebinit{,.xml} release.conf "$pkgdir/usr/share/i-nex/pastebinit"
  sed -i 's|python$|python2|' "$pkgdir/usr/share/i-nex/pastebinit/pastebinit"
}

# vim:set ts=2 sw=2 et:
