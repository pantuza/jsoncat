#!/bin/bash

zypper update -y

zypper install -y wget tar gcc make rpm-build rpmlint

cd rpmbuild

rpmbuild -ba jsoncat.spec
