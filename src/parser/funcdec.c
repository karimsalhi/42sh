#include "parser.h"

static struct ast_node *set(struct token *token)
{
    struct ast_node *node = create_node(NODE_FUNCDEC);
    struct ast_node *child = create_node(NODE_WORD);
    add_node_data(child, token->value);
    free(token);
    add_child(node, child, NULL);

    return node;
}

static size_t freeall(struct ast_node *node, size_t id)
{
    free_ast(node);
    return id;
}

struct ast_node *funcdec(struct lexer *lexer)
{
    size_t id = lexer->index;
    struct token *token = pop(lexer);
    struct ast_node *node = NULL;
    struct ast_node *child = NULL;

    if (token->type == TOKEN_FUNCDEC)
    {
        free(token);
        token = pop(lexer);
    }

    if (token->type != TOKEN_WORD)
    {
        free(token);
        lexer->index = id;
        return NULL;
    }

    node = set(token);

    if (!(pop_check(lexer, TOKEN_LEFT_PARENTHESIS)
          && pop_check(lexer, TOKEN_RIGHT_PARENTHESIS)))
    {
        free_ast(node);
        lexer->index = id;
        return NULL;
    }

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    if (!(child = shell_command(lexer)))
    {
        lexer->index = freeall(node, id);
        return NULL;
    }

    add_child(node, child, NULL);

    return node;
}
