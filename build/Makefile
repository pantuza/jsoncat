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



#
# Target rules to build and package the project
#
all: opensuse rpm deb


# Creates a tar.gz file with all source files
tarfile:
	@tar -czvf $(TGZ_FILE_NAME) ../../$(PROJECT_NAME) \
		--exclude="*build*" --exclude="*.git*"
	@mv -v $(TGZ_FILE_NAME) $(OBS_DIR)/$(PROJECT_NAME)
	

# Builds the project package for OpenSUSE
opensuse: $(OBS_DIR)/$(PROJECT_NAME)/$(TGZ_FILE_NAME)
	@echo "Opensuse Build Service"
	@$(OSC) update $(OBS_DIR)/$(PROJECT_NAME)
	@make -C .. clean
	@cd $(OBS_DIR)/$(PROJECT_NAME) && $(OSC) build


# Builds the project package for RPM based distros
rpm:
	@echo "Building rpm package"


# Build the project package for Debian distributions
deb:
	@echo "Building deb package"
