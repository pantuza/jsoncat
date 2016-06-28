#
#
# J S O N C A T
#
#

# Include generic Makefile variables
include Makefile.conf


# Source code directory structure
BINDIR := bin
SRCDIR := src
LOGDIR := log
LIBDIR := lib
TESTSDIR := tests
SO_PATH := /usr/bin
BIN_SO_PATH := /bin
BUILD_DIR := build


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
DEBUG := #-g3 -D DEBUG=1


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
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS)
	@echo $(ECHO_OPTS) "\n--\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo $(ECHO_OPTS) "$(BROWN)CC $(END_COLOR)";
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS)


# installs the binary file at operating system path
install: $(BINDIR)/$(BINARY) $(DOCS)/$(MANPAGE)
	@echo $(ECHO_OPTS) "Installing binary file at" \
			  "$(BROWN)$(SO_PATH)/$(BINARY)$(END_COLOR)\n";
	@install $^ $(SO_PATH)/
	@echo $(ECHO_OPTS) "Creating a symbolic link of the binary file on" \
			  "$(BROWN)$(BIN_SO_PATH)/$(BINARY)$(END_COLOR)\n";
	@ln -sf $(SO_PATH)/$(BINARY) $(BIN_SO_PATH)/$(BINARY)
	@echo $(ECHO_OPTS) "Installing manpages at" \
		  "$(BROWN)$(MANPAGE_OS_DIR)/$(MANPAGE)$(END_COLOR)\n";
	@install $(DOCS)/$(MANPAGE) $(MANPAGE_OS_DIR)/$(MANPAGE)
	@echo $(ECHO_OPTS) "--\n\n$(BROWN)Installation complete$(END_COLOR)\n"


# Uninstall the jsoncat binary
uninstall: $(SO_PATH)/$(BINARY)
	@echo $(ECHO_OPTS) "$(BLUE)Uninstalling Jsoncat..$(END_COLOR)\n";
	@rm -vf $(BIN_SO_PATH)/$(BINARY)
	@rm -vf $^
	@rm -vf $(MANPAGE_OS_DIR)/$(MANPAGE)


# Build project as distribution packages
build: $(BUILD_DIR)/Makefile
	@make -C $^ all


# Rule for run valgrind tool
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/$(BINARY) $(TESTSDIR)/samples/input_08.json
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
