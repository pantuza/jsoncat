#!/bin/bash

#
# This bash script parses jsons with constants like true, false, null, etc
#


# Include tests utils
. tests/utils.sh


# -------------------- T E S T S ------------------------ #


# Check binary
binary_exists;


# Prints start message
start_message "Parsing constants";


#
# Tests true constant
#
CONST="true";
test_message "Parsing true constant as value";
has_value "true" $CONST;
assert_command $?;



#
# Tests true constant
#
CONST="truexxx";
test_message "Parsing wrong true ($CONST) constant as value that should fail";
has_value "true" $CONST;
assert_command_fail $?;


#
# Tests true constant
#
CONST="xxxtrue";
test_message "Parsing wrong true ($CONST) constant as value that should fail";
has_value "true" $CONST;
assert_command_fail $?;


#
# Tests false constant
#
CONST="false";
test_message "Parsing false constant as value";
has_value "false" $CONST;
assert_command $?;



#
# Tests false constant
#
CONST="falsexxx";
test_message "Parsing wrong false ($CONST) constant as value that should fail";
has_value "false" $CONST;
assert_command_fail $?;



#
# Tests false constant
#
CONST="xxxfalse";
test_message "Parsing wrong false ($CONST) constant as value that should fail";
has_value "false" $CONST;
assert_command_fail $?;



#
# Tests null constant
#
CONST="null";
test_message "Parsing null constant as value";
has_value "null" $CONST;
assert_command $?;



#
# Tests null constant
#
CONST="nullxxx";
test_message "Parsing wrong null ($CONST) constant as value that should fail";
has_value "null" $CONST;
assert_command_fail $?;



#
# Tests null constant
#
CONST="xxxnull";
test_message "Parsing wrong null ($CONST) constant as value that should fail";
has_value "null" $CONST;
assert_command_fail $?;



# Prints tests result
result_message;
