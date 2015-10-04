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

#include "parsing.h"
#include "colors.h"
#include "tokens.h"



/*
 * Prints the json until the error and exits
 */
void print_json_error (char json[])
{
    fprintf(stdout, json);
    exit(EXIT_FAILURE);
}



/*
 * Print token
 */
void
add_token (struct token *token, char json[])
{
    /* Always there is 2 colors in the string: token->color and NO_COLOR */ 
    int colors_size = 2 * COLOR_STR_SIZE;

    int size = strlen(token->value) + colors_size;
    char value[size];

    /* Formats the new value */
    snprintf(value, size, "%s%s%s", token->color, token->value, NO_COLOR);
    strncat(json, value, strlen(value));

    if(token->type == TOKEN_ERROR)
    {
        print_json_error(json);
    }
}

/*
 * Object parser
 */
void
parse_object (struct token *token, FILE *file, char json[])
{ 

    add_token(token, json);
    char character = getc(file);

    if (character == STRING_0 || character == STRING_1) {

        parse_string(token, character, file);
        add_token(token, json);
        parse_object_separator(token, file);
        add_token(token, json);

        fprintf(stdout, json);
        fprintf(stdout, "\nAQUI\n");
    } else {

        // TODO: Refactory this lines into a function that makes sense
        char curr[2] = {character, '\0'};
        char str[10];
        fgets(str, 10, file);
        strncat(curr, str, strlen(str));

        char value[DEFAULT_VALUE_LENGTH];
        
        snprintf(value, DEFAULT_VALUE_LENGTH,
                "\n\t%s%s\n%s%s%s%s%s%c%s%s%s%c%s%s%s%c\n",
                 GREEN, curr, RED, "Malformed object: ", BROWN, "Expected ",
                 GRAY, STRING_0, BROWN," or ", GRAY, STRING_1, BROWN, 
                 " but found ", GRAY, character);
        update_token(token, TOKEN_ERROR, RED, value, 1, 4);
        add_token(token, json);
    }
}



/*
 * Array parser 
 */
void
array ()
{

}



/*
 * String parser
 */
void
parse_string (struct token *token, char already_read, FILE *file)
{
    char value[DEFAULT_VALUE_LENGTH] = {'\t', already_read, '\0'};
    char character = getc(file);

    do {
        sprintf(value, "%s%c", value, character);

        if(character == EOF) {
            fprintf(stdout, "Malformed string");
            exit(EXIT_FAILURE);
        }

        character = getc(file);

    } while (character != STRING_0 && character != STRING_1);

    // strncat(value, &character, 1); 
    sprintf(value, "%s%c", value, character);

    update_token(token, STRING_TOKEN, BLUE, value, 1, 4);
}



/*
 * Constant values parser
 */
void
constant ()
{

}



/*
 * Number parser
 */
void
number ()
{
    
}

/*
 * Separators parser
 */
void
parse_object_separator (struct token *token, FILE *file)
{
    char character = getc(file);

    if(character != PAIR_SEPARATOR) {
        fprintf(stdout, "Expected object separator");
        exit(EXIT_FAILURE);
    } else {
        char value[2] = {character, '\0'};
        update_token(token, PAIR_SEPARATOR, BROWN, value, 0, 1);
    }
}
