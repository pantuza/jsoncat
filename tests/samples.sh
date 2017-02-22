#!/bin/bash

#
# This bash script parses all samples files and verify execution result
#


# Include tests utils
. tests/utils.sh


# -------------------- T E S T S ------------------------ #


# Check binary
binary_exists;


# Prints start message
start_message "Parsing samples files that do not fail";


#
# Parses each json file in the samples directory
#
while read file_name;
do
    test_message "Parsing file $file_name";
    ./${BINDIR}/${BINARY} $file_name &> ${LIMBO};
    assert_command $?;

# We pass the result of ls as the stdin to the while. It makes the
# utils.sh variables referenced inside the while scope
done < <(ls ${TESTDIR}/samples/ok/*.json);



# Prints start message
start_message "Parsing samples files that fails";

#
# Parses each json file in the samples directory
#
while read file_name;
do
    test_message "Parsing file $file_name";
    ./${BINDIR}/${BINARY} $file_name &> ${LIMBO};
    assert_command_fail $?;

# We pass the result of ls as the stdin to the while. It makes the
# utils.sh variables referenced inside the while scope
done < <(ls ${TESTDIR}/samples/nok/*.json);

# Prints tests result
result_message;
