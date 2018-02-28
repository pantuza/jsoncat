#!/bin/bash

version="$1"

apt update -y

apt install -y devscripts chrpath

cd jsoncat-${version}

debuild -uc -us
