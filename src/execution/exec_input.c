#include "execution.h"

int exec_input(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_INPUT)
        return 0;

    if (node->nb_children == 0)
        return 0;

    return exec_list(*node->children, list);
}
