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
 * Function that assigns the character as a token struct
 */
void
update_current_token (struct token *token, char token_type, char value[])
{
    token->type = token_type;
    strncpy(token->value, value, sizeof(value + 1));
}



/*
 * Function to identify if the token represents any valid Json symbol.
 * If it matches a symbol, the symbol parser is called. Otherwise
 * the program exits with errors
 */
void
match_symbol(struct token *token)
{

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

        /* Update the current token struct */
        update_current_token(token, character, "test");

        /* matches the token with an Json symbol */
        match_symbol(token);

    } while (character != EOF);
}



/*  
 * Function to start the first token
 */
void
start_token (struct token *token)
{
    /* The first token starts on line and column 1 */
    token->line = 1;
    token->column = 1;
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


    FILE *file = open_json_file(options->file_name);

    struct token* token;
    start_token(token);

    find_token(file, token, json);
}
