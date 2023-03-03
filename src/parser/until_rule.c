#include "parser.h"

struct ast_node *until_rule(struct lexer *lexer)
{
    struct ast_node *until_child = NULL;
    size_t id;

    if (!lexer || !peek_check(lexer, TOKEN_UNTIL))
        return NULL;

    id = lexer->index++;

    struct ast_node *until_node = create_node(NODE_UNTIL);

    if (!(until_child = compound_list(lexer)))
    {
        free_ast(until_node);
        lexer->index = id;
        return NULL;
    }

    struct ast_node *do_node = do_group(lexer);

    if (!do_node)
    {
        free_ast(until_node);
        free_ast(until_child);
        lexer->index = id;
        return NULL;
    }
    else
    {
        add_child(until_node, until_child, NULL);
        add_child(until_node, do_node, NULL);
    }
    return until_node;
}
