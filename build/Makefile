#
#
# This is the Makefile to rule the distros build process
#
#

SHELL := bash

OBS_DIR := home\:pantuza

PROJECT_NAME := jsoncat

OSC := $(shell which osc)

TGZ_FILE_NAME := jsoncat-0.1.0.tar.gz

all: opensuse rpm deb dmg


tarfile:
	@tar -czvf $(TGZ_FILE_NAME) ../../$(PROJECT_NAME) \
		--exclude="*build*" --exclude="*.git*"
	@mv -v $(TGZ_FILE_NAME) $(OBS_DIR)/$(PROJECT_NAME)
	

opensuse: $(OBS_DIR)/$(PROJECT_NAME)/$(TGZ_FILE_NAME)
	@echo "Opensuse Build Service"
	@$(OSC) update $(OBS_DIR)/$(PROJECT_NAME)
	@make -C .. clean
	@cd $(OBS_DIR)/$(PROJECT_NAME) && $(OSC) build


rpm:
	@echo "Building rpm package"

deb:
	@echo "Building deb package"

dmg:
	@echo "Building dmg package"
