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


void parse_object (struct token *token,
                   char value[DEFAULT_VALUE_LENGTH], int n_tabs);
void parse_object_close(struct token *token, int *n_tabs);
void parse_array (struct token *token);
void parse_string (struct token *token, char character,
                   char value[DEFAULT_VALUE_LENGTH], FILE *file);
void parse_pair_separator (struct token *token);
void parse_value_separator (struct token *token,
                            char value[DEFAULT_VALUE_LENGTH], int n_tabs);
void parse_number (struct token *token, char character,
                   char value[DEFAULT_VALUE_LENGTH], FILE *file);
void parse_true_token (struct token *token, FILE *file);
void parse_false_token (struct token *token, FILE *file);
void parse_null_token (struct token *token, FILE *file);


#endif // PARSING_H
