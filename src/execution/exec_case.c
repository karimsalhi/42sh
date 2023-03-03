#include <fnmatch.h>

#include "execution.h"

static int _case_item(char *var, struct ast_node *node,
                      struct list_variable *list)
{
    for (size_t i = 0;
         i < node->nb_children && node->children[i]->type == NODE_WORD; i++)
    {
        if (fnmatch(node->children[i]->data, var, 0) == 0)
        {
            if (node->children[node->nb_children - 1]->type
                == NODE_COMPOUND_LIST)
                return exec_compound_list(node->children[node->nb_children - 1],
                                          list);
            return 0;
        }
    }

    return -1;
}

static int _case_clause(char *var, struct ast_node *node,
                        struct list_variable *list)
{
    int rtn;
    for (size_t i = 0; i < node->nb_children; i++)
    {
        rtn = _case_item(var, node->children[i], list);
        if (rtn >= 0)
            return rtn;
    }

    return 0;
}

int exec_case(struct ast_node *node, struct list_variable *list)
{
    if (node->nb_children == 1)
        return 0;

    char *var = node->children[0]->data;
    if (*var == '$')
    {
        char *var2 = variable_substitution(var, list);
        int res = _case_clause(var2, node->children[1], list);
        if (strcmp(var2, "") != 0)
            free(var2);
        return res;
    }

    return _case_clause(var, node->children[1], list);
}
