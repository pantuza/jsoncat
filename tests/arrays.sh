#!/bin/bash

#
# This bash script parses jsons with different types of arrays
#


# Include tests utils
. tests/utils.sh


# -------------------- T E S T S ------------------------ #


# Check binary
binary_exists;


# Prints start message
start_message "Parsing arrays";


#
# Tests an empty array
#
CONST="[ ]";
test_message "Parsing an empty array";
has_value "[]" $CONST;
assert_command $?;



#
# Tests an array with one element
#
CONST="[ 42]";
test_message "Parsing an array with one element";
has_value "[42]" $CONST;
assert_command $?;



#
# Tests an array with many elements
#
CONST="[ 42, 10, 30]";
test_message "Parsing an array with n elements";
has_value "[42, 10, 30]" $CONST;
assert_command $?;



#
# Tests an array of strings
#
CONST="[ 'x', 'y', 'z']";
test_message "Parsing an array of strings";
has_value "['x', 'y', 'z']" $CONST;
assert_command $?;



#
# Tests an array with escaped string
#
CONST="[ '\bbla', 'a', 'b']";
test_message "Parsing an array with escaped string";
has_value "['\bbla', 'a', 'b']" $CONST;
assert_command $?;



#
# Tests an array with constants
#
CONST="[ true, false, null]";
test_message "Parsing an array with constants";
has_value "[true, false, null]" $CONST;
assert_command $?;



#
# Tests an array with another array
#
CONST="[ [ 1, 2, 3]]";
test_message "Parsing an array with another array";
has_value "[[1,2,3]]" $CONST;
assert_command $?;



#
# Tests an array with an object inside
#
CONST="{";
test_message "Parsing an array with an object";
has_value "[{'test': true}]" $CONST;
assert_command $?;



#
# Tests an array with many different types of values
#
CONST="[ 1.0, 'string', true, false, null]";
test_message "Parsing an array with different types of values";
has_value "[1.0, 'string', true, false, null, {}]" $CONST;
assert_command $?;



# Prints tests result
result_message;
