/*
 * ============================================================================
 *
 *       Filename:  jsoncat.c
 *
 *    Description:  This file is the main execution of the jsoncat program
 *
 *        Version:  1.0
 *        Created:  09/15/2015 12:46:34 AM
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


#include "args.h"
#include "colors.h"
#include "lexical.h"



int
main (int argc, char* argv[])
{
    /* Read command line options */
    options_t options;
    jsoncat_options_parser(argc, argv, &options);

#ifdef DEBUG
    fprintf(stdout, BLUE "Command line options:\n" NO_COLOR);
    fprintf(stdout, BROWN "help: %d\n" NO_COLOR, options.help);
    fprintf(stdout, BROWN "version: %d\n" NO_COLOR, options.version);
    fprintf(stdout, BROWN "use colors: %d\n" NO_COLOR, options.use_colors);
    fprintf(stdout, BROWN "tab stop: %d\n" NO_COLOR, options.tab_stop);
    fprintf(stdout, BROWN "filename: %s\n" NO_COLOR, options.file_name);
#endif

    start_parsing(&options);

    /* Forces a line break at and of the json print */
    fprintf(stdout, "\n");

    return EXIT_SUCCESS;
}
