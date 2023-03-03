#include "execution.h"
#include "signal.h"

static int *create_pipelines(size_t nb)
{
    int *pipes = NULL;

    for (size_t i = 0; i < nb - 1; i++)
    {
        int fd[2];
        pipe(fd);

        pipes = xrealloc(pipes, sizeof(int) * 2 * (i + 1));

        *(pipes + i * 2) = fd[1];
        *(pipes + i * 2 + 1) = fd[0];
    }

    return pipes;
}

static void close_id(int *pipes, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        close((*(pipes + i * 2 + 1)));
        close((*(pipes + i * 2)));
    }
}

static int _exec(int *pipes, struct ast_node *node, struct list_variable *list)
{
    size_t nb_children = node->nb_children;
    pid_t *pid_list = xmalloc(sizeof(pid_t) * node->nb_children);
    int *wstatus = xmalloc(sizeof(int *));

    for (size_t i = 0; i < nb_children; i++)
    {
        pid_list[i] = fork();

        if (pid_list[i] == 0)
        {
            if (i != 0)
                dup2((*(pipes + i * 2 - 1)), STDIN_FILENO);

            if (i != (nb_children - 1))
                dup2((*pipes + i * 2), STDOUT_FILENO);

            close_id(pipes, nb_children);

            int rtn = exec_command(*(node->children + i), list);
            free(pid_list);

            exit(rtn);
        }
    }

    close_id(pipes, nb_children);
    int rtn = 0;

    for (size_t i = 0; i < nb_children; i++)
    {
        if (pid_list[i] > 0)
            waitpid(pid_list[i], wstatus, 0);
        if (rtn != 4242 && rtn != 4243)
            rtn = WEXITSTATUS(*wstatus);
    }
    free(wstatus);
    free(pid_list);
    return rtn;
}

int exec_pipeline(struct ast_node *node, struct list_variable *list)
{
    if (!node || node->type != NODE_PIPELINE)
    {
        return 0;
    }

    if (node->nb_children == 0)
    {
        return 0;
    }

    if (node->nb_children == 1)
    {
        if (node->data && *(node->data) == '!')
            return exec_command(*(node->children), list) > 0 ? 0 : 1;
        return exec_command(*(node->children), list);
    }

    int *pipes = create_pipelines(node->nb_children);
    int rtn = _exec(pipes, node, list);

    free(pipes);

    if (node->data && *(node->data) == '!')
    {
        if (rtn > 0)
            rtn = 0;
        else
            rtn = 1;
    }

    return rtn;
}
