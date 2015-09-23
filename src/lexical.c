/*
 * ============================================================================
 *
 *       Filename:  lexical.c
 *
 *    Description:  This file is responsible of identify tokens of the json
 *                  object model
 *
 *        Version:  1.0
 *        Created:  09/15/2015 07:52:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza, 
 *   Organization:  Software Community
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "colors.h"
#include "lexical.h"



/* 
 * Tries to open the input json file. Exits with failure in case of any error
 */
void
open_json_file (FILE* file, char filename[])
{
    if (strcmp(filename, "-") == 0) {
        file = stdin;
        
    } else {
        file = fopen(filename, "r");
    }
    
    if (!file) {
        fprintf(stderr, RED "Error on openning file '%s'\n" NO_COLOR,
                filename);
        exit(EXIT_FAILURE);
    }
}



/*
 * Search for tokens on the opened json file
 */
void
find_token (FILE* file, struct token* token, char json[])
{
    char character;

    do {

        character = getc(file);
        fprintf(stdout, "character: %c", character);

    } while (character != EOF);
}



/*
 * Starts the parsing by doing the lexical analysis
 */
void
start_parsing (options_t* options)
{

    /*
     *  The well formatted json
     */
    char json[] = "";


    FILE* file = NULL;
    open_json_file(file, options->file_name);

    struct token* token = NULL;
    find_token(file, token, json);
}
