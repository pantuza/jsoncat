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
#include <ctype.h>
#include <errno.h>

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
        fprintf(stderr, RED "Error on openning file '%s': %s\n" NO_COLOR,
                filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return file;
}



/*
 * Check if we found a number
 */
void
check_number(char *character)
{
    if(isdigit(*character)) {
        *character = (char) NUMBER;
    }
}



/*
 * Function to identify if the token represents any valid Json symbol.
 * If it matches a symbol, the symbol parser is called. Otherwise
 * the program exits with errors
 */
void
match_symbol(char character, struct token *token, FILE *file,
             char json[], int *n_tabs)
{
    char char_cpy = character;
    check_number(&character);

    switch (character) {

        case OBJECT_OPEN:
        {
            char value[DEFAULT_VALUE_LENGTH];
            *n_tabs += 1;
            parse_object(token, value, *n_tabs);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case PAIR_SEPARATOR:
        {
            parse_pair_separator(token);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case OBJECT_CLOSE:
        {
            char value[] = "\n"; 
            int i = 0;
            *n_tabs -= 1;
            if(*n_tabs > 0) {
                for(; i < *n_tabs; i++) {
                    strncat(value, "\t", sizeof(char));
                }
            }
            char to_append[2] = {OBJECT_CLOSE, '\0'};
            strncat(value, to_append, strlen(to_append));

            update_token(token, OBJECT_CLOSE, GRAY, value, 1, 0);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case ARRAY_OPEN:
        {
            parse_array(token);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case VALUE_SEPARATOR:
        {
            char value[DEFAULT_VALUE_LENGTH];
            parse_value_separator(token, value, *n_tabs);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case ARRAY_CLOSE:
        {
            char value[3] = {ARRAY_CLOSE, '\n', '\0'};
            update_token(token, ARRAY_CLOSE, GRAY, value, 1, 0);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case STRING_0:
        case STRING_1:
        { 
            char value[DEFAULT_VALUE_LENGTH];
            parse_string(token, character, value, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case '-':
        case ((char) NUMBER):
        {
            char value[DEFAULT_VALUE_LENGTH];
            parse_number(token, char_cpy, value, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }

        case 't':
        {
            parse_true_token(token, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }
        
        case 'f':
        {
            parse_false_token(token, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
            break;
        }
        
        case 'n':
        {
            parse_null_token(token, file);
            add_token(token, json);

            char next_char = getc(file);
            match_symbol(next_char, token, file, json, n_tabs);
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
    int n_tabs = 0;
    char character;

    do {
        /* Gets the character */
        character = getc(file);

        /* matches the token with an Json symbol */
        match_symbol(character, token, file, json, &n_tabs);

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
