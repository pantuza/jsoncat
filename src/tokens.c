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
#include "string.h"



/*
 * Increment the token line
 */
void
inc_line(struct token *token, int inc_size)
{
    token->line += (inc_size) ? inc_size : 0;
}



/*
 * Increment the token column
 */
void
inc_column (struct token *token, int inc_size)
{
    token->column += (inc_size) ? inc_size : 0;
}



/*
 * Sets the token value color
 */
void
set_color (struct token *token, char color[COLOR_STR_SIZE])
{
    strncpy(token->color, color, COLOR_STR_SIZE);
}



/*
 * Sets the token value
 */
void
set_value (struct token *token, char value[DEFAULT_VALUE_LENGTH])
{
    strncpy(token->value, value, DEFAULT_VALUE_LENGTH);
}



/*
 * Update current token
 */
void
update_token (struct token *token, int type, char color[COLOR_STR_SIZE],
              char value[DEFAULT_VALUE_LENGTH], int inc_l, int inc_c)
{
    token->type = type;

    inc_line(token, inc_l);
    inc_column(token, inc_c);
    
    set_color(token, color);
    set_value(token, value);
}
