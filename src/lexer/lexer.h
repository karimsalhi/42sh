#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_type.h"
#include "xmalloc.h"

struct lexer
{
    char **input;
    size_t index;
    size_t size;
};

struct token
{
    enum token_type type;
    char *value;
};

struct option
{
    int c_option;
    char *c_arg;

    int verbose_option;
    int ast_option;
};

/**
 * \brief examine the input and determine the option
 *
 * \param opt option to set
 * \param argc
 * \param argv
 */
FILE *input_type(struct option *opt, int argc, char **argv);

struct lexer *_lexer(struct option *opt, int argc, char **argv);
/**
 * \brief Create a lexer from the input
 *
 * \param file input file
 */
struct lexer *create_lexer(FILE *file);
/**
 * \brief Split string to word
 *
 * \param str string to split
 */
char **create_tab(char *str);
/**
 * \brief Create a token via teh value
 *
 * \param value value to give to token
 */
struct token *create_token(char *value);

/**
 * \brief Get the type of value
 *
 * \param value value
 */
enum token_type get_type(char *value);

/**
 * \brief Get the type of redirection
 *
 * \param value value
 */
enum token_type get_redirection(char *value);
/**
 * \brief Peek a token from lexer
 *
 * \param lexer lexer
 */
struct token *peek(struct lexer *lexer);

/**
 * \brief Pop a token from lexer
 *
 * \param lexer lexer
 */
struct token *pop(struct lexer *lexer);

/**
 * \brief Pop a token command from lexer
 *
 * \param lexer lexer
 */
struct token *pop_command(struct lexer *lexer);

/**
 * \brief free the lexer
 *
 * \param lexer lexer
 */
void free_lexer(struct lexer *lexer);
/**
 * \brief free a token
 *
 * \param token token
 */
void free_token(struct token *token);

/**
 * \brief Peek then check a token from lexer
 *
 * \param lexer lexer
 * \param type type to be checked
 */
int peek_check(struct lexer *lexer, enum token_type type);
/**
 * \brief Pop then check a token from lexer
 *
 * \param lexer lexer
 * \param type type to be checked
 */
int pop_check(struct lexer *lexer, enum token_type type);
#endif // LEXER_H
