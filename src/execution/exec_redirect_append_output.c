#include "execution.h"

struct redirection *exec_redirect_append_output(struct ast_node *node)
{
    char *in = (node->children)[0]->data;
    char *out = (node->children)[1]->data;

    int fd_in = atoi(in);
    int fd_out;

    if ((fd_out = open(out, O_CREAT | O_APPEND | O_RDWR, DEFFILEMODE)) == -1)
        return NULL;

    int save = dup(fd_in);
    fd_in = dup2(fd_out, fd_in);

    struct redirection *redirection = xmalloc(sizeof(struct redirection));
    redirection->fd = fd_in;
    redirection->save = save;

    return redirection;
}
