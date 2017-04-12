#!/bin/bash

#
# Bash script with utils variables and function for tests
#



# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                             #
#                       V  A  R  I  A  B  L  E  S                             #
#                                                                             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


# Binary directory
BINDIR=bin


# Tests dir
TESTDIR=tests


# Binary file
BINARY=jsoncat


# Used to not print to stdout and stderr
LIMBO=/dev/null


# String for the MAC OS X operationg system
MAC_OS_X_OSTYPE="Darwin";

# Color prefix for Linux based distributions
COLOR_PREFIX="e";

# Adding color prefix for Mac OS X
OS=$(uname -s);

[ "${OS}" == "${MAC_OS_X_OSTYPE}" ] && {
    COLOR_PREFIX="033";
}


# Colors definition
BROWN="\\${COLOR_PREFIX}[1;33m";
BLUE="\\${COLOR_PREFIX}[1;34m";
GRAY="\\${COLOR_PREFIX}[1;30m";
RED="\\${COLOR_PREFIX}[1;31m";
GREEN="\\${COLOR_PREFIX}[1;32m";
END_COLOR="\\${COLOR_PREFIX}[0m";


# Success message
SUCCESS="${GREEN}OK${END_COLOR}";


# Fail message
FAIL="${RED}FAIL${END_COLOR}";


# Number of executed tests
N_TESTS=0;


# Number of successful tests
N_SUCCESS=0;


# Number of failed tests
N_FAILED=0;




# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                             #
#                       F  U  N  C  T  I  O  N  S                             #
#                                                                             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #



#
# Check if the executable file exists
#
binary_exists ()
{
    [ -x "${BINDIR}/${BINARY}" ] || {
        echo -en "${RED}Binary file do not exists. " \
                 "Try to compile the project${END_COLOR}\n";
        exit 1;
    }
}



#
# Prints the starting tests message
#
start_message ()
{
    echo -en "\n${BLUE}Testing ${BROWN}${BINDIR}/${BINARY} ";
    echo -en "${BLUE}$1${END_COLOR}\n\n";
}



#
# Prints the results of the tests
#
result_message ()
{
    echo -en "${BROWN}--${END_COLOR}\n";
    echo -en "${BLUE}Successful tests:\t${GREEN}${N_SUCCESS}${END_COLOR}\n";
    echo -en "${BLUE}Failed tests:\t\t${RED}${N_FAILED}${END_COLOR}\n";
    echo -en "${BLUE}Total tests:\t\t${END_COLOR}${N_TESTS}\n";
}



#
# Function that prints the test message
#
test_message ()
{
    echo -en "${GRAY}${1}: ";
}



#
# Function to verify if the test passed
#
assert_command ()
{
    N_TESTS=$((N_TESTS + 1));

    if [ "$1" == "0" ]; then
        echo -en "${SUCCESS}\n";
        N_SUCCESS=$((N_SUCCESS + 1));
    else
        echo -en "${FAIL}\n";
        N_FAILED=$((N_FAILED + 1));
    fi;
    # Will sleep just for pretty print the tests
    sleep 0.2;
}



#
# Function to assert when program should fail
#
assert_command_fail ()
{
    if [ "$1" -ne "0" ]; then
        assert_command "0"; # Success
    else
        assert_command "1"; # Fail
    fi;
}



#
# Function that verifies inside the json the value
#
has_value ()
{
    [ -z "$2" ] && { # Verify only $2 because the string $1 can be empty
        echo -en "${RED}Missing arguments for has_str test utility function" \
                 "${END_COLOR}\n";
        exit 1;
    }
    echo -en "{\"test\": $1}" | ${BINDIR}/${BINARY} | grep -F $2 &> ${LIMBO}
}



#
# Function that verifies inside string $1 if string $2 matches on grep
#
has_str ()
{
    has_value "$1" "$2"
}
