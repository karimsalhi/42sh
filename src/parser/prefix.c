#include "parser.h"

static int find_equal(char *value)
{
    int equal = 0;
    while (*value)
    {
        if (*value == '=')
            equal++;
        value++;
    }
    return equal == 1;
}

static struct ast_node *check_assignement_word(struct lexer *lexer)
{
    struct token *token = peek(lexer);
    char *value = token->value;

    if (token->type != TOKEN_WORD || !find_equal(token->value))
    {
        free_token(token);
        return NULL;
    }

    lexer->index++;
    struct ast_node *node = NULL;

    if (*value != '=')
        node = create_node(NODE_ASSIGNEMENT_WORD);
    else
        node = create_node(NODE_WORD);

    add_node_data(node, value);

    free_token(token);

    return node;
}

struct ast_node *prefix(struct lexer *lexer)
{
    size_t id = lexer->index;
    struct ast_node *node = NULL;

    if ((node = check_assignement_word(lexer)) != NULL)
        return node;
    else if ((node = redirection(lexer)) != NULL)
        return node;

    lexer->index = id;

    return node;
}
