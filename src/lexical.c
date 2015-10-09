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


#include "tokens.h"
#include "colors.h"
#include "lexical.h"
#include "parsing.h"
#include "colors.h"



/* 
 * Tries to open the input json file. Exits with failure in case of any error
 */
FILE*
open_json_file (char filename[])
{
    FILE *file;

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

    return file;
}



/*
 * Function to identify if the token represents any valid Json symbol.
 * If it matches a symbol, the symbol parser is called. Otherwise
 * the program exits with errors
 */
void
match_symbol(char character, struct token *token, FILE *file, char json[])
{
    switch (character) {

        case OBJECT_OPEN:
        { 
            char value[4] = {OBJECT_OPEN, '\n', '\t', '\0'};

            update_token(token, OBJECT_OPEN, GRAY, value, 0, 1);
            parse_object(token, file, json);
            break;
        }

        case ARRAY_OPEN:
        {
            char value[3] = {ARRAY_OPEN, '\n', '\0'};

            update_token(token, ARRAY_OPEN, GRAY, value, 0, 1);
            parse_array(token, file, json);
            break;
        }

        case STRING_0:
        case STRING_1:
        { 
            parse_string(token, character, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json);
            break;
        }
    }
}



/*
 * Search for tokens on the opened json file
 */
void
find_token (FILE *file, struct token *token, char json[])
{
    char character;

    do {
        /* Gets the character */
        character = getc(file);

        /* matches the token with an Json symbol */
        match_symbol(character, token, file, json);

    } while (character != EOF);
}



/*
 * Starts the parsing by doing the lexical analysis
 */
void
start_parsing (options_t* options, char json[])
{

    FILE *file = open_json_file(options->file_name);

    struct token token;
    token.line = 0;
    token.column = 0;

    find_token(file, &token, json);
}
