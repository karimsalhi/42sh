#include "parser.h"

struct ast_node *input(struct lexer *lexer)
{
    struct ast_node *node = create_node(NODE_INPUT);

    if (peek_check(lexer, TOKEN_NEWLINE) || peek_check(lexer, TOKEN_EOF))
    {
        free(pop(lexer));
        return node;
    }

    struct ast_node *tmp = NULL;

    if ((tmp = list(lexer)) == NULL)
    {
        free_ast(node);
        return NULL;
    }

    add_child(node, tmp, NULL);

    if (peek_check(lexer, TOKEN_NEWLINE) || peek_check(lexer, TOKEN_EOF))
    {
        free(pop(lexer));
        return node;
    }

    free_ast(node);
    return NULL;
}
