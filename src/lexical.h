/*
 * ============================================================================
 *
 *       Filename:  lexical.h
 *
 *    Description:  Header file of the lexical analyser program
 *
 *        Version:  1.0
 *        Created:  09/15/2015 07:54:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza, 
 *   Organization:  Software Community
 *
 * ============================================================================
 */

#ifndef LEXICAL_H
#define LEXICAL_H


#include "args.h"


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
    /* The value read that identifies the token */
    char value[];
};



/* Public functions of the lexical analyser */
void start_parsing (options_t* options);


#endif // LEXICAL_H
