/*
 * ============================================================================
 *
 *       Filename:  messages.c
 *
 *    Description:  Jsoncat messages
 *
 *        Version:  1.0
 *        Created:  09/16/2015 12:28:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Software Community
 *
 * ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>


#include "colors.h"
#include "messages.h"



/*
 * Jsoncat help message
 *
 */
void
help ()
{
    fprintf(stdout, BLUE "J S O N C A T \n\n" NO_COLOR);
    usage();
    description();
    options();
    author();
    version();
}



/*
 * Jsoncat usage message
 *
 */
void
usage ()
{
    fprintf(stdout, BROWN "Usage: " NO_COLOR);
    fprintf(stdout, "%s [options] input file\n\n", __JSONCAT_PROGRAM_NAME__);
}



/*
 * Jsoncat description message
 */
void
description ()
{
    fprintf(stdout, BROWN "Description: " NO_COLOR);
    fprintf(stdout, "Json pretty-print parser based on a recursive "
            "lexical analyser.\n\tThe input file is parsed to build a json "
            "object. If the object \n\tis correct, it will be "
            "pretty-printed to standard output\n\n");
}



/*
 * Jsoncat options message
 */
void
options ()
{
    fprintf(stdout, BROWN "Options:\n\n" NO_COLOR);
    fprintf(stdout, GRAY "\t-v|--version\n" NO_COLOR
                    "\t\tPrints %s version\n\n", __JSONCAT_PROGRAM_NAME__);
    fprintf(stdout, GRAY "\t-h|--help\n" NO_COLOR
                    "\t\tPrints this help message\n\n");
    fprintf(stdout, GRAY "\t--no-color\n" NO_COLOR
                    "\t\tDoes not prints json files using colors\n\n");
    fprintf(stdout, GRAY "\t-t|--tab-stop\n" NO_COLOR
                    "\t\tTabs are expanded as spaces. Default is 4\n\n");

}



/*
 * Jsoncat author message
 *
 */
void
author ()
{
    fprintf(stdout, BROWN "Written by: " GRAY "%s\n\n" NO_COLOR,
            __JSONCAT_AUTHOR__);
}



/*
 * Jsoncat version message
 *
 */
void
version ()
{
    fprintf(stdout, "jsoncat version " GRAY "%s\n" NO_COLOR,
            __JSONCAT_VERSION__);
}
