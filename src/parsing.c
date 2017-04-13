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
parse_object(struct token *token, int *n_tabs, unsigned int tabstop)
{
    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    *n_tabs += 1;

    value[0] = OBJECT_OPEN;
    value[1] = '\n';
    value[2] = '\0';


    if(*n_tabs > 0) {
        char tab_str[EXPANDTAB_SIZE];
        expandtab(tab_str, *n_tabs, tabstop);
        strncat(value, tab_str, EXPANDTAB_SIZE);
    }

    update_token(token, OBJECT_OPEN, GRAY, value, 0, 1);
    free(value);
}



/*
 * Parse the object close token
 */
void
parse_object_close(struct token *token, int *n_tabs, unsigned int tabstop)
{

    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    *n_tabs -= 1;

    value[0] = '\n';
    value[1] = '\0';

    /* Fill value with tab characters for identation */
    if(*n_tabs > 0) {
        char tab_str[EXPANDTAB_SIZE];
        expandtab(tab_str, *n_tabs, tabstop);
        strncat(value, tab_str, EXPANDTAB_SIZE);
    }

    char to_append[2] = {OBJECT_CLOSE, '\0'};

    strncat(value, to_append, strlen(to_append));

    update_token(token, OBJECT_CLOSE, GRAY, value, 1, 0);
    free(value);
}



/*
 * Array parser open
 */
void
parse_array_open (struct token *token, int *n_tabs, unsigned int tabstop)
{

    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    memset(value, 0, DEFAULT_VALUE_LENGTH);

    if(token->type == ARRAY_OPEN){
        *n_tabs += 1;
        value[0] = '\n';
        char tab_str[EXPANDTAB_SIZE];
        expandtab(tab_str, *n_tabs, tabstop);
        strncat(value, tab_str, EXPANDTAB_SIZE);
    }
    int size = strlen(value);
    value[size] = ARRAY_OPEN;
    value[++size] = '\0';

    update_token(token, ARRAY_OPEN, GRAY, value, 0, 1);
    free(value);
}


/*
 * Parse array close
 */
void parse_array_close (struct token *token, int *n_tabs, unsigned int tabstop)
{

    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    memset(value, 0, DEFAULT_VALUE_LENGTH);

    if(token->type == ARRAY_CLOSE) {
        *n_tabs -= 1;
        value[0] = '\n';
        char tab_str[EXPANDTAB_SIZE];
        expandtab(tab_str, *n_tabs, tabstop);
        strncat(value, tab_str, EXPANDTAB_SIZE);
    }
    int size = strlen(value);
    value[size] = ARRAY_CLOSE;
    value[++size] = '\0';

    update_token(token, ARRAY_CLOSE, GRAY, value, 1, 0);
    free(value);
}


/*
 * Verifies if we are inside a string
 */
bool
is_string_end(char string_open_char, char curr_char, char prev_char)
{
    /* If we found the string end (' or ") and it is not escaped */
    if(curr_char == string_open_char && prev_char != '\\')
    {
        return true;
    }
    return false;
}



/*
 * String parser
 */
void
parse_string (struct token *token, char character, FILE *file)
{
    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));
    value[0] = character;
    value[1] = '\0';

    char prev_char = character;
    char curr_char = getc(file);

    int i = 1;
    while (!is_string_end(character, curr_char, prev_char))
    {
        if(strlen(value) == (unsigned int) i * DEFAULT_VALUE_LENGTH - 1) {
            char* tmp = realloc(value, (++i * DEFAULT_VALUE_LENGTH) * sizeof(char));
            value = tmp;
            tmp = NULL;
        }
        strncat(value, &curr_char, 1);

        if(curr_char == EOF) {
            fprintf(stdout, RED "Malformed string\n" NO_COLOR);
            exit(EXIT_FAILURE);
        }

        prev_char = curr_char;
        curr_char = getc(file);
    }
    strncat(value, &curr_char, 1);
    update_token(token, STRING_TOKEN, GREEN, value, 1, 4);
    free(value);
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
parse_number (struct token *token, char character, FILE *file)
{

    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    value[0] = character;
    value[1] = '\0';

    char next_char = getc(file);

    while(is_part_of_a_number(next_char)) {

        strncat(value, &next_char, sizeof(char));
        next_char = getc(file);
    }

    ungetc(next_char, file);
    update_token(token, NUMBER, RED, value, 0, 1);
    free(value);
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
parse_value_separator (struct token *token,
                       int n_tabs, bool inside_array, unsigned int tabstop)
{

    char* value = malloc(DEFAULT_VALUE_LENGTH * sizeof(char));

    value[0] = VALUE_SEPARATOR;
    value[1] = '\0';

    /* If the value do not separates elements of an array, we break the line */
    if(!inside_array){
        value[1] = '\n';
        value[2] = '\0';

        /* Insert tabs on value to format json */
        if(n_tabs > 0) {
            char tab_str[EXPANDTAB_SIZE];
            expandtab(tab_str, n_tabs, tabstop);
            strncat(value, tab_str, EXPANDTAB_SIZE);
        }
    } else {
        /* If inside an array, separate elements with a single space */
        value[1] = ' ';
        value[2] = '\0';
    }

    update_token(token, VALUE_SEPARATOR, BROWN, value, 1, 0);
    free(value);
}
