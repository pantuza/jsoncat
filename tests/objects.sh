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
start_message "Parsing objects";



#
# Tests an empty object
#
OBJ="{ }";
test_message "Parsing an empty object";
has_value "{}" $OBJ;
assert_command $?;



#
# Tests an object with a string
#
OBJ="'string'";
test_message "Parsing an object with a string";
has_value "{'test': 'string'}" $OBJ;
assert_command $?;



#
# Tests an object with a Number
#
OBJ="42";
test_message "Parsing an object with a Number";
has_value "{'test': 42}" $OBJ;
assert_command $?;



#
# Tests an object with the 'true' constant
#
OBJ="true";
test_message "Parsing an object with the 'true' constant";
has_value "{'test': true}" $OBJ;
assert_command $?;



#
# Tests an object with the 'false' constant
#
OBJ="false";
test_message "Parsing an object with the 'false' constant";
has_value "{'test': false}" $OBJ;
assert_command $?;



#
# Tests an object with the 'null' constant
#
OBJ="null";
test_message "Parsing an object with the 'null' constant";
has_value "{'test': null}" $OBJ;
assert_command $?;



#
# Tests an object with an array
#
OBJ="[ 42, 'test', true]";
test_message "Parsing an object with an array";
has_value "{'test': [42,'test',true]}" $OBJ;
assert_command $?;



#
# Tests an object with an inner object
#
OBJ="'my_object_key'";
test_message "Parsing an object with an inner object";
has_value "{'my_object_key': 42}" $OBJ;
assert_command $?;



#
# Tests an object with an inner object with two elements
#
OBJ="'second_key'";
test_message "Parsing an object with an inner object with two elements";
has_value "{'first_key': 42, 'second_key': true}" $OBJ;
assert_command $?;



# Prints tests result
result_message;
