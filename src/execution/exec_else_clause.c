#include "execution.h"

int exec_else_clause(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_ELSE_CLAUSE)
        return 0;

    if (node->nb_children == 1)
        return exec_compound_list(*(node->children), list);

    if (exec_compound_list(*node->children, list) == 0)
        return exec_compound_list(*(node->children + 1), list);

    if (node->nb_children == 3)
        return exec_else_clause(*(node->children + 2), list);

    return 1;
}
