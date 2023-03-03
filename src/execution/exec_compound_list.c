#include "execution.h"

static int exec_elems(struct ast_node *node, size_t n,
                      struct list_variable *list)
{
    if (n == node->nb_children - 1)
        return exec_and_or(*(node->children + n), list);

    int rtn = exec_and_or(*(node->children + n), list);
    if (rtn == 4242 || rtn == 4243)
        return rtn;
    return exec_elems(node, n + 1, list);
}

int exec_compound_list(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_COMPOUND_LIST)
        return 0;

    return exec_elems(node, 0, list);
}
