#include "execution.h"

int exec_root(struct ast_node *node, struct list_variable *list)
{
    int rtn = 0;

    if (!node || node->type != NODE_ROOT)
        return 0;

    for (size_t i = 0; i < node->nb_children; i++)
        rtn = exec_input(node->children[i], list);

    return rtn;
}
