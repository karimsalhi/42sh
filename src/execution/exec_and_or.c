#include "execution.h"

int exec_and_or(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_AND_OR)
        return 0;

    int c = exec_pipeline(*(node->children), list);
    if (c == 4242 || c == 4243)
        return c;

    for (size_t i = 1; i < node->nb_children; i++)
    {
        int rtn;

        if ((*(node->data + i - 1) == '|') && c != 0)
        {
            rtn = exec_pipeline(*(node->children + i), list);

            if (rtn == 4242 || rtn == 4243)
                return rtn;

            c = rtn == 0 ? 0 : rtn;
        }

        else if (c == 0 && (*(node->data + i - 1) == '&'))
        {
            rtn = exec_pipeline(*(node->children + i), list);

            if (rtn == 4242 || 4243)
                return rtn;

            c = c > rtn ? c : rtn;
        }
    }

    return c;
}
