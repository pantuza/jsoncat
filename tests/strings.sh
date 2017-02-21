#!/bin/bash

#
# This bash script parses different kinds of strings
#


# Include tests utils
. tests/utils.sh


# -------------------- T E S T S ------------------------ #


# Check binary
binary_exists;


# Prints start message
start_message "Parsing strings";


#
# Tests an empty string
#
STR="\"\"";
test_message "Parsing an empty string";
has_str "\"\"" $STR;
assert_command $?;

#
# Tests a string with numbers
#
STR="42";
test_message "Parsing a string with a number";
has_str "42" $STR;
assert_command $?;


#
# Tests a string with an object
#
STR="\"{\\\"a\\\":10}\"";
test_message "Parsing a string with an object";
has_str "\"{\\\"a\\\":10}\"" $STR;
assert_command $?;



#
# Tests a string with an array
#
STR="\"[10, 12.2, 23]\"";
test_message "Parsing a string with an array";
has_str "\"[10, 12.2, 23]\"" $STR;
assert_command $?;



#
# Tests a string with null
#
STR="null";
test_message "Parsing a string with the null constant";
has_str "null" $STR;
assert_command $?;



#
# Tests a string with true
#
STR="true";
test_message "Parsing a string with true as the value";
has_str "true" $STR;
assert_command $?;



#
# Tests a string with false as value
#
STR="false";
test_message "Parsing a string with false as the value";
has_str "false" $STR;
assert_command $?;



#
# Tests a string with scaped text
#
STR="\"string\"";
test_message "Parsing a escaped string with \"";
has_str "\"string\"" $STR;
assert_command $?;



#
# Tests a string with lots of string open characters
#
STR="\"''''''''''\"";
test_message "Parsing a string lots of string open characters";
has_str "\"''''''''''\"" $STR;
assert_command $?;



#
# Tests a string with special characters
#
STR="\"!@#$%ˆ&*()-=_+\"";
test_message "Parsing a string special characters";
has_str "\"!@#$%ˆ&*()-=_+\"" $STR;
assert_command $?;



#
# Tests a string with escaped back slash
#
STR="\"\\////\"";
test_message "Parsing a string with escaped back slash";
has_str "\"\\////\"" $STR;
assert_command $?;



# Prints tests result
result_message;
