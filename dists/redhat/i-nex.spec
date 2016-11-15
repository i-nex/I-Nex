# Please set the 3 %define values below based on the source code GIT tag - https://github.com/eloaders/I-Nex/commits/master
# Also, the source should be named ~/rpmbuild/SOURCES/I-Nex-(gitlong).zip

# The gittag version below ensures that the source tag points to the latest commit in GitHub e.g. latest commit as of 14 Aug 2016 is f57f4a5

%define gittag a75faf8
%define gitlong a75faf816744066a428c9dce9e0d1d76dccc076f
%define gitdate 20161115

Name:           i-nex
Version:        7.6.0
Release:        %{gitdate}.git%{?gittag}%{?dist}
Summary:        System information tool

License:        GPL-3.0+
Url:            http://i-nex.linux.pl
Group:          System/X11/Utilities
Source0:        https://github.com/eloaders/I-Nex/archive/%{gittag}.zip#/I-Nex-%{gitlong}.zip

BuildRequires:  ImageMagick
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  fdupes
BuildRequires:  gambas3-devel >= 3.8.4
BuildRequires:  gambas3-gb-desktop >= 3.8.4
BuildRequires:  gambas3-gb-form >= 3.8.4
BuildRequires:  gambas3-gb-form-dialog >= 3.8.4
BuildRequires:  gambas3-gb-form-stock >= 3.8.4
BuildRequires:  gambas3-gb-gtk >= 3.8.4
BuildRequires:  gambas3-gb-gui >= 3.8.4
BuildRequires:  gambas3-gb-image >= 3.8.4
BuildRequires:  gambas3-gb-qt5 >= 3.8.4
BuildRequires:  gambas3-gb-qt5-opengl >= 3.8.4
BuildRequires:  gambas3-gb-qt5-webkit >= 3.8.4
BuildRequires:  gambas3-gb-settings >= 3.8.4
BuildRequires:  hicolor-icon-theme
BuildRequires:  net-tools
BuildRequires:  pkgconfig
BuildRequires:  pkgconfig(libcpuid) >= 0.4.0
BuildRequires:  pkgconfig(libprocps)
BuildRequires:  pkgconfig(x11)
BuildRequires:  pkgconfig(gl)
BuildRequires:  pkgconfig(xext)
BuildRequires:  pciutils
BuildRequires:  procps-ng
BuildRequires:  procps-ng-devel
BuildRequires:  xz
Requires:       %{name}-data = %{version}
Requires:       gambas3-gb-desktop >= 3.8.4
Requires:       gambas3-gb-form >= 3.8.4
Requires:       gambas3-gb-form-dialog >= 3.8.4
Requires:       gambas3-gb-form-stock >= 3.8.4
Requires:       gambas3-gb-gtk >= 3.8.4
Requires:       gambas3-gb-gui >= 3.8.4
Requires:       gambas3-gb-image >= 3.8.4
Requires:       gambas3-gb-qt5 >= 3.8.4
Requires:       gambas3-gb-qt5-opengl >= 3.8.4
Requires:       gambas3-gb-qt5-webkit >= 3.8.4
Requires:       gambas3-gb-settings >= 3.8.4
Requires:       gambas3-runtime >= 3.8.4
Requires:       procps-ng
Requires:       libcpuid14 >= 0.4.0
# Recommends:     i2c-tools
# Recommends:     glx-utils
# Recommends:     pastebinit >= 1.5

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
%setup -q -n I-Nex-%{gitlong}

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
       I-Nex/i-nex/.src/Reports/MPastebinit.module
%__cp I-Nex/i-nex/logo/i-nex.0.4.x.png $RPM_SOURCE_DIR/%{name}.png
%{__sed} -e 's|env LIBOVERLAY_SCROLLBAR=0 /usr/bin/i-nex.gambas|i-nex|' \
         -e '/^Icon=/s|=.*|=%{name}|' debian/%{name}.desktop > %{name}.desktop

%build
cd I-Nex
autoreconf -fiv
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

# Using %%doc macro, so files not needed
rm -rf %{buildroot}%{_datadir}/doc/%{name}

%fdupes -s %{buildroot}%{_datadir}

%files
%defattr(-,root,root,-)
%doc debian/copyright I-Nex/ChangeLog I-Nex/COPYING 
%doc I-Nex/INSTALL I-Nex/NEWS I-Nex/README
%{_bindir}/%{name}-*
%doc %{_mandir}/man*/%{name}*

%files  data
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_bindir}/%{name}.gambas
%{_datadir}/applications/%{name}*.desktop
%{_datadir}/pixmaps/%{name}*
%doc debian/changelog* I-Nex/ChangeLog
%doc I-Nex/AUTHORS I-Nex/COPYING I-Nex/NEWS I-Nex/README
/lib/udev/rules.d/i2c_smbus.rules

%changelog
* Wed Aug 17 2016 <GitHub/eloaders/I-Nex/alphastar868>
- New SPEC file for 2016 RedHat RPM distros
