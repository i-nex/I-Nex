
%define gittag fa87a5e
%define gitlong fa87a5e183a3809ded89ecb3efde4e94837c5736
%define gitdate 20161112

Name:           libcpuid
Version:        0.4.0
Release:        %{gitdate}+git%{?gittag}%{?dist}
Summary:        Provides CPU identification for x86
License:        BSD-2-Clause
Group:          Development/Libraries/C and C++
Url:            https://github.com/anrieff/libcpuid
Source0:        https://www.github.com/anrieff/libcpuid/archive/%{gittag}.zip#/libcpuid-%{gitlong}.zip

BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  libtool
BuildRequires:  pkgconfig
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
Libcpuid provides CPU identification for the x86 (and x86_64).


%package devel
Summary:        Development files for %{name}
Group:          Development/Libraries/C and C++
Requires:       %{name}14 = %{version}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.
For details about the programming API, please see the docs
on the project's site (http://libcpuid.sourceforge.net/)


%package -n %{name}14
Summary:        Provides CPU identification for x86
Group:          Development/Libraries/C and C++

%description -n %{name}14
Libcpuid provides CPU identification for the x86 (and x86_64).


%prep
%setup -q -n libcpuid-%{gitlong}


%build
libtoolize
autoreconf --install
%configure
make V=1 %{?_smp_mflags}


%install
make V=1 DESTDIR=%{buildroot} install
# WARNING: empty dependency_libs variable. remove the pointless .la
rm %{buildroot}%{_libdir}/*.la


%post -n %{name}14 -p /sbin/ldconfig

%postun -n %{name}14 -p /sbin/ldconfig


%files -n %{name}14
%defattr(-,root,root)
%{_libdir}/%{name}.so.*
%doc %{_mandir}/man*/*cpu*

%files devel
%defattr(-,root,root)
%{_bindir}/cpuid_tool
%{_includedir}/%{name}
%{_libdir}/%{name}*
%exclude %{_libdir}/%{name}.so.*
%{_libdir}/pkgconfig/%{name}.pc

%changelog


