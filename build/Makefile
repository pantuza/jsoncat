#
#
# This is the Makefile to rule the distros build process
#
#

PROJECT_NAME := jsoncat

OSC := $(shell which osc)

TGZ_FILE_NAME := jsoncat-0.1.0.tar.gz 

all: opensuse rpm deb dmg


opensuse: 
	@echo "Opensuse Build Service"
	@$(OSC) update home:pantuza/$(PROJECT_NAME)
	@make -C .. clean
	@tar -czvf $(TGZ_FILE_NAME) ../../$(PROJECT_NAME) \
		--exclude="*build*" --exclude="*.git*"
	@mv -v $(TGZ_FILE_NAME) home:pantuza/$(PROJECT_NAME)
	cd home:pantuza/$(PROJECT_NAME) && $(OSC) build

rpm:
	@echo "Building rpm package"

deb:
	@echo "Building deb package"

dmg:
	@echo "Building dmg package"
