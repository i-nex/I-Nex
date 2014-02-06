%define name i-nex
%define version 0.6.0
%define release 1suse

Summary: I-Nex
Name: %{name}
Version: %{version}
Release: %{release}
Source0: %{name}-%{version}.tar.bz2
License: LGPL-3.0+
Group: System/X11/Utilities
BuildRoot: %{_tmppath}/%{name}-%{version}-${release}-buildroot
Prefix: %{_prefix}
BuildArch: x86_64
BuildRequires:  gambas3-devel
BuildRequires:  gambas3-gb-desktop
BuildRequires:  gambas3-gb-form
BuildRequires:  gambas3-gb-form-dialog
BuildRequires:  gambas3-gb-form-stock
BuildRequires:  gambas3-gb-gtk
BuildRequires:  gambas3-gb-gui
BuildRequires:  gambas3-gb-image
BuildRequires:  gambas3-gb-qt4
BuildRequires:  gambas3-gb-qt4-ext
BuildRequires:  gambas3-gb-settings
BuildRequires:  hicolor-icon-theme
BuildRequires:  lsb-release
BuildRequires:  net-tools
BuildRequires:  pciutils
BuildRequires:  procps
BuildRequires:  update-desktop-files
BuildRequires:  xorg-x11 >= 7.5
Requires: gambas3-runtime >= 3.5,
Requires: gambas3-runtime < 3.99.0
Requires: gambas3-gb-image >= 3.5
Requires: gambas3-gb-image < 3.99.0
Requires: gambas3-gb-qt4 >= 3.5
Requires: gambas3-gb-qt4 < 3.99.0
Requires: gambas3-gb-form >= 3.5
Requires: gambas3-gb-form < 3.99.0
Requires: gambas3-gb-desktop >= 3.5
Requires: gambas3-gb-desktop < 3.99.0
Requires: lsb-release
Requires: net-tools
Requires: pciutils
Requires: procps
Requires: update-desktop-files
Requires: xorg-x11 >= 7.5
Requires: freeglut
Requires: Mesa-demo-x
Requires: python
Requires: python-configobj >= 7.5
AutoReq: 0
AutoReqProv: 0

%description
I-Nex is an application that gathers information for hardware components available on your system and displays it using an user interface similar to the popular Windows tool CPU-Z.
  I-Nex can display information for the following components: 
  CPU, GPU, Motherboard, Sound, Hard disks, RAM, Network and USB as well as some system info like the hostname, Linux distribution and version, Xorg, GCC, GLX versions and Linux Kernel info.
  Besides being able to display hardware information, 
  I-Nex can also generate an advanced report for which you can select what to include and optionally send the report to a service such as Pastebin (and others). 
  It also features an option to take a screenshot of the I-Nex window directly from the application.
  The difference between I-Nex and the other hardware information GUI tools available for Linux is that the information is better organized and is displayed faster (than lshw-gtk for instance). 
  Also, the hardware information is presented in a way that’s easier to understand than other such tools.
This program is written in Gambas, so you will need Gambas to be installed.

%prep
rm -rf %{buildroot}

%setup -q -n i-nex

%build
gcc edid-decode.c -g -Wall -o inex-edid
gcc -o inex-cpuid cpu.c -static `pkg-config libcpuid --cflags --libs`
/usr/bin/gbc3 -e -a -g -t -p -m  src/i-nex
gba3 src/i-nex

