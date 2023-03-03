#include "parser.h"
/*
static struct token *get_token(struct token *token, struct lexer *lexer)
{
    free(token);
    token = pop(lexer);
    return token;
}
*/
struct ast_node *pipeline(struct lexer *lexer)
{
    struct ast_node *node = create_node(NODE_PIPELINE);
    if (peek_check(lexer, TOKEN_NOT))
    {
        lexer->index++;
        node->data = "!";
    }

    struct ast_node *tmp = NULL;

    if ((tmp = command(lexer)) == NULL)
    {
        free_ast(node);
        return NULL;
    }

    add_child(node, tmp, lexer);

    size_t id = lexer->index;

    while (peek_check(lexer, TOKEN_PIPE))
    {
        lexer->index++;
        while (peek_check(lexer, TOKEN_NEWLINE))
            lexer->index++;

        if ((tmp = command(lexer)) == NULL)
            break;

        id = add_child(node, tmp, lexer);
    }

    lexer->index = id;
    return node;
}
