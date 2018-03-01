#!/bin/bash

OS=$(uname -s);

ECHO=$(which echo);
ECHOOPTS="-en";

CAT=$(which cat);

GREP=$(which grep);

CUT=$(which cut);

SED=$(which sed);
if [ "$OS" = "Darwin" ]; then
    SED=$(which gsed);
fi
SEDOPTS="-i";

GIT=$(which git);


# Directories
SPEC_DIR="rpmbuild";


# Files
SRC_VERSION_FILE="../src/messages.h";
SPEC_FILE="${SPEC_DIR}/jsoncat.spec"