%install
%{__install} -d %{buildroot}/%{_bindir}
%{__install} -p src/i-nex/i-nex.gambas %{buildroot}/%{_bindir}/i-nex
%{__install} -d %{buildroot}/usr/share/i-nex/
%{__install} -d %{buildroot}/usr/share/i-nex/pastebinit/
%{__install} -d %{buildroot}/usr/share/doc/i-nex/
%{__install} -d %{buildroot}/usr/bin/
%{__install} -d %{buildroot}/usr/share/i-nex/pastebinit/
%{__install} -p debian/changelog %{buildroot}/usr/share/i-nex/changelog
cp -R --preserve=timestamp pastebin.d %{buildroot}/usr/share/i-nex/pastebinit/pastebin.d
%{__install} -p debian/changelogs/changelog-0.4.6 %{buildroot}/usr/share/doc/i-nex/changelog-0.4.6
%{__install} -p debian/changelogs/changelog-0.4.8 %{buildroot}/usr/share/doc/i-nex/changelog-0.4.8
%{__install} -p debian/changelogs/changelog-0.4.8.1 %{buildroot}/usr/share/doc/i-nex/changelog-0.4.8.1
%{__install} -p debian/changelogs/changelog-0.5.0 %{buildroot}/usr/share/doc/i-nex/changelog-0.5.0
%{__install} -p debian/changelogs/changelog-0.5.1 %{buildroot}/usr/share/doc/i-nex/changelog-0.5.1
%{__install} -p debian/changelogs/changelog-0.5.2 %{buildroot}/usr/share/doc/i-nex/changelog-0.5.2
%{__install} -p debian/changelogs/changelog-0.5.4 %{buildroot}/usr/share/doc/i-nex/changelog-0.5.4
%{__install} -p debian/changelogs/changelog-0.5.6 %{buildroot}/usr/share/doc/i-nex/changelog-0.5.6
%{__install} -p debian/check_kernel %{buildroot}/usr/bin/check_kernel
%{__install} -p debian/i-nex-lspci %{buildroot}/usr/bin/i-nex-lspci
%{__install} -p inex-edid %{buildroot}/usr/bin/inex-edid
%{__install} -p inex-cpuid %{buildroot}/usr/bin/inex-cpuid
%{__install} -p pastebinit %{buildroot}/usr/share/i-nex/pastebinit/pastebinit
%{__install} -p pastebinit.xml %{buildroot}/usr/share/i-nex/pastebinit/pastebinit.xml

%{__install} -d %{buildroot}/%{_datadir}/pixmaps
%{__install} -d %{buildroot}/%{_datadir}/applications

cat << EOF > %{buildroot}%{_datadir}/applications/%{name}.desktop
[Desktop Entry]
Version=1.0
Name=I-Nex
Comment=I-Nex is an application that gathers information for hardware components available on your system and displays it using an user interface similar to the popular Windows tool CPU-Z.   I-Nex can display information for the following components:    CPU, GPU, Motherboard, Sound, Hard disks, RAM, Network and USB as well as some system info like the hostname, Linux distribution and version, Xorg, GCC, GLX versions and Linux Kernel info.   Besides being able to display hardware information,    I-Nex can also generate an advanced report for which you can select what to include and optionally send the report to a service such as Pastebin (and others).    It also features an option to take a screenshot of the I-Nex window directly from the application.   The difference between I-Nex and the other hardware information GUI tools available for Linux is that the information is better organized and is displayed faster (than lshw-gtk for instance).    Also, the hardware information is presented in a way that’s easier to understand than other such tools.
Exec=%{_bindir}/i-nex
Icon=i-nex.png
Terminal=false
Type=Application
StartupNotify=true
Categories=HardwareSettings;Settings;
EOF

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%{_bindir}/i-nex
%{_datadir}/i-nex/changelog
%{_datadir}/i-nex/pastebinit/pastebin.d
%{_datadir}/doc/i-nex/changelog-0.4.6
%{_datadir}/doc/i-nex/changelog-0.4.8
%{_datadir}/doc/i-nex/changelog-0.4.8.1
%{_datadir}/doc/i-nex/changelog-0.5.0
%{_datadir}/doc/i-nex/changelog-0.5.1
%{_datadir}/doc/i-nex/changelog-0.5.2
%{_datadir}/doc/i-nex/changelog-0.5.4
%{_datadir}/doc/i-nex/changelog-0.5.6
%{_bindir}/check_kernel
%{_bindir}/i-nex-lspci
%{_datadir}/i-nex/pastebinit/pastebinit
%{_datadir}/i-nex/pastebinit/pastebinit.xml

