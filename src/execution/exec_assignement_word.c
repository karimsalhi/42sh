#include "execution.h"

struct list_variable *exec_assignement_word(struct ast_node *node,
                                            struct list_variable *list)
{
    if (!node)
        return list;
    char *data = node->data;

    char *variable = data;

    int i = 0;
    while (data[i] && data[i] != '=')
        i++;

    data[i] = '\0';

    char *value = (data + i + 1);

    list = add_variable(list, variable, value);

    return list;
}
