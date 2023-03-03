#include "redirection.h"

struct ast_node *redirect_dup_output(struct lexer *lexer)
{
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_DUP_OUTPUT);
    if (!ionumber)
        return NULL;

    char *follow = follow_word(lexer);

    if (!follow)
        return NULL;

    struct ast_node *node =
        create_redirect_node(ionumber, follow, NODE_REDIRECT_DUP_OUTPUT);

    return node;
}