%{_datadir}/applications/%{name}.desktop

%changelog

* Sun Dec 08 2013 eloaders <eloaders@linux.pl> 0.5.8
- i-nex (0.5.8) unstable; urgency=medium
- * NEXT
-- eloaders <eloaders@linux.pl>  Wed, 27 Nov 2013 18:15:38 +0100

i-nex (0.5.8) unstable; urgency=medium

  * NEXT

 -- eloaders <eloaders@linux.pl>  Wed, 27 Nov 2013 18:15:38 +0100
 
i-nex (0.5.6) stable; urgency=medium

  * Chengelog for version 0.5.6 see file /usr/share/doc/i-nex/changelog-0.5.6

 -- eloaders <eloaders@yahoo.com>  Mon, 25 Nov 2013 01:33:11 +0100

i-nex (0.5.4) stable; urgency=low

  * Chengelog for version 0.5.4 see file /usr/share/doc/i-nex/changelog-0.5.4

 -- eloaders <eloaders@yahoo.com>  Fri, 18 Oct 2013 15:54:24 +0200
 
i-nex (0.5.2) stable; urgency=low

  * Chengelog for version 0.5.2 see file /usr/share/doc/i-nex/changelog-0.5.2

 -- eloaders <eloaders@yahoo.com>  Fri, 04 Jan 2013 19:48:32 +0100
 
i-nex (0.5.1) stable; urgency=low

  * Chengelog for version 0.5.1 see file /usr/share/doc/i-nex/changelog-0.5.1

 -- eloaders <eloaders@yahoo.com>  Sun, 02 Dec 2012 14:44:59 +0100

i-nex (0.5.0) stable; urgency=medium

  * Chengelog for version 0.5.0 see file /usr/share/doc/i-nex/changelog-0.5.0

 -- eloaders <eloaders@yahoo.com>  Thu, 29 Nov 2012 09:03:21 +0100

i-nex (0.4.8.1) stable; urgency=medium

  * Chengelog for version 0.4.8.1 see file /usr/share/doc/i-nex/changelog-0.4.8.1

 -- eloaders <eloaders@yahoo.com>  Fri, 13 Apr 2012 22:28:09 +0200

i-nex (0.4.8) stable; urgency=low

  * Chengelog for version 0.4.8 see file /usr/share/doc/i-nex/changelog-0.4.8

 -- eloaders <eloaders@yahoo.com>  Wed, 04 Apr 2012 18:12:01 +0200

i-nex (0.4.6) stable; urgency=low

  * Chengelog for version 0.4.6 see file /usr/share/doc/i-nex/changelog-0.4.6

 -- eloaders <eloaders@yahoo.com>  Sat, 03 Mar 2012 14:37:35 +0100

i-nex (0.4.5) unstable; urgency=low

  * Change version to 0.4.5 Unstable

 -- eloaders <eloaders@yahoo.com>  Tue, 14 Feb 2012 14:03:52 +0100

i-nex (0.4.4) stable; urgency=low

  * Fix Cache position
  * Fix distrodetect.class
  * Add gentoo
  * Update USB_Drives.module
  * Fix Bug in battery.module
    Detect BAT0 & BAT1
  * Battery Fix Spaces LTrim
  * Add new bug reporter
    Tomasz Przybył (FadeMind) dj.m.freex[at]gmail[dot]com www.gravatar.com/fademind
  * Fix CPU Tab → Frame CPU → Text Size, Padding, Autoresize, Expand.
  * New About dialog
  * Fix battery tab, All TextBox = ReadOnly True
  * Add botton to About: I-Nex home page
  * Fix CPU Tab, Text size 10,Bold
    Add HBox, → /Fix position
  * Change CPU Tab: Spacing = True to False
    Add to Battery tab: Progressbar for show XX%
  * Add support: Intel(R) Core(TM) i3
  * Fix bug dospam_uptime()
    [6] Type mismatch: wanted Integer, got string instead. Finfosys.dospam_uptime.414

 -- eloaders <eloaders@yahoo.com>  Thu, 02 Feb 2012 12:13:22 +0100

