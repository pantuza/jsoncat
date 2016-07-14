#
#
# This is the Makefile to rule the distros build process
#
#


# Include generic Makefile variables
include ../Makefile.conf


# OpenSUSE Build Studio directory
OBS_DIR := home\:pantuza


# Get the Opensuse build studio client program
OSC := $(shell which osc)


# Packaged project file name
TGZ_FILE_NAME := $(PROJECT_NAME)-$(VERSION).tar.gz


# Author name
AUTHOR := "Gustavo Pantuza"


# Author email
AUTHOR_EMAIL := gustavopantuza@gmail.com


# Author site
AUTHOR_SITE := "https://pantuza.com"

# Scripts directory
SCRIPTS := scripts

# Script for build
BUILDER := ${SCRIPTS}/builder.sh


# Dpkg Buildpackage
DPKGBUILD := $(shell which dpkg-buildpackage)


#
# Target rules to build and package the project
#
all: opensuse rpm deb


# Creates a tar.gz file with all source files
tarfile:
	@make -C .. clean;
	@tar -czvf $(TGZ_FILE_NAME) ../../$(PROJECT_NAME) \
		--exclude="*build*" --exclude="*.git*";
	@echo $(ECHO_OPTS) "Removing older tar files:\n";
	@rm -rvf $(OBS_DIR)/$(PROJECT_NAME)/*.tar.gz;
	@mv -v $(TGZ_FILE_NAME) $(OBS_DIR)/$(PROJECT_NAME);
	@echo $(ECHO_OPTS) "\n--\nCreated project tarball at " \
		"$(BROWN)$(OBS_DIR)/$(PROJECT_NAME)/$(TGZ_FILE_NAME)$(END_COLOR)\n";
	
new_version:
	@. ${BUILDER} $@;

# Builds the project package for OpenSUSE
opensuse: $(OBS_DIR)/$(PROJECT_NAME)/$(TGZ_FILE_NAME)
	@echo $(ECHO_OPTS) "$(BROWN)OpenSUSE Build Service$(END_COLOR)\n";
	@$(OSC) update $(OBS_DIR)/$(PROJECT_NAME)
	@make -C .. clean
	@cd $(OBS_DIR)/$(PROJECT_NAME) && $(OSC) build


# Builds the project package for RPM based distros
rpm:
	@echo $(ECHO_OPTS) "$(BROWN)Building RPM package$(END_COLOR)\n";


# Build the project package for Debian distributions
deb:
	@echo $(ECHO_OPTS) "$(BROWN)Building Debian package$(END_COLOR)\n";
	$(DPKGBUILD) -us -uc -d

project:
	@make -C ..

# Creates the project manpage
manpage:
	@echo '.\" Manpage for $(PROJECT_NAME)' > $(MANPAGE)
	@echo '.\" Contact $(AUTHOR_EMAIL) to correct errors.' >> $(MANPAGE)
	@echo '.TH man 1 "$(shell date +%d\ %B\ %Y)" ' \
		  '"$(VERSION)" "$(PROJECT_NAME) man page"' >> $(MANPAGE)
	@echo '.SH NAME' >> $(MANPAGE)
	@echo '$(PROJECT_NAME) \- Json pretty-print parser based on a' \
		  'recursive lexical analyser ' >> $(MANPAGE)
	@echo '.SH SYNOPSIS' >> $(MANPAGE)
	@echo '$(PROJECT_NAME) [OPTION]... [FILE]...' >> $(MANPAGE)
	@echo '.SH DESCRIPTION' >> $(MANPAGE)
	@echo 'Json pretty-print parser based on a recursive lexical analyser. ' \
		  'The parser was based on the specification defined at json.org. ' \
		  'The input file is parsed to build a json object. ' \
		  'If the object is correct, it will be pretty-printed to ' \
		  'standard output.' >> $(MANPAGE)
	@echo '.SH OPTIONS' >> $(MANPAGE)
	@echo '.TP' >> $(MANPAGE)
	@echo '.B -h | --help' >> $(MANPAGE)
	@echo 'Prints $(PROJECT_NAME) help message' >> $(MANPAGE)
	@echo '.TP' >> $(MANPAGE)
	@echo '.B -v | --version' >> $(MANPAGE)
	@echo 'Prints $(PROJECT_NAME) version' >> $(MANPAGE) 
	@echo '.SH USAGE' >> $(MANPAGE)
	@echo $(ECHO_OPTS) '.PP\n.nf\n.RS\n' >> $(MANPAGE)
	@echo $(ECHO_OPTS) 'Jsoncat parses a json that comes from a pipe to' \
		  'stdin. For example, parsing a request:\n\n' >> $(MANPAGE)
	@echo '$$\> curl -s $(AUTHOR_SITE)/sample.json ' \
		  '--insecure | jsoncat' >> $(MANPAGE)
	@echo $(ECHO_OPTS) "\n{\n\t'what': \"A json example file\",\n\t'test': " \
		  "true,\n\t'values': [ 42, 10, 5.32],\n\t'data': {\n\t\t'name': " \
		  "'Test Name',\n\t\t'type': null\n\t}\n}" >> $(MANPAGE)
	@echo $(ECHO_OPTS) '\n\nOr simple by passing a path to a json file as ' \
		  'follows:\n\n' >> $(MANPAGE)
	@echo $(ECHO_OPTS) '$$\> $(PROJECT_NAME) ' \
		  'tests/samples/input_06.json' >> $(MANPAGE)
	@echo $(ECHO_OPTS) "\n\n{\n\t'age': 42,\n\t'name': 'marvin',\n\t'what':" \
		  "'robot'\n}\n\n" >> $(MANPAGE) 
	@echo 'Or yet, again from stdin, by echoing a json:' >> $(MANPAGE)
	@echo $(ECHO_OPTS) "\n$$\> echo \"{'test': true}\" | jsoncat" >> $(MANPAGE)
	@echo $(ECHO_OPTS) "\n\n{\n\t'test': true\n}\n" >> $(MANPAGE)
	@echo $(ECHO_OPTS) '\n.RE\n.fi\n.PP\n' >> $(MANPAGE)
	@echo '.SH BUGS' >> $(MANPAGE)
	@echo 'Report bugs to $(AUTHOR_EMAIL)' >> $(MANPAGE)
	@echo '.SH AUTHOR' >> $(MANPAGE)
	@echo '$(AUTHOR) ($(AUTHOR_SITE))' >> $(MANPAGE)
	@mv $(MANPAGE) ../$(DOCS)/$(MANPAGE)
	@echo $(ECHO_OPTS) "manpage created and placed at " \
		  "$(BROWN)$(DOCS)/$(MANPAGE)$(END_COLOR)\n"
