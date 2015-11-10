#
# spec file for package jsoncat
#
# Copyright (c) 2015 SUSE LINUX Products GmbH, Nuernberg, Germany.
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

Name:           jsoncat
Version:        0.1.0
Release:        1%{?dist}
License:        GPLv2+
Summary:        Json pretty-print parser based on a recursive lexical analyser
Url:            https://github.com/pantuza/%{name}
Source:         %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
Json pretty-print parser based on a recursive lexical analyser.
The parser was based on the specification defined at json.org.
The input file is parsed to build a json object.
If the object is correct, it will be pretty-printed to standard output.

%prep
%autosetup -n %{name}

%build
make CFLAGS="%{optflags}" %{?_smp_mflags}

%install
mkdir -p %{buildroot}%{_bindir}
install bin/jsoncat %{buildroot}%{_bindir}

%files
%{_bindir}/jsoncat

%changelog
