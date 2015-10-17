/*
 * ============================================================================
 *
 *       Filename:  parsing.c
 *
 *    Description:  File responsible of the syntactic analysis of the json 
 *                  object
 *
 *        Version:  1.0
 *        Created:  09/15/2015 07:58:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza, 
 *   Organization:  Software Community
 *
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lexical.h"
#include "parsing.h"
#include "colors.h"
#include "tokens.h"


/*
 * Object parser
 */
void
parse_object(struct token *token, char value[DEFAULT_VALUE_LENGTH], int n_tabs)
{ 
    value[0] = OBJECT_OPEN;
    value[1] = '\n';
    value[2] = '\0';

    int i = 0;
    if(n_tabs > 0) {
        for(; i < n_tabs; i++) {
            strncat(value, "\t", sizeof(char));
        }
    }

    update_token(token, OBJECT_OPEN, GRAY, value, 0, 1);
}



/*
 * Array parser 
 */
void
parse_array (struct token *token)
{
    char value[3] = {ARRAY_OPEN, ' ', '\0'};
    update_token(token, ARRAY_OPEN, GRAY, value, 0, 1);
}



/*
 * String parser
 */
void
parse_string (struct token *token, char character,
              char value[DEFAULT_VALUE_LENGTH], FILE *file)
{
    value[0] = character;
    value[1] = '\0';

    char next_char = getc(file);

    while (next_char != character)
    {
        strncat(value, &next_char, 1); 

        if(next_char == EOF) {
            fprintf(stdout, RED "Malformed string\n" NO_COLOR);
            exit(EXIT_FAILURE);
        }

        next_char = getc(file);
    }
    strncat(value, &next_char, 1); 

    update_token(token, STRING_TOKEN, NO_COLOR, value, 1, 4);
}



/*
 * true constant value parser
 */
void
parse_true_token (struct token *token, FILE *file)
{
    unsigned int true_str_size = 4;
    char value[] = "true";

    unsigned int i;
    char next_char;
    for(i = 1; i < true_str_size; i++) {

        next_char = getc(file);
        if(!(next_char == value[i])) {
            fprintf(stderr, RED "Error on parsing the 'true' token value\n"
                    NO_COLOR);
            exit(EXIT_FAILURE);
        }
    }

    update_token(token, TRUE_VALUE, RED, value, 0, 4);
}



/*
 * false constant value parser
 */
void
parse_false_token (struct token *token, FILE *file)
{
    unsigned int false_str_size = 5;
    char value[] = "false";

    unsigned int i;
    char next_char;
    for(i = 1; i < false_str_size; i++) {

        next_char = getc(file);
        if(!(next_char == value[i])) {
            fprintf(stderr, RED "Error on parsing the 'false' token value\n" 
                    NO_COLOR);
            exit(EXIT_FAILURE);
        }
    }

    update_token(token, FALSE_VALUE, RED, value, 0, 4);
}



/*
 * null constant value parser
 */
void
parse_null_token (struct token *token, FILE *file)
{
    unsigned int null_str_size = 4;
    char value[] = "null";

    unsigned int i;
    char next_char;
    for(i = 1; i < null_str_size; i++) {

        next_char = getc(file);
        if(!(next_char == value[i])) {
            fprintf(stderr, RED "Error on parsing the 'null' token value\n"
                    NO_COLOR);
            exit(EXIT_FAILURE);
        }
    }

    update_token(token, NULL_VALUE, RED, value, 0, 4);
}



/*
 * Get valid number value
 */
bool
is_part_of_a_number(char character) 
{
    switch (character) {

        case '.':
        case 'e':
        case 'E':
        case '+':
        case '-':
            return true;

        default:
            if(isdigit(character)) {
                return true;
            } else {
                return false;
            }
    }
}



/*
 * Number parser
 */
void
parse_number (struct token *token, char character,
              char value[DEFAULT_VALUE_LENGTH], FILE *file)
{
    value[0] = character;
    value[1] = '\0';

    char next_char = getc(file);

    while(is_part_of_a_number(next_char)) {

        strncat(value, &next_char, sizeof(char));
        next_char = getc(file);
    }

    ungetc(next_char, file);
    update_token(token, NUMBER, RED, value, 0, 1);
}



/*
 * Separators parser
 */
void
parse_pair_separator (struct token *token)
{
    char value[3] = {PAIR_SEPARATOR, ' ', '\0'};
    update_token(token, PAIR_SEPARATOR, BROWN, value, 0, 1);
}



/*
 * Value separator parser
 */
void
parse_value_separator (struct token *token, char value[DEFAULT_VALUE_LENGTH],
                       int n_tabs)
{
    value[0] = VALUE_SEPARATOR;
    value[1] = '\n';
    value[2] = '\0';

    int i = 0;
    if(n_tabs > 0) {
        for(; i < n_tabs; i++) {
            strncat(value, "\t", sizeof(char));
        }
    }

    update_token(token, VALUE_SEPARATOR, BROWN, value, 1, 0);
}
