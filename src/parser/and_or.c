#include "parser.h"

struct token *get_token(struct token *token, struct lexer *lexer)
{
    free(token);
    token = pop(lexer);
    return token;
}

static void add_symbol(struct ast_node *node, enum token_type type)
{
    if (!node->data)
    {
        node->data = xmalloc(sizeof(char) * 2);
        *(node->data) = '\0';
        *(node->data + 1) = '\0';
    }
    else
        node->data =
            xrealloc(node->data, (strlen(node->data) + 2) * sizeof(char));

    *(node->data + strlen(node->data)) = '\0';

    if (type == TOKEN_AND)
        strncat(node->data, "&'\0'", 1);
    else
        strncat(node->data, "|'\0'", 1);
}

static void next_pipeline(struct ast_node *node, struct lexer *lexer)
{
    size_t id = lexer->index;

    struct token *token = peek(lexer);
    enum token_type type;

    if (token->type != TOKEN_AND && token->type != TOKEN_OR)
    {
        lexer->index = id;
        free(token);
        return;
    }

    type = token->type;

    lexer->index++;
    free(token);

    token = peek(lexer);
    while (token->type == TOKEN_NEWLINE)
        token = get_token(token, lexer);

    struct ast_node *tmp = NULL;
    if ((tmp = pipeline(lexer)))
    {
        id = add_child(node, tmp, lexer);
    }
    else
    {
        lexer->index = id;
        free(token);
        return;
    }

    lexer->index = id;
    free(token);

    add_symbol(node, type);
    next_pipeline(node, lexer);
}

struct ast_node *and_or(struct lexer *lexer)
{
    struct ast_node *tmp = NULL;

    if ((tmp = pipeline(lexer)) == NULL)
        return NULL;

    struct ast_node *node = create_node(NODE_AND_OR);
    add_child(node, tmp, lexer);

    next_pipeline(node, lexer);

    return node;
}
