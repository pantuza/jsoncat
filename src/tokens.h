/*
 * ============================================================================
 *
 *       Filename:  tokens.h
 *
 *    Description:  Json object model token representation
 *
 *        Version:  1.0
 *        Created:  09/17/2015 08:46:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Software Community
 *
 * ============================================================================
 */

#ifndef TOKENS_H
#define TOKENS_H


#include "args.h"


/*
 * Tokens are based on the JSON object model definition: http://json.org
 */
#define OBJECT_OPEN     '{'
#define OBJECT_CLOSE    '}'

#define ARRAY_OPEN      '['
#define ARRAY_CLOSE     ']'

#define VALUE_SEPARATOR ','
#define PAIR_SEPARATOR  ':'

#define STRING_TOKEN    900
#define STRING_0        '\''
#define STRING_1        '"'
#define STRING_SCAPE    '\\'

#define TRUE_VALUE      901
#define FALSE_VALUE     902
#define NULL_VALUE      903

#define NUMBER          904

#define TOKEN_ERROR     905


/* Considered size of any color string defined in colors.h */
#define COLOR_STR_SIZE 6


/* Token value default size */
#define DEFAULT_VALUE_LENGTH 512


/* Switch tabs with spaces */
#define EXPANDTAB   ""

/* expanded tabs string size */
#define EXPANDTAB_SIZE  256

/* Default tabstop */
#define TABSTOP     4

/*
 * Types used by the lexical analiser
 */
struct token
{
    /* The token type (one of the defines in tokens.h) */
    int type;
    /* Line number */
    int line;
    /* Column number */
    int column;
    /* Color string */
    char color[COLOR_STR_SIZE];
    /* The value read that identifies the token */
    char value[DEFAULT_VALUE_LENGTH];
};



/* Public function to handle token struct */

void inc_line(struct token *token, int inc_size);
void inc_column (struct token *token, int inc_size);
void set_color (struct token *token, char color[COLOR_STR_SIZE]);
void set_value (struct token *token, char value[DEFAULT_VALUE_LENGTH]);


void update_token (struct token *token, int type, char color[COLOR_STR_SIZE],
              char value[DEFAULT_VALUE_LENGTH], int inc_line, int inc_column);
void add_token (struct token *token, options_t *options);
void expandtab (char tab_str[EXPANDTAB_SIZE], int n_tabs);


#endif // TOKENS_H
