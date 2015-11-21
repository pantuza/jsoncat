/*
 * =====================================================================================
 *
 *       Filename:  args.h
 *
 *    Description:  Header file of the command line options parser
 *
 *        Version:  1.0
 *        Created:  09/15/2015 08:19:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Software Community
 *
 * =====================================================================================
 */


#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>
#include <getopt.h>


/* Max size of a file name */
#define FILE_NAME_SIZE 512

/* Defines the command line allowed options struct */
struct options
{
    bool help;
    bool version;
    bool use_colors;
    unsigned int tab_stop;
    char file_name[FILE_NAME_SIZE];
};


/* Exports jsoncat_options as a global type */
typedef struct options options_t;



/* Public functions section */
void jsoncat_options_parser(int argc, char* argv[], options_t* options);

#endif // ARGS_H
