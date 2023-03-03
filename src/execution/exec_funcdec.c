#include "execution.h"

int exec_funcdec(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_FUNCDEC)
    {
        return 1;
    }

    struct list_function *new = xmalloc(sizeof(*new));

    new->name = node->children[0]->data;
    new->command = node->children[1];
    new->next = NULL;

    if (list->head_f == NULL)
        list->head_f = new;

    else
        list->tail_f->next = new;

    list->tail_f = new;
    list->size_f++;

    return 0;
}
