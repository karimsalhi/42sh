#include "execution.h"

struct list_variable *create_list_variable(void)
{
    struct list_variable *list_variable =
        xcalloc(sizeof(struct list_variable), 1);
    return list_variable;
}

static int variable_in_list(struct variable *node, char *variable, char *value)
{
    while (node)
    {
        if (strcmp(variable, node->variable) == 0)
        {
            node->value = value;
            return 1;
        }

        node = node->next;
    }

    return 0;
}

struct list_variable *add_variable(struct list_variable *list_variable,
                                   char *variable, char *value)
{
    if (variable_in_list(list_variable->head, variable, value))
        return list_variable;

    struct variable *new_var = xcalloc(sizeof(struct variable), 1);
    new_var->variable = variable;
    new_var->value = value;

    if (!list_variable->head)
    {
        list_variable->head = new_var;
        list_variable->tail = new_var;
    }
    else
    {
        list_variable->tail->next = new_var;
        list_variable->tail = new_var;
    }

    return list_variable;
}

char *get_value(struct list_variable *list, char *variable)
{
    char *value = NULL;
    struct variable *node = list->head;

    while (node && !value)
    {
        if (strcmp(variable, node->variable) == 0)
        {
            value = node->value;
            break;
        }

        node = node->next;
    }

    return value;
}

void delete_value(struct list_variable *list, char *variable)
{
    if (!variable || !list)
        return;

    struct variable *node = list->head;
    struct variable *before = node;
    while (node)
    {
        if (strcmp(variable, node->variable) == 0)
            break;
        before = node;
        node = node->next;
    }

    if (!node)
        return;

    if (node == list->head)
        list->head = node->next;
    else
        before->next = node->next;

    free(node);
}

static void _free_list_variable(struct variable *node)
{
    if (!node)
        return;
    _free_list_variable(node->next);
    free(node);
}

static void _free_list_function(struct list_function *node)
{
    if (!node)
        return;
    _free_list_function(node->next);
    free(node);
}

void free_list_variable(struct list_variable *list)
{
    if (!list)
        return;

    _free_list_variable(list->head);
    _free_list_function(list->head_f);
    free(list);
}
