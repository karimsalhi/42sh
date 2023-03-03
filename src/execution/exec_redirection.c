#include "execution.h"

static struct list_redirection *add_list(struct redirection *redirection)
{
    struct list_redirection *list = xcalloc(sizeof(struct list_redirection), 1);
    list->redirection = redirection;
    return list;
}

static struct list_redirection *add_redirection(struct list_redirection *list,
                                                struct redirection *red)
{
    if (!list)
        return add_list(red);

    struct list_redirection *tmp = list;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = add_list(red);
    return list;
}

int free_redirection(struct list_redirection *list)
{
    if (!list)
        return 0;

    free_redirection(list->next);

    struct redirection *redirection = list->redirection;
    dup2(redirection->fd, redirection->save);
    close(redirection->save);

    free(redirection);
    free(list);

    return 1;
}

int is_digits(char *value)
{
    int i = 0;
    while (value[i])
    {
        if (value[i] < '0' || value[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int is_valid_fd(int fd)
{
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

struct list_redirection *exec_redirection(struct ast_node *node,
                                          struct list_redirection *list)
{
    struct redirection *red = NULL;
    if (node->type == NODE_REDIRECT_OUTPUT)
        red = exec_redirect(node);
    else if (node->type == NODE_REDIRECT_INPUT)
        red = exec_redirect_input(node);
    else if (node->type == NODE_REDIRECT_APPEND_OUTPUT)
        red = exec_redirect_append_output(node);
    else if (node->type == NODE_REDIRECT_DUP_INPUT)
        red = exec_redirect_dup_input(node);
    else if (node->type == NODE_REDIRECT_DUP_OUTPUT)
        red = exec_redirect_dup_output(node);
    else if (node->type == NODE_REDIRECT_RDWR)
        red = exec_redirect_rdwr(node);

    if (red == NULL)
        return NULL;

    list = add_redirection(list, red);

    return list;
}
