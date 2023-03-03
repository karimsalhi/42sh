#include "redirection.h"

struct ast_node *redirect_here_document(struct lexer *lexer)
{
    struct ast_node *node = NULL;
    struct ast_node *follow = NULL;

    char *ionumber = get_ionumber(lexer);
    if (!ionumber)
        ionumber = "0";
    size_t id = lexer->index;

    struct token *token = peek(lexer);

    if (token->type != TOKEN_REDIRECTION_HERE_DOCUMENT)
    {
        free(token);
        return NULL;
    }

    lexer->index++;
    free(token);

    if (!(follow = follow_word(lexer)))
    {
        lexer->index = id;
        return NULL;
    }

    struct ast_node *io = create_node(NODE_IONUMBER);
    add_node_data(io, ionumber);

    node = create_node(NODE_REDIRECT_HERE_DOCUMENT);
    add_child(node, io, NULL);
    add_child(node, follow, NULL);

    return node;
}
