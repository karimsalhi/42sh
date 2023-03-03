#include "parser.h"

struct ast_node *while_rule(struct lexer *lexer)
{
    struct ast_node *while_child = NULL;
    size_t id;

    if (!lexer || !peek_check(lexer, TOKEN_WHILE))
        return NULL;

    id = lexer->index++;

    struct ast_node *while_node = create_node(NODE_WHILE);

    if (!(while_child = compound_list(lexer)))
    {
        free_ast(while_node);
        lexer->index = id;
        return NULL;
    }

    struct ast_node *do_node = do_group(lexer);

    if (!do_node)
    {
        free_ast(while_node);
        free_ast(while_child);
        lexer->index = id;
        return NULL;
    }
    else
    {
        add_child(while_node, while_child, NULL);
        add_child(while_node, do_node, NULL);
    }
    return while_node;
}
