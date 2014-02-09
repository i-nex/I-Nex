## I-Nex: System and Hardware information tool

![logo](https://raw2.github.com/eloaders/I-Nex/master/src/i-nex/logo/i-nex.0.4.x.png)

### I-Nex jest aplikacją Open Source, która wyświetla informacje o podzespołach komputera jak i samym systemie operacyjnym.

* Wyświetla informacje w przyjaznej formie, opartej na kartach.
* Potrafi tworzyć zrzut aktywnej karty i zapisywać w formacie JPG lub PNG.
* Pozwala wybierać poziom kompresji zapisywanego zdjęcia.
* Potrafi tworzyć raport z zakładek i zapisuje je w formacie raw txt.
* Pozwala wybrać, co dokładnie ma zawrzeć w raporcie.
* Potrafi wysłać wygenerowany raport na ponad 10 serwisów nopaste.
* Zapamiętuje pozycję na akranie oraz pozwala na ustwienie położenia kart.

### Strony

* Strony: [Strona domowa](http://i-nex.linux.pl/) | [Wygląd aplikacji](http://i-nex.linux.pl/screenshots/) | [Blog](http://i-nex.linux.pl/) | [Forum/Raportowanie błędów](http://demo.gitlabhq.com/users/sign_in)

### Testowany na

* Ubuntu i pochodne
* Debian [Bug lp:1258468](https://bugs.launchpad.net/i-nex/+bug/1258468)
* openSUSE [Question:243542](https://answers.launchpad.net/i-nex/+question/243542)
* Fedora 20


* Gambas3
  * gambas3-runtime (>= 3.5.0)
  * gambas3-gb-image (>= 3.5.0)
  * gambas3-gb-qt4 (<< 3.5.0)
  * gambas3-gb-form (<< 3.5.0)
  * gambas3-gb-desktop (>= 3.5.0)
  * gambas3-gb-form-stock (>= 3.5.0)
* libc6
* [libcpuid](https://github.com/eloaders/libcpuid)
* libx11 libxext libgl1-mesa libglu1-mesa
  * libX11 libGL libxcb libdl libglapi libXext libXdamage libXfixes libX11-xc libxcb-glx libxcb-dri2 libXxf86vm libpthread libXau
* libprocps
  * libprocps3 | libprocps0 | libproc

** More details are in the [requirements doc](doc/install/requirements.md)

### Kompilacja
#### Ubuntu
Dodanie repozytoriów:

    sudo add-apt-repository ppa:nemh/gambas3
    sudo add-apt-repository ppa:i-nex-development-team/libcpuid11

Instalacja zależności potrzebnych do kompilacji:

    sudo apt-get install debhelper devscripts
    sudo apt-get install python python-all python-dev python-all-dev pkg-config dpkg-dev 
    sudo apt-get install libcpuid11-dev lsb-release libprocps3-dev libprocps0-dev libproc-dev 
    sudo apt-get install libx11-dev libxext-dev libgl1-mesa-dev libglu1-mesa-dev 
    sudo apt-get install gambas3-dev gambas3-gb-image gambas3-gb-qt4 gambas3-gb-form gambas3-gb-desktop gambas3-gb-form-stock
    sudo apt-get install imagemagick
    sudo apt-get install git

Pobieranie źródeł:

    git clone https://github.com/eloaders/I-Nex.git

Budowanie pakietu deb:

    cd ./I-Nex
    fakeroot debian/rules build 
    fakeroot debian/rules binary
    cd ..
    sudo dpkg -i ./i-nex*.deb