i-nex (0.4.3) unstable; urgency=low

  * Add detect removable
    0 = No
    1 = Yes
  * Add Ext range, range
  * Add detect:
    add_random
    discard_granularity
    discard_max_bytes
    discard_zeroes_data
    hw_sector_size
  * Add detect:
    max_hw_sectors_kb
    max_sectors_kb
    max_segments
    max_segment_size
    read_ahead_kb
    scheduler
  * Add info to About window
    Main developer
    Main bug reporter
  * Add new logo in about window.
    Special thanks to: mmaciek12 http://mmaciek12.deviantart.com/art/CPU-Icon-281444281
  * Fix icons in forms
  * Add depends: 
    dpkg (>= 1.16), grep (>= 2.9), mount (>= 2.19), procps, x11-xserver-utils (>= 7.6), lsb-release (>= 4.0), bash (>= 4.2), coreutils (>= 8.5), sed (>= 4.2), pciutils, x11-utils (>= 7.6), mesa-utils (>= 7.6), hostname
  * Fix CPU tab TextArea to TextBox
    Strings font = Bold
  * Fix disable overlay-scrollbar
    Add to debian/i-nex.desktop
    Exec=env LIBOVERLAY_SCROLLBAR=0 /usr/bin/i-nex.gambas
  * Add detect nVidia logo in Graphic tab
  * Fix Motherboard / Bios, System Tab
  * Fix CPU tab
  * Fix Used
    add sed -n '1p'
  * Fix font CPU Tab 
    Bold,10
  * Add HPanel, HBox
    Change size fonts, use system settings. Auto resize / expand
    CPU, Frame = The Main Information
    Graphic, Frame = OpenGl
  * Fix Bios. Detect Vendor,Date and Version
  * + 531 
    ProgressBar2.ToolTip = Disk_Drives.Used & "%"
    + 535
    ProgressBar2.ToolTip = "Unknown"
  * Fix debian/control Build-depends and Depends.
    Screenshot not based on gnome-screenshot.
    New modules and Forms for create screenshot.
  * Fix ScreenShot.form
    Set Icon and Text
  * Fix internet()
  * Fix uptime
  * Update Depends: dpkg (>= 1.15), grep (>= 2.5), mount (>= 2.17), procps, x11-xserver-utils (>= 7.5), lsb-release (>= 4.0), bash (>= 4.1), coreutils (>= 7.4), sed (>= 4.2), pciutils, x11-utils (>= 7.5), mesa-utils (>= 7.6), hostname
  * Add USB_Drives.module
    Fix ComboBox Read Only = True
  * Bzr 103 New Version 0.4.3

 -- eloaders <eloaders@yahoo.com>  Mon, 30 Jan 2012 19:02:50 +0100

