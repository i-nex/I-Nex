# Maintainer: aaditya <aaditya_gnulinux[at]zoho[dot]com>

pkgname=i-nex
prgname=I-Nex
pkgver=0.5.8
pkgrel=1
pkgdesc="System information tool like hardinfo, sysinfo"
arch=('any')
url="https://github.com/eloaders/I-Nex"
license=('LGPL3')
depends=('gcc' 'gambas3-gb-image' 'gambas3-gb-gtk' 'gambas3-gb-form' 'gambas3-gb-desktop' 'gambas3-gb-settings' 'gambas3-gb-form-dialog' 'gambas3-gb-qt4' 'gambas3-gb-form-mdi' 'gambas3-gb-form-stock' 'xorg-server-utils' 'lsb-release' 'mesa-demos')
makedepends=('gambas3-devel')
conflicts=('i-nex-bzr')
source=("https://github.com/eloaders/I-Nex/archive/0.5.8.tar.gz")
sha1sums=('e3b297c5726a175319cbf734d90d47f8b34c7733')

build() {
  cd "${srcdir}/${prgname}-${pkgver}/src/i-nex"
  echo "Starting make..."
  gbc3 -eagtpmv
  gba3
  cd "${srcdir}/${prgname}-${pkgver}/
  gcc edid-decode.c -g -Wall -o inex-edid
}

package() {
  cd "${srcdir}/${prgname}-${pkgver}"
  sed -i 's|i-nex.gambas|i-nex|' debian/i-nex.desktop
  install -Dm755 inex-edid "$pkgdir/usr/bin/inex-edid"
  install -Dm755 src/i-nex/i-nex.gambas "$pkgdir/usr/bin/i-nex"
  install -Dm644 src/i-nex/logo/i-nex.0.4.x.png "$pkgdir/usr/share/pixmaps/i-nex.0.4.x.png"
  install -Dm644 debian/i-nex.desktop "$pkgdir/usr/share/applications/i-nex.desktop"
  install -dm755 "$pkgdir/usr/share/i-nex/pastebinit"
  cp -rf pastebin.d utils pastebinit{,.xml} release.conf test.sh "$pkgdir/usr/share/i-nex/pastebinit"
  sed -i 's|python$|python2|' "$pkgdir/usr/share/i-nex/pastebinit/pastebinit"
}

# vim:set ts=2 sw=2 et: