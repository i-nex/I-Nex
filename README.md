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
* Fedora 20
* Arch Linux
* Manjaro Linux

### Dependencies
* Gambas3
  * gambas3-runtime (>= 3.5.0)
  * gambas3-gb-image (>= 3.5.0)
  * gambas3-gb-qt4 (>= 3.5.0)
  * gambas3-gb-form (>= 3.5.0)
  * gambas3-gb-desktop (>= 3.5.0)
  * gambas3-gb-form-stock (>= 3.5.0)
* libc6
* [libcpuid](https://github.com/eloaders/libcpuid)
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
  * libprocps3 | libprocps0 | libproc

### Build in Ubuntu

Adding required repositories:
```
sudo add-apt-repository ppa:nemh/gambas3 &&\
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
