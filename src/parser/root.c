#include "parser.h"

struct ast_node *root(struct lexer *lexer)
{
    struct ast_node *rtn = create_node(NODE_ROOT);

    while (!peek_check(lexer, TOKEN_EOF))
    {
        struct ast_node *child = input(lexer);
        if (!child)
        {
            free_ast(rtn);
            return NULL;
        }

        add_child(rtn, child, NULL);
    }

    return rtn;
}
