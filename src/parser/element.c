#include "parser.h"

// Element return soit un node REDIRECTION ou un node WORD directement

static int is_separator(enum token_type type)
{
    if (type == TOKEN_AMPERSAND)
        return 1;
    if (type == TOKEN_COMMA)
        return 1;
    if (type == TOKEN_EOF)
        return 1;
    if (type == TOKEN_NEWLINE)
        return 1;
    if (type == TOKEN_OR)
        return 1;
    if (type == TOKEN_AND)
        return 1;
    if (type == TOKEN_DOUBLE_AMPERSAND)
        return 1;
    if (type == TOKEN_PIPE)
    {
        return 1;
    }
    if (type == TOKEN_LEFT_PARENTHESIS)
        return 1;
    if (type == TOKEN_RIGHT_PARENTHESIS)
        return 1;
    return 0;
}

struct ast_node *element(struct lexer *lexer)
{
    struct ast_node *node = NULL;

    if ((node = redirection(lexer)))
        return node;

    struct token *token = peek(lexer);

    if (!is_separator(token->type))
    {
        if (token->type == TOKEN_WORD)
            node = create_node(NODE_WORD);
        else
            node = create_node(NODE_OTHER);
        add_node_data(node, token->value);
        lexer->index++;
    }

    free_token(token);

    return node;
}
