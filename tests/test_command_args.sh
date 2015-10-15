#
# This bash script verifies that command line arguments are working right
#


# Binary directory
BINDIR=bin


# Binary file
BINARY=jsoncat


# Used to not print to stdout and stderr
LIMBO=/dev/null


# Colors definition
BROWN="\e[1;33m";
BLUE="\e[1;34m";
GRAY="\e[1;30m";
RED="\e[1;31m";
GREEN="\e[1;32m";
END_COLOR="\e[0m";


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


# --------------------  F U N C T I O N S ---------------------- #


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
    sleep 0.5;
}


#
# Function to assert when program should fail
#
assert_command_fail ()
{
    if [ "$1" -ne "0" ]; then
        assert_command "0"; # Success
    else
        assert_command "$1";
    fi;
}


#
# Check if the executable file exists
#
binary_exists ()
{
    [ -x "${BINDIR}/${BINARY}" ] || {
        echo -en "Binary file do not exists. Try to compile the project\n";
        exit 1;
    }
}


# -------------------- T E S T S ------------------------ #


# Check binary
binary_exists;


#
# Prints the starting tests message
#
echo -en "${BROWN}*** ";
echo -en "${BLUE}Testing ${BROWN}${BINDIR}/${BINARY} ";
echo -en "${BLUE}command line options${END_COLOR}";
echo -en "${BROWN} ***${END_COLOR}\n\n";



#
# Verifies -v command line options
#
test_message "Prints program version with -v option";
./${BINDIR}/${BINARY} -v | grep "version" &> ${LIMBO};
assert_command $?;



#
# Verifies --version command line option
#
test_message "Prints program version with --version option";
./${BINDIR}/${BINARY} --version | grep "version" &> ${LIMBO};
assert_command $?;



#
# Verifies -h command line option
#
test_message "Prints program help with -h option";
./${BINDIR}/${BINARY} -h | grep "Description" &> ${LIMBO};
assert_command $?;



#
# Verifies --help command line option
#
test_message "Prints program help with --help option";
./${BINDIR}/${BINARY} --help | grep "Description" &> ${LIMBO};
assert_command $?;



#
# Verifies the use of stdin as the input json
#
test_message "Use stdin as the input json to parse";
echo "{'test': true}" | ${BINDIR}/${BINARY} &> ${LIMBO};
assert_command $?;



#
# Tests no such file or directory
#
test_message "Validate if file does not exists";
./${BINDIR}/${BINARY} "some_invalid_file_name.json" &> ${LIMBO};
assert_command_fail $?;



#
# Prints the results of the tests
#
echo -en "${BROWN}--${END_COLOR}\n\n";
echo -en "${BLUE}Successful tests:\t${GREEN}${N_SUCCESS}${END_COLOR}\n";
echo -en "${BLUE}Failed tests:\t\t${RED}${N_FAILED}${END_COLOR}\n";
echo -en "\n${BLUE}Total tests:\t\t${END_COLOR}${N_TESTS}\n";
