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



/*
 * Print token
 */
void
print_token (struct token *token, char json[])
{
    int size = strlen(token->value) + 12;
    char tmp[size];

    snprintf(tmp, size, "%s%s%s\n", RED, token->value, NO_COLOR);
    strncpy(json, tmp, strlen(tmp));
    fprintf(stdout, json);
}

/*
 * Object parser
 */
void
parse_object (struct token *token, FILE *file, char json[])
{ 

    print_token(token, json);
    char character = getc(file);


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
string ()
{

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
