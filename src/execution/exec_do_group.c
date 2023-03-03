#include "execution.h"

int exec_do_group(struct ast_node *node, struct list_variable *list)
{
    if (node->type != NODE_DO)
        return 0;

    return exec_compound_list(*node->children, list);
}
