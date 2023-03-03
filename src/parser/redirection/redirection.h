#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "../../lexer/lexer.h"
#include "../parser.h"

// utils function in redirection
char *follow_word(struct lexer *lexer);
char *get_io_redirection(struct lexer *lexer, enum token_type type);
struct ast_node *create_redirect_node(char *io, char *follow,
                                      enum node_type type);

struct ast_node *redirection(struct lexer *lexer);
struct ast_node *redirect_output(struct lexer *lexer);
struct ast_node *redirect_input(struct lexer *lexer);
struct ast_node *redirect_append_output(struct lexer *lexer);
struct ast_node *redirect_dup_input(struct lexer *lexer);
struct ast_node *redirect_dup_output(struct lexer *lexer);
struct ast_node *redirect_read_write(struct lexer *lexer);

#endif // REDIRECTION_H
