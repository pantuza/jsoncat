/*
 * ============================================================================
 *
 *       Filename:  parsing.h
 *
 *    Description:  Header file of the syntactical analysis program
 *
 *        Version:  1.0
 *        Created:  09/15/2015 08:00:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza, 
 *   Organization:  Software Community
 *
 * ============================================================================
 */


#ifndef PARSING_H
#define PARSING_H


#include <stdlib.h>
#include <stdio.h>

#include "tokens.h"


void parse_object (struct token *token, FILE *file, char json[]);
void parse_string (struct token *token, char already_read, FILE *file);
void parse_object_separator(struct token *token, FILE *file);


#endif // PARSING_H
