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


#include <stdio.h>

#include "tokens.h"
#include "args.h"



/* Public functions of the lexical analyser */
void start_parsing (options_t* options);
void match_symbol(char character, struct token *token,
                  FILE *file, int *n_tabs);


#endif // LEXICAL_H
