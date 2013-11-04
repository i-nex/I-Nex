# Maintainer: Ner0

pkgname=i-nex
pkgver=0.5.6
pkgrel=1
pkgdesc="System information tool like hardinfo, sysinfo"
arch=('any')
url="http://tuxportal.pl/"
license=('LGPL3')
depends=('gambas3-runtime' 'gambas3-gb-image' 'gambas3-gb-gtk' 'gambas3-gb-form' 'gambas3-gb-desktop' 'gambas3-gb-settings' 'gambas3-gb-form-dialog' 'gambas3-gb-qt4'
         'gambas3-gb-form-mdi' 'gambas3-gb-form-stock' 'util-linux' 'procps' 'xorg-server-utils' 'gksu' 'lsb-release' 'coreutils' 'pciutils' 'inetutils' 'mesa-demos')
makedepends=('bzr' 'gambas3-devel' 'gcc')

_bzrtrunk=lp:i-nex
_bzrmod=i-nex

build() {
  msg "Connecting to Bazaar server...."

  if [[ -d "$_bzrmod" ]]; then
    cd "$_bzrmod" && bzr pull "$_bzrtrunk" -r "$pkgver" && cd ..
    msg "The local files are updated."
  else
    bzr branch "$_bzrtrunk" "$_bzrmod" -r "$pkgver"
  fi

  msg "BZR checkout done or server timeout"
  msg "Starting make..."

  rm -rf "$_bzrmod-build"
  cp -rf $_bzrmod $_bzrmod-build
  cd "$_bzrmod-build/src/i-nex"

  gbc3 -eagtpmv
  gba3
}

package() {
  cd "$srcdir/$_bzrmod-build/"

  sed -i 's|i-nex.gambas|i-nex|' debian/i-nex.desktop

  install -Dm755 src/i-nex/i-nex.gambas "$pkgdir/usr/bin/i-nex"
  install -Dm644 src/i-nex/logo/i-nex.0.4.x.png "$pkgdir/usr/share/pixmaps/i-nex.0.4.x.png"
  install -Dm644 debian/i-nex.desktop "$pkgdir/usr/share/applications/i-nex.desktop"
  install -dm755 "$pkgdir/usr/share/i-nex/pastebinit"
  cp -rf pastebin.d utils pastebinit{,.xml} release.conf test.sh "$pkgdir/usr/share/i-nex/pastebinit"

  sed -i 's|python$|python2|' "$pkgdir/usr/share/i-nex/pastebinit/pastebinit"
} 