i-nex (0.4.0) unstable; urgency=low

  * Add debian/control depends Gambas form stock icons
  * Remove: options, settings mangament, modules.
  * Fix version program. Not 0.3.5, correct to 0.3.3.
  * Fix Internet / Network
  * Battery support on netbooks is active if exist patch to get informations from info file.
  * Add Build Depends = gambas3-gb-dbus (>= 2.90.0)
  * Remove TextBox, TextLabel and fix Kernel Tab, System Tab
  * Move PictureBox on Graphic Tab.
  * Delete /src/i-nex/version, /src/i-nex/VERSION.
  * Label25.Text = Application.Name & " v: " & Application.version
  * Change: System Tab
  * Add support for:
                            Intel(R) Core(TM) i7 xxx (bug = black logo)
                            Intel(R) Core(TM) i5 xxx
  * Fix bug:
                            /usr/bin/gbc3 -e -a -g -t -p -m  src/i-nex
                            Finfosys.class:499: error: Unknown identifier: &1   Brightness
  * Add support: Intel(R) Celeron(R) M xxx
  * Add support: AMD Athlon(tm) 2 x3
  * Add Check for default display manager
    Dim default_display_manager As Boolean = Exist("/etc/X11/default-display-manager")

    Debug "Check for default display manager"
    If default_display_manager = True Then
     Label4.Visible = True
     TextBox22.Visible = True
     TextBox22.Text = File.Load("/etc/X11/default-display-manager")
     TextBox22.Text = Replace(TextBox22.Text, "\n", "")
     Debug "Default display manager is " & TextBox22.Text
    Endif
  * Add to Credits, Art and Graphic
    I-Nex logo by: mmaciek12
                         DeviantArt profile: http://mmaciek12.deviantart.com/
                         Mail: mmaciek123@gmail.com
  * Add Frames for: 0.2.x Version and 0.3.x Version
  * Fix Memory Tab: total, used, free, shared, buffers, cached +$1
    Thanks to Dariusz Duma
  * TextBox22 ReadOnly = True
  * Fix detect L3 Cache
    Thanks to lp:~dhor
  * Fix:
    Finfosys.dospam_uptime.435: #6: Type mismatch: wanted Float, got String instead
    1: Finfosys.dospam_uptime.435
  * 1: Fix Motherboard / Bios Tab, replace TextArea to TexBox
    2: Fix bios()
    Exec ["cat", "/sys/devices/virtual/dmi/id/board_vendor"] Wait To TextBox23.Text
    Exec ["cat", "/sys/devices/virtual/dmi/id/board_name"] Wait To TextBox24.Text
    Exec ["cat", "/sys/devices/virtual/dmi/id/bios_vendor"] Wait To TextBox25.Text
    Exec ["cat", "/sys/devices/virtual/dmi/id/bios_date"] Wait To TextBox26.Text
    Exec ["cat", "/sys/devices/virtual/dmi/id/bios_vendor"] Wait To TextBox27.Text
    TextBox23.Text = Replace(TextBox23.Text, "\n", "")
    TextBox24.Text = Replace(TextBox24.Text, "\n", "")
    TextBox25.Text = Replace(TextBox25.Text, "\n", "")
    TextBox26.Text = Replace(TextBox26.Text, "\n", "")
    TextBox27.Text = Replace(TextBox27.Text, "\n", "")
  * Add support Pentium(R) Dual-Core
    see http://opensource-tr.org/destek/thread-569-post-4227.html#pid4227
  * Fix last commit
    files added:
                src/i-nex/Processors/pentium_dual_core.png
  * Fix Device Tab, remove old functions and add new func and UI. More Information about disc sda,b,c....,x..
    New 0.4.0 Version

 -- eloaders <eloaders@yahoo.com>  Wed, 25 Jan 2012 00:20:29 +0100

i-nex (0.3.3) unstable; urgency=low

  * Add battery.module
  * Add Setting.module
  * Add pots
  * Add Options dialog
  * Update and add initial support for battery on netbooks / laptops
  * Update project gambas files
  * Update control Build depends and binary depends
  * Update changelog for version 0.3.3

 -- eloaders <eloaders@yahoo.com>  Sat, 14 Jan 2012 15:13:07 +0100

i-nex (0.3.1) unstable; urgency=low

  * Więcej opcji w głównej karcie
  * Wsparcie dla kart ATI, wyświetlania grafiki
  * Wsparcie dla większej ilości procesorów amd

 -- eloaders <eloaders@yahoo.com>  Tue, 03 Jan 2012 12:00:00 +0000

i-nex (0.3.0) unstable; urgency=low

  * Gambas3

 -- eloaders <eloaders@yahoo.com>  Tue, 03 Jan 2012 12:00:00 +0000

i-nex (0.2.4) oneiric; urgency=low

  * Zmiana nazwy
  * Zmiana plików w debian/

 -- eloaders <eloaders@yahoo.com>  Sat, 22 Oct 2011 11:49:59 +0200

