#include "parser.h"

struct ast_node *do_group(struct lexer *lexer)
{
    struct ast_node *do_child = NULL;
    size_t id;

    if (!lexer || !peek_check(lexer, TOKEN_DO))
        return NULL;

    id = lexer->index++;

    struct ast_node *do_node = create_node(NODE_DO);

    if (!(do_child = compound_list(lexer)))
    {
        free_ast(do_node);
        lexer->index = id;
        return NULL;
    }

    if (!pop_check(lexer, TOKEN_DONE))
    {
        free_ast(do_node);
        free_ast(do_child);
        lexer->index = id;
        return NULL;
    }

    add_child(do_node, do_child, NULL);
    return do_node;
}
