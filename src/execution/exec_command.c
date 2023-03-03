#include "execution.h"

static struct list_redirection *exec_red_command(struct ast_node *node)
{
    struct list_redirection *list_redirection = NULL;
    for (size_t i = 1; i < node->nb_children; ++i)
        list_redirection =
            exec_redirection((node->children[i]), list_redirection);

    return list_redirection;
}

static int command_type_shell(struct ast_node *node, struct list_variable *list)
{
    int c;

    struct list_redirection *list_redirection = exec_red_command(node);

    c = exec_shell_command(*node->children, list);

    if (free_redirection(list_redirection))
    {
        if (c != 0)
            return 1;
        return 0;
    }

    return c;
}

static int command_type_funcdec(struct ast_node *node,
                                struct list_variable *list)
{
    int c;

    struct list_redirection *list_redirection = exec_red_command(node);

    c = exec_funcdec(*node->children, list);

    if (free_redirection(list_redirection))
    {
        if (c != 0)
            return 1;
        return 0;
    }

    return c;
}

int exec_command(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_COMMAND)
        return 0;

    if (((node->children)[0])->type == NODE_SHELL_COMMAND)
        return command_type_shell(node, list);

    if (((node->children)[0])->type == NODE_FUNCDEC)
        return command_type_funcdec(node, list);

    return exec_simple_command(*(node->children), list);
}
