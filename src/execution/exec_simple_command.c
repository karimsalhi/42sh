#include "execution.h"

static struct list_redirection *exec_red(struct ast_node *node)
{
    struct list_redirection *list_redirection = NULL;
    for (size_t i = 0; i < node->nb_children; ++i)
    {
        list_redirection =
            exec_redirection((node->children)[i], list_redirection);
    }
    return list_redirection;
}

static void exec_assign(struct ast_node *node, struct list_variable *list)
{
    struct ast_node *node_assignement = (node->children)[1];
    for (size_t i = 0; i < node_assignement->nb_children; ++i)
        list = exec_assignement_word((node_assignement->children)[i], list);
}

int exec_simple_command(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_SIMPLE_COMMAND)
    {
        return 0;
    }

    struct list_redirection *list_redirection = NULL;
    if ((node->children)[0]->nb_children != 0)
    {
        if ((list_redirection = exec_red(node->children[0])) == NULL)
            return 1;
    }

    exec_assign(node, list);

    struct ast_node *word_list = (node->children)[2];

    char **argv = xmalloc(sizeof(argv) * (word_list->nb_children + 1));

    for (size_t i = 0; i < word_list->nb_children; i++)
    {
        argv[i] = (word_list->children)[i]->data;
    }

    argv[word_list->nb_children] = NULL;

    int res = 0;
    if (*argv)
    {
        res = exec_cmd(argv, list);
    }

    free(argv);

    if (free_redirection(list_redirection))
    {
        if (res != 0)
            return 1;
        return 0;
    }

    return res;
}
