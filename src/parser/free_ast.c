#include "parser.h"

int freeable(struct ast_node *node)
{
    if (node->type == NODE_AND_OR)
        return 1;
    if (node->type == NODE_COMPOUND_LIST)
        return 1;
    if (node->type == NODE_LIST)
        return 1;
    return 0;
}

void free_ast(struct ast_node *node)
{
    if (!node)
        return;

    if (node->data && freeable(node))
        free(node->data);

    for (size_t i = 0; i < node->nb_children; i++)
        free_ast((node->children)[i]);

    if (node->nb_children > 0)
        free(node->children);
    free(node);
}
