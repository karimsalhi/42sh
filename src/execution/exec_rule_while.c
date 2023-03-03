#include "execution.h"

int exec_rule_while(struct ast_node *node, struct list_variable *list)
{
    int rtn = 0;
    int cond;
    if (!node || node->type != NODE_WHILE)
    {
        return 0;
    }

    size_t loop = list->is_loop;
    list->is_loop = 1;

    while ((cond = exec_compound_list(*node->children, list)) || 1)
    {
        if (cond == 4243)
            continue;
        if (cond != 1)
        {
            if (cond == 4242)
                rtn = 0;
            break;
        }
        rtn = exec_do_group(*(node->children + 1), list);

        if (rtn == 4242)
        {
            rtn = 0;
            break;
        }
        if (rtn == 4243)
            rtn = 0;
    }

    list->is_loop = loop;

    return rtn;
}
