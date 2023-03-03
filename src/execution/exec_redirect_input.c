#include "execution.h"

struct redirection *exec_redirect_input(struct ast_node *node)
{
    char *in = (node->children)[0]->data;
    char *out = (node->children)[1]->data;

    int fd_in = atoi(in);
    int fd_out;
    if ((fd_out = open(out, O_RDONLY, DEFFILEMODE)) == -1)
    {
        fprintf(stderr, "42sh: %s: No such file or directory", out);
        return NULL;
    }

    int save = dup(fd_in);
    fd_in = dup2(fd_out, fd_in);

    struct redirection *redirection = xmalloc(sizeof(struct redirection));
    redirection->fd = fd_in;
    redirection->save = save;

    return redirection;
}
