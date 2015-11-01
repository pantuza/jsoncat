#
#
# J S O N C A T 
#
#

# Shell program
SHELL := bash


# Gets from shell the operating system
OS := $(shell uname -s)

# String for the MAC OS X operationg system
MAC_OS_X_OSTYPE := Darwin

#
# Color prefix for Linux based distributions
#
COLOR_PREFIX := e

# echo command line options for Linux based distributions
ECHO_OPTS := -en


#
# If the operating system is MAC OS X, the colors prefix and echo options 
# must be different
#
ifeq ($(OS), $(MAC_OS_X_OSTYPE))
	COLOR_PREFIX := 033
endif


# Color definition for print purpose
BROWN=\$(COLOR_PREFIX)[0;33m
BLUE=\$(COLOR_PREFIX)[1;34m
END_COLOR=\$(COLOR_PREFIX)[0m


# Source code directory structure
BINDIR := bin
SRCDIR := src
LOGDIR := log
LIBDIR := lib
TESTSDIR := tests
SO_PATH := /usr/bin


# Source code file extension
SRCEXT := c


# Defines the C Compiler
CC := gcc


# Defines the language standards for GCC
STD := -std=gnu99 # See man gcc for more options

# Protection for stack-smashing attack
STACK := -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic # -pedantic warns on language standards 

# Flags for compiling
CFLAGS := -O3 $(STD) $(STACK) $(WARNS)

# Debug options 
DEBUG := -g3 # -DDEBUG=1

# Dependency libraries
LIBS := -lm


#
# The binary file name
#
BINARY := jsoncat


# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))



#
# COMPILATION RULES
#

# Rule for link and generate the binary file
all: $(OBJECTS)
	@echo $(ECHO_OPTS) "$(BROWN)LD $(END_COLOR)";
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS) $(LIBS) 
	@echo $(ECHO_OPTS) "\n--\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo $(ECHO_OPTS) "$(BROWN)CC $(END_COLOR)";
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS) $(LIBS) 

# installs the binary file at operating system path
install: $(BINDIR)/$(BINARY)
	@echo $(ECHO_OPTS) "Installing binary file at" \
			  "$(BROWN)$(SO_PATH)/$(BINARY)$(END_COLOR)\n";
	@sudo install $^ $(SO_PATH)/
	@echo $(ECHO_OPTS) "Creating a symbolic link of the binary file to " \
			  "$(BROWN)/bin/$(BINARY)$(END_COLOR)\n";
	@sudo ln -sf $(SO_PATH)/$(BINARY) /bin/$(BINARY)
	@echo $(ECHO_OPTS) "--\n$(BROWN)Installation complete$(END_COLOR)\n"

# Uninstall the jsoncat binary
uninstall: $(SO_PATH)/$(BINARY)
	@echo $(ECHO_OPTS) "$(BLUE)Uninstalling Jsoncat..$(END_COLOR)\n";
	@sudo rm -vf /bin/$(BINARY)
	@sudo rm -vf $^

# Rule for run valgrind tool
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/$(BINARY)
	@echo $(ECHO_OPTS) "\nCheck the log file: $(LOGDIR)/$@.log\n"


# Rule to run the resulted binary file
run: $(BINDIR)/$(BINARY)
	@./$^ $(TESTSDIR)/samples/input_06.json

# Rule for cleaning the project
clean:

	@rm -rvf $(BINDIR)/*;
	@rm -rvf $(LIBDIR)/*;
	@rm -rvf $(LOGDIR)/*;

# Rule to run the project tests
test: command_line_test strings_test constants_test arrays_test \
	  objects_test samples_test

# Rule to run the command line arguments tests
command_line_test: $(TESTSDIR)/command_args.sh
	@$(SHELL) $^

# Rule to run tests on different kind of strings
strings_test: $(TESTSDIR)/strings.sh
	@$(SHELL) $^

# Rule to run tests on constants as json value
constants_test: $(TESTSDIR)/constants.sh
	@$(SHELL) $^

# Rule to run tests on different types of arrays
arrays_test: $(TESTSDIR)/arrays.sh
	@$(SHELL) $^

# Rule to run tests on different types of objects
objects_test: $(TESTSDIR)/objects.sh
	@$(SHELL) $^

# Rule to run samples parsing test
samples_test: $(TESTSDIR)/samples.sh
	@$(SHELL) $^

