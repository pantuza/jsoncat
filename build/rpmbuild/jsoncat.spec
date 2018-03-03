#
# spec file for package jsoncat
#


# Supress unpackaged files message
%define _unpackaged_files_terminate_build 0



Name:           jsoncat
Version:		0.7.1
Release:        1%{?dist}
License:        GPL-2.0+
Summary:        Json pretty-print parser based on a recursive lexical analyser
Url:            https://github.com/pantuza/%{name}
Source:         %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Group:          Applications/System
BuildArch:      noarch


%description
Json pretty-print parser based on a recursive lexical analyser.
The parser was based on the specification defined at json.org.
The input file is parsed to build a json object.
If the object is correct, it will be pretty-printed to standard output.


%prep
# Extract archive to start build process
%setup -c -n %{name}-%{version}.tar.gz


%build
# Builds the entire code base
cd %{name}-%{version}
make CFLAGS="%{optflags}" %{?_smp_mflags}


%install
# Clear build root
rm -rf $RPM_BUILD_ROOT

cd %{name}-%{version}

# Installs binary on system path
mkdir -p %{buildroot}%{_bindir}
install bin/jsoncat %{buildroot}%{_bindir}

# Installs man pages for jsoncat
mkdir -p %{buildroot}%{_mandir}/man1
install -m 644 docs/jsoncat.1 %{buildroot}%{_mandir}/man1/jsoncat.1

# Installs readme on system documentation path
install -m 644 README.md %{buildroot}


# Run test suite using the compiled binary
%check
cd %{name}-%{version}
make test


%files
%defattr(-,root,root,-)
%{_bindir}/jsoncat
%{_mandir}/man1/jsoncat.1.gz

%doc $RPM_BUILD_ROOT/README.md


%changelog
* Thu Mar 1 2018 Gustavo Pantuza <gustavopantuza@gmail.com> 0.7.0
- First RPM package of jsoncat tool
