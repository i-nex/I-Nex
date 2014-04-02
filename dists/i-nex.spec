#
# spec file for package i-nex
#
# Copyright (c) 2014 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


Name:           i-nex
Version:        0.6.4
Release:        1
Summary:        System information tool

License:        GPL-3.0+
Url:            http://i-nex.linux.pl
Group:          System/X11/Utilities
Source0:        https://github.com/eloaders/I-Nex/archive/%{version}.tar.gz

BuildRequires:  ImageMagick
%if 0%{?suse_version} <= 1210
BuildRequires:  freeglut
%else
BuildRequires:  Mesa-demo-x
%endif
BuildRequires:  fdupes
BuildRequires:  gambas3-devel >= 3.5.0
BuildRequires:  gambas3-gb-desktop >= 3.5.0
BuildRequires:  gambas3-gb-form >= 3.5.0
BuildRequires:  gambas3-gb-form-dialog >= 3.5.0
BuildRequires:  gambas3-gb-form-stock >= 3.5.0
BuildRequires:  gambas3-gb-gtk >= 3.5.0
BuildRequires:  gambas3-gb-gui >= 3.5.0
BuildRequires:  gambas3-gb-image >= 3.5.0
BuildRequires:  gambas3-gb-qt4 >= 3.5.0
BuildRequires:  gambas3-gb-qt4-ext >= 3.5.0
BuildRequires:  gambas3-gb-settings >= 3.5.0
BuildRequires:  hicolor-icon-theme
%if 0%{?suse_version}
BuildRequires:  lsb-release
%endif
BuildRequires:  net-tools
%if 0%{?suse_version}
BuildRequires:  openSUSE-release
%endif
BuildRequires:  pkgconfig
BuildRequires:  pkgconfig(libcpuid)
BuildRequires:  pkgconfig(libprocps)
BuildRequires:  pkgconfig(x11)
BuildRequires:  pkgconfig(gl)
BuildRequires:  pkgconfig(xext)
BuildRequires:  pciutils
BuildRequires:  procps
BuildRequires:  update-desktop-files
%if 0%{?suse_version}
BuildRequires:  xorg-x11 >= 7.5
%endif
BuildRequires:  xz
Requires:       %{name}-data = %{version}
Requires:       gambas3-gb-desktop >= 3.5.0
Requires:       gambas3-gb-form >= 3.5.0
Requires:       gambas3-gb-form-dialog >= 3.5.0
Requires:       gambas3-gb-form-stock >= 3.5.0
Requires:       gambas3-gb-geom >= 3.4.0
Requires:       gambas3-gb-gtk >= 3.5.0
Requires:       gambas3-gb-gui >= 3.5.0
Requires:       gambas3-gb-image >= 3.5.0
Requires:       gambas3-gb-qt4 >= 3.5.0
Requires:       gambas3-gb-qt4-ext >= 3.5.0
Requires:       gambas3-gb-settings >= 3.5.0
Requires:       gambas3-runtime >= 3.5.0
%if 0%{?suse_version}
%if 0%{?suse_version} <= 1210
Recommends:     freeglut
%else
Recommends:     Mesa-demo-x
Recommends:     xrandr
%endif
Recommends:     lsb-release
Recommends:     net-tools
Recommends:     pastebinit >= 1.3
Recommends:     pciutils
Recommends:     procps
Recommends:     python
Recommends:     python-configobj
Recommends:     xorg-x11 >= 7.5
%endif

%description
An application that gathers information for hardware
components available on your system and displays it using an
user interface similar to the popular Windows tool CPU-Z.
pastebinit required for publishing the hardware configuration.

%package        data
Summary:        I-Nex noarch data
BuildArch:      noarch
Requires:       %{name} = %{version}

%description    data
I-Nex arch independent data.

%prep
%setup -q -n I-Nex-%{version}
# A hack to be able to run the program via the name execution.
#+ some info tools are under *sbin
cat > %{name}.sh <<HERE
#!/bin/sh

export LIBOVERLAY_SCROLLBAR=0 PATH=/sbin:/usr/sbin:\$PATH
exec %{_bindir}/%{name}.gambas
HERE

#using system's pastebinit
%__sed -i \
       '\|/usr/share/i-nex/pastebinit/|s|/usr/share/i-nex/pastebinit/||' \
       src/i-nex/.src/Reports/MPastebinit.module
%__cp src/i-nex/logo/i-nex.0.4.x.png $RPM_SOURCE_DIR/%{name}.png
%{__sed} -e 's|env LIBOVERLAY_SCROLLBAR=0 /usr/bin/i-nex.gambas|i-nex|' \
         -e '/^Icon=/s|=.*|=%{name}|' debian/%{name}.desktop > %{name}.desktop

%build
cd src
%configure
cd ..
make \
     %{?_smp_mflags} \
     STATIC=false \
     V=1 \
     additional_confflags+="%{optflags}"

%install
make V=1 DESTDIR=%{buildroot} install

# A hack to be able to run the program via the name execution.
%{__install} -D -m 755 %{name}.sh %{buildroot}%{_bindir}/%{name}

# Let's use %%doc macro.
rm -rf %{buildroot}%{_datadir}/doc/%{name}

# Let's use system's `pastebinit`.
rm -rf %{buildroot}%{_datadir}/%{name}/pastebinit

%if 0%{?suse_version}
%suse_update_desktop_file -r %{name} 'System;HardwareSettings;'
%endif

%fdupes -s %{buildroot}%{_datadir}


%post   data
%desktop_database_post

%postun data
%desktop_database_postun


%files
%defattr(-,root,root,-)
%doc docs/copyright docs/I-Nex.LICENSE src/COPYING
%{_bindir}/%{name}-*
%doc %{_mandir}/man*/%{name}*


%files  data
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_bindir}/%{name}.gambas
%{_datadir}/applications/%{name}.desktop
%{_datadir}/pixmaps/%{name}*
%doc debian/changelog* changelogs/changelog*
%doc src/AUTHORS src/ChangeLog src/README

%changelog
