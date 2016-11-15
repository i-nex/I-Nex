Name:           pastebinit
Version:        1.5
Release:        2%{?dist}
Summary:        Send anything you want directly to a pastebin from the command line

Group:          Applications/Internet
License:        GPLv2+
URL:            https://launchpad.net/pastebinit
Source0:        http://launchpad.net/%{name}/trunk/%{version}/+download/%{name}-%{version}.tar.gz

BuildArch:      noarch
BuildRequires:  docbook-style-xsl libxslt gettext
Requires:       python-configobj

%description
A software that lets you send anything you want directly to a
pastebin from the command line.  This software lets you send a file
or simply the result of a command directly to the pastebin you want
(if it's supported) and gives you the URL in return.

%prep
%setup -q

sed -i "s|pastebin.d|%{name}|g" %{name} README

%build
# Generate the man page from docbook xml
xsltproc -''-nonet %{_datadir}/sgml/docbook/xsl-stylesheets*/manpages/docbook.xsl pastebinit.xml

# Build translation
pushd po
make
popd

%install
rm -rf %{buildroot}

mkdir -p %{buildroot}%{_datadir}/
mkdir -p %{buildroot}%{_sysconfdir}/%{name}/

cp -a pastebin.d %{buildroot}%{_datadir}
rm %{buildroot}%{_datadir}/pastebin.d/yourpaste.net.conf
mv %{buildroot}%{_datadir}/pastebin.d/ %{buildroot}%{_datadir}/%{name}/

install -m 0755 -D -p %{name} %{buildroot}%{_bindir}/%{name}
install -m 0644 -D -p %{name}.1 %{buildroot}%{_mandir}/man1/%{name}.1

# Add symlink to /usr/share/pastebin.d/
ln -sf %{_datadir}/%{name} %{buildroot}/%{_datadir}/pastebin.d

# Install translations
pushd po
cp -a mo %{buildroot}%{_datadir}/locale/
popd

%find_lang %{name}

%clean
rm -rf %{buildroot}


%files -f %{name}.lang
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1.*
%{_datadir}/%{name}/
%{_datadir}/pastebin.d
%dir %{_sysconfdir}/%{name}/
%doc README COPYING
%doc pastebin.d/yourpaste.net.conf

%changelog
* Mon Nov 14 2016 alphastar868 
- Restore /usr/share/pastebin.d/ as symlink

