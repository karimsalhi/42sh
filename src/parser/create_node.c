#include "parser.h"

struct ast_node *create_node(enum node_type type)
{
    struct ast_node *node = xcalloc(sizeof(struct ast_node), 1);

    node->type = type;

    return node;
}

void add_node_data(struct ast_node *node, char *value)
{
    node->data = value;
}
