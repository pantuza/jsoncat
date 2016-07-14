#!/bin/bash


# Include default bash variables fro scripting
. ./scripts/utils.sh


#
# Gets current version
#
get_current_version ()
{
    VERSION=$(${CAT} ../src/messages.h |${GREP} "VERSION" |${CUT} -d ' ' -f3);
}


#
# Asks for new version
#
get_new_version ()
{
    read NEW_VERSION
}


#
# Updates the version at the source file
#
update_version_on_src_file ()
{
    RE="s/__JSONCAT_VERSION__ \".*\"/__JSONCAT_VERSION__ \"${NEW_VERSION}\"/g";
    ${SED} ${SEDOPTS} "${RE}" ${SRC_VERSION_FILE};
}



#
# Updates the version at the spec file
#
update_version_on_spec_file ()
{
    RE="s/Version:.*/Version:\t\t${NEW_VERSION}/g";
    ${SED} ${SEDOPTS} "${RE}" ${SPEC_FILE};
}



#
# Create a new git tag and pushes to remote
#
create_tag_from_new_version ()
{
    ${GIT} add ${SRC_VERSION_FILE};
    ${GIT} add ${SPEC_FILE};
    ${GIT} commit -m "New version ${NEW_VERSION}";
    ${GIT} tag ${NEW_VERSION};
    ${GIT} push origin ${NEW_VERSION};
}


#
# Generates a new version of Jsoncat
#
new_version ()
{
    get_current_version;
    ${ECHO} ${ECHO_OPTS} "Current version is: ${VERSION}";
    ${ECHO} ${ECHO_OPTS} "Enter the new version";
    get_new_version;
    update_version_on_src_file;
    update_version_on_spec_file;
    # TODO: create the update_version_on_debian_files
    create_tag_from_new_version;
}


#
# Main function to handle build process
#
main ()
{
    case "$1" in
        new_version)
            new_version
            ;;
        *)
            ${ECHO} ${ECHOOPTS} "No function to satisfy '$1'";
            exit 1;
    esac;
}


#
# Calls the main
#
main $@;
