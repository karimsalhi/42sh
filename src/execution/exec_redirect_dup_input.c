#include "execution.h"

static int valid_word(char *out, int fd_in)
{
    int fd_out;
    if (is_digits(out))
    {
        fd_out = atoi(out);
        if (!is_valid_fd(fd_out))
        {
            fprintf(stderr, "42sh: %s: Bad file descriptor\n", out);
            return -1;
        }
    }
    else
    {
        if (strcmp(out, "-") == 0)
        {
            close(fd_in);
            fd_out = fd_in;
        }
        else
        {
            fprintf(stderr, "42sh: %s: ambiguous redirect\n", out);
            return -1;
        }
    }
    return fd_out;
}

struct redirection *exec_redirect_dup_input(struct ast_node *node)
{
    char *in = (node->children)[0]->data;
    char *out = (node->children)[1]->data;

    int fd_in = atoi(in);
    int save = dup(fd_in);
    int fd_out = valid_word(out, fd_in);

    if (fd_out == -1)
        return NULL;

    if (fd_out != fd_in)
        fd_in = dup2(fd_out, fd_in);

    struct redirection *redirection = xmalloc(sizeof(struct redirection));
    redirection->fd = fd_in;
    redirection->save = save;

    return redirection;
}
