#include "execution.h"

int exec_rule_for(struct ast_node *node, struct list_variable *list)
{
    int rtn = 0;

    if (node->type != NODE_FOR)
        return 0;

    char *var = node->children[0]->data;
    size_t loop = list->is_loop;
    list->is_loop = 1;
    for (size_t i = 1; i < node->nb_children - 1; i++)
    {
        add_variable(list, var, node->children[i]->data);

        rtn = exec_do_group(node->children[node->nb_children - 1], list);

        if (rtn == 4242)
        {
            rtn = 0;
            break;
        }
        if (rtn == 4243)
            rtn = 0;
    }
    list->is_loop = loop;

    delete_value(list, var);

    return rtn;
}
