## I-Nex: System and Hardware information tool

<p align="left">
  <img src="https://raw.githubusercontent.com/eloaders/I-Nex/master/I-Nex/i-nex/logo/i-nex.0.4.x.png" alt="logo"/> <img src="http://wstaw.org/m/2014/02/24/02202014003011573_1.png" alt="logo"/>
</p>

**[Homepage](http://i-nex.linux.pl/)**

I-Nex is an application that gathers information for hardware components available on your system and displays it using an user interface similar to the popular Windows tool CPU-Z.

I-Nex can display information for the following components: CPU, GPU, Motherboard, Sound, Hard disks, RAM, Network and USB as well as some system info like the hostname, Linux distribution and version, Xorg, GCC, GLX versions and Linux Kernel info.

Besides being able to display hardware information, I-Nex can also generate an advanced report for which you can select what to include and optionally send the report to a service such as Pastebin (and others). It also features an option to take a screenshot of the I-Nex window directly from the application.

The difference between I-Nex and the other hardware information GUI tools available for Linux is that the information is better organized and is displayed faster (than lshw-gtk for instance). Also, the hardware information is presented in a way that’s easier to understand than other such tools.

### Tested on

* Ubuntu/Mint
* Debian [Bug lp:1258468](https://bugs.launchpad.net/i-nex/+bug/1258468)
* openSUSE [Question:243542](https://answers.launchpad.net/i-nex/+question/243542)
* Fedora/CentOS/RHEL
* Arch Linux
* Manjaro Linux

### Dependencies
* Gambas3
  * gambas3-runtime (>= 3.8.4)
  * gambas3-gb-image (>= 3.8.4)
  * gambas3-gb-qt4 (>= 3.8.4)
  * gambas3-gb-form (>= 3.8.4)
  * gambas3-gb-desktop (>= 3.8.4)
  * gambas3-gb-form-stock (>= 3.8.4)
* libc6
* [libcpuid](https://github.com/anrieff/libcpuid)
* libx11 libxext libgl1-mesa libglu1-mesa
  * libX11 
  * libGL 
  * libxcb 
  * libdl 
  * libglapi 
  * libXext 
  * libXdamage 
  * libXfixes 
  * libX11-xc 
  * libxcb-glx 
  * libxcb-dri2 
  * libXxf86vm 
  * libpthread 
  * libXau
* libprocps
  * libprocps3-dev, libprocps4-dev, libprocps-dev, libprocps0-dev, libproc-dev

### Build in Ubuntu

Adding required repositories:
```
sudo add-apt-repository ppa:nemh/gambas3 && \
sudo add-apt-repository ppa:i-nex-development-team/libcpuid11
```
Installing dependencies:
```
sudo apt-get install \
debhelper devscripts python python-all python-dev python-all-dev pkg-config dpkg-dev libcpuid11-dev \
lsb-release libprocps3-dev libprocps0-dev libproc-dev libx11-dev libxext-dev libgl1-mesa-dev \
libglu1-mesa-dev gambas3-dev gambas3-gb-image gambas3-gb-qt4 gambas3-gb-form gambas3-gb-desktop \
gambas3-gb-form-stock imagemagick git
```
## Downloading sources
```
git clone https://github.com/eloaders/I-Nex.git
```
## Build DEB package from sources:
```
cd ./I-Nex && \
fakeroot debian/rules build && \ 
fakeroot debian/rules binary && \
cd .. && \
sudo dpkg -i ./i-nex*.deb
```


## Install Fedora Build

### Adding required repositories:
```
  yum install dnf dnf-plugins-core fedora-repos-rawhide
  dnf copr enable brollylssj/libcpuid
  dnf copr enable brollylssj/I-Nex
```
### Installing dependencies:
```
  yum install --enablerepo rawhide gambas3-runtime gambas3-gb-desktop gambas3-gb-form gambas3-gb-form-dialog \
    gambas3-gb-form-stock gambas3-gb-gtk gambas3-gb-gui gambas3-gb-image gambas3-gb-qt5* gambas3-gb-settings
  yum install fdupes glx-utils i2c-tools procps-ng
```
### Install RPM from repository:
```
  dnf install i-nex i-nex-data
```


## Build in CentOS/RHEL

### Installing dependencies:
```
  yum install fdupes glx-utils i2c-tools procps-ng
  yum install imagemagick autoconf automake hicolor-icon-theme net-tools pkgconfig libcpuid-devel \
    procps-ng-devel freeglut libx* libx11-devel mesa-libgl* qt5-qtx11extras-devel xorg-x11-proto-devel pciutils \
    xz rpm-build redhat-rpm-config make gcc
```
### Setup RPM Build Environment
...as per [CentOS/RHEL instructions here](https://wiki.centos.org/HowTos/SetupRpmBuildEnvironment)
```
  mkdir -p ~/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
  echo "%_topdir /home/testuser/rpmbuild" >> ~/.rpmmacros
```
### Rebuild Fedora Rawhide RPM dependencies for CentOS/RHEL:
where _VERSION_ = currently available Rawhide RPM

`  rpmbuild --rebuild gambas3-<VERSION>.src.rpm` [download RPM from Rawhide repository](https://download.fedoraproject.org/pub/fedora/linux/development/rawhide/Everything/source/tree/Packages/)

`  rpmbuild --rebuild libcpuid-<VERSION>.src.rpm` [download RPM from Rawhide repository](https://download.fedoraproject.org/pub/fedora/linux/development/rawhide/Everything/source/tree/Packages/)
```
  cd ~/rpmbuild/RPMS/x86_64/
  
  yum --nogpgcheck localinstall gambas3-runtime gambas3-gb-desktop gambas3-gb-form gambas3-gb-form-dialog \
    gambas3-gb-form-stock gambas3-gb-gtk gambas3-gb-gui gambas3-gb-image gambas3-gb-qt5* gambas3-gb-settings \
    libcpuid* libcpuid*-devel
```

### Building RPM from latest commit sources:
where _GITTAG_ = Short git commit tag,
_GITLONG_ = Long git commit tag,
_TEMPSRCDIR_ = Temporary folder for uncompressed source

```
  wget https://github.com/eloaders/I-Nex/archive/<GITTAG>.zip
  cp I-Nex-<GITTAG>.zip ~/rpmbuild/SOURCES/I-Nex-<GITLONG>.zip
  unzip I-Nex-<GITTAG>.zip -d <TEMPSRCDIR>
  cp <TEMPSRCDIR>/dists/redhat/i-nex.spec ~/rpmbuild/SPECS
  rpmbuild -bb ~/rpmbuild/SPECS/i-nex.spec
```

### Build lastest git snapshot I-Nex release in Arch Linux
```
yaourt -S i-nex-git --needed --noconfirm
```

### Install lastest backported I-Nex release in Manjaro Linux
```
sudo pacman -S i-nex
```

### Main guide build app from sources

| NOTE: Don't report issues about manual build I-Nex app from sources based on this guide. First of all be sure you have installed all dependencies. Changes specify in pastebinit and inex.mk via sed command are needed for Arch Linux here. In Your distro these values can be different.|
:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


## Downloading sources
```
git clone https://github.com/eloaders/I-Nex.git
```
## Build and install app from sources
```
cd I-Nex
sed -i 's|python3$|python2|' pastebinit
sed -i -e 's|^STATIC.*|STATIC = false|' i-nex.mk
sed -i -e 's|^UDEV_RULES_DIR.*|UDEV_RULES_DIR = /usr/lib/udev/rules.d|' i-nex.mk
cd I-Nex
autoreconf -i
./configure --prefix=/usr
cd ..
make
sudo make install
```