silicon (0.2.3) oneiric; urgency=low

  * Change debian/control and compat
  * Change debian/chanelog
  * Dodano wykrywanie do 12 procesorów bądź rdzeni
  * Dodanie zależności debian/control
  * Nowy formularz wyświetlający informacje o pakietach

 -- eloaders <eloaders@yahoo.com>  Mon, 26 Sep 2011 15:48:00 +0200

silicon (0.2.1~eloaders) oneiric; urgency=low

  * Dodano opcję zmiany rozdzielczości
  * Dodano opcję usuwania kerneli
  * Usunięto nieużywane pliki graficzne z programu
  * Zmieniono ikony zakładek

 -- eloaders <eloaders@yahoo.com>  Sun, 25 Sep 2011 12:43:00 +0200

silicon (0.1.99~eloaders~natty) natty; urgency=low

  * Przebudowano pozycję Kernel
  * Dodatkowy progressbar informujący o użyciu pamięci swap w pozycji Pamięć
  * Wykrywanie informacji o procesorze do 6 rdzeni oraz całkowite przebudowanie kodu w tej części

 -- eloaders <eloaders@yahoo.com>  Fri, 23 Sep 2011 19:50:00 +0200

silicon (0.1.9-1~eloaders) natty; urgency=low

  * Naprawiono wyświetlanie grafiki dla procesorów AMD Athlon 2 x2 2xx

 -- eloaders <eloaders@yahoo.com>  Sun, 18 Sep 2011 14:16:00 +0200

silicon (0.1.8-0ubuntu2) natty; urgency=low

  * Naprawiono pozycje dysk oraz progressbary.
  * Naprawiono / Ulepszono wykrywanie domyślnej przeglądarki.
  * Dodano wstępny button generowania raportu. (Domyślnie niewidoczny)

 -- eloaders <eloaders@yahoo.com>  Sun, 06 Mar 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Naprawiono wyświetlanie nazwy dystrybucji w zakładce system.
  * Przebudowano i dodano dodatkowe opcje wyświetlania w zakładce pamięć.

 -- eloaders <eloaders@yahoo.com>  Thu, 17 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Zmieniono pozycję system oraz grafika.

 -- eloaders <eloaders@yahoo.com>  Wed, 16 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Zmiana nazwy
  * Test build

 -- eloaders <eloaders@yahoo.com>  Wed, 16 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Zmieniono wygląd zakładki system.
  * Dodano informacje o ilości zainstalowanych pakietów.
  * Naprawiono wyświetlanie zakładki dysk.

 -- eloaders <eloaders@yahoo.com>  Tue, 15 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Dodano progress bar informujący o zajętym miejscu na dysku jak i informacja o wolnym miejscu.
  * Zmieniono wygląd pozycji bios.
  * Dodano progress bar w zakładce pamięć.
  * Dodano informacje o pojemności głównego dysku.

 -- eloaders <eloaders@yahoo.com>  Mon, 14 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Poprawiono wyświetlanie grafiki / stickera procesora

 -- eloaders <eloaders@yahoo.com>  Sat, 12 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Dodano ikony do zakładek.
  * Naprawiono karte dźwięk. Wyświetla wszystkie urządzenia odpowiedzialne za dźwięk.
  * Dodano wykrywanie grafiki, sticera procesora.
  * Dodano button info odsyłający do strony o szczegółowych informacjach o procesorze.
  * Zmieniono tekst strona domowa na button.
  * Zmieniono wygląd zakładki system.

 -- eloaders <eloaders@yahoo.com>  Fri, 11 Feb 2011 12:00:00 +0200

silicon (0.1.8-0ubuntu1) natty; urgency=low

  * Usunięto opcje zmiany tapety.
  * Usunięto wykrywanie tapety pulpitu.
  * Zmniejszono użycie procesora poprzez usunięcie timer.
  * Dodano buttony odświerz.
  * Oraz naprawiono inne błędy których nie pamiętam.

 -- eloaders <eloaders@yahoo.com>  Tue, 08 Feb 2011 12:00:00 +0200


