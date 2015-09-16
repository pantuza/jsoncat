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
}



/* 
 * Jsoncat usage message
 *
 */
void
usage ()
{
    fprintf(stdout, BROWN "Usage: " NO_COLOR);
    fprintf(stdout, "jsoncat [options] input file\n");
}



/* 
 * Jsoncat version message
 *
 */
void
version ()
{
    fprintf(stdout, "jsoncat version " BROWN __JSONCAT_VERSION__ NO_COLOR);
}
