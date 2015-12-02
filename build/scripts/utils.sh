#!/bin/bash


ECHO=$(which echo);
ECHOOPTS="-en";

CAT=$(which cat);

GREP=$(which grep);

CUT=$(which cut);

SED=$(which sed);
SEDOPTS="-i";

GIT=$(which git);


# Directories
SPEC_DIR="home:pantuza/jsoncat";


# Files
SRC_VERSION_FILE="../src/messages.h";
SPEC_FILE="${SPEC_DIR}/jsoncat.spec"
