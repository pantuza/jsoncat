/*
 * ============================================================================
 *
 *       Filename:  tokens.c
 *
 *    Description:  Functions that controls the token
 *
 *        Version:  1.0
 *        Created:  09/27/2015 02:23:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Software Community
 *
 * ============================================================================
 */


#include "tokens.h"
#include "colors.h"



/*
 * Update current token
 */
void
update_token (struct token *token, int type, char color[COLOR_STR_SIZE],
              char value[DEFAULT_VALUE_LENGTH], int inc_line, int inc_column)
{

    token->type = type;

    token->line += (inc_line) ? inc_line : 0;

    token->column += (inc_column) ? inc_column : 0;

    strncpy(token->color, RED, COLOR_STR_SIZE);

    strncpy(token->value, value, DEFAULT_VALUE_LENGTH);
}
