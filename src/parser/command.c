#include "parser.h"

void add_redirection(struct ast_node *node, struct lexer *lexer)
{
    struct ast_node *tmp = NULL;

    while ((tmp = redirection(lexer)))
        add_child(node, tmp, NULL);
}

struct ast_node *command(struct lexer *lexer)
{
    struct ast_node *node = create_node(NODE_COMMAND);

    struct ast_node *tmp = NULL;

    if ((tmp = funcdec(lexer)) != NULL)
    {
        add_child(node, tmp, NULL);
        add_redirection(node, lexer);
    }

    else if ((tmp = simple_command(lexer)) != NULL)
        add_child(node, tmp, NULL);

    else if ((tmp = shell_command(lexer)) != NULL)
    {
        add_child(node, tmp, NULL);
        add_redirection(node, lexer);
    }
    if (!tmp)
    {
        free_ast(node);
        return NULL;
    }

    return node;
}
