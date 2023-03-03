#include "redirection.h"

struct ast_node *redirection(struct lexer *lexer)
{
    struct ast_node *node = NULL;

    if ((node = redirect_output(lexer)))
        return node;

    if ((node = redirect_input(lexer)))
        return node;

    if ((node = redirect_append_output(lexer)))
        return node;

    if ((node = redirect_dup_input(lexer)))
        return node;

    if ((node = redirect_dup_output(lexer)))
    {
        return node;
    }

    if ((node = redirect_read_write(lexer)))
        return node;

    return node;
}
