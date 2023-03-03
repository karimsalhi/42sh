#include "redirection.h"

static int is_digit(char value)
{
    if (value >= '0' && value <= '9')
        return 1;
    return 0;
}

static char *get_io_type(enum token_type type)
{
    switch (type)
    {
    case TOKEN_REDIRECTION_OUTPUT:
        return "1";
    case TOKEN_REDIRECTION_INPUT:
        return "0";
    case TOKEN_REDIRECTION_APPEND_OUTPUT:
        return "1";
    case TOKEN_REDIRECTION_DUP_INPUT:
        return "0";
    case TOKEN_REDIRECTION_DUP_OUTPUT:
        return "1";
    case TOKEN_REDIRECTION_RDWR:
        return "0";
    default:
        return NULL;
    }
    return NULL;
}

char *get_io_redirection(struct lexer *lexer, enum token_type type)
{
    struct token *token = peek(lexer);
    char *ionumber = token->value;

    if (token->type == TOKEN_WORD)
    {
        size_t i = 0;
        while (is_digit(ionumber[i]))
            i++;

        if (type == get_redirection(ionumber + i))
            ionumber[i] = '\0';
        else
            ionumber = NULL;
    }
    else
    {
        if (type == token->type)
            ionumber = get_io_type(type);
        else
            ionumber = NULL;
    }

    if (ionumber)
        lexer->index++;

    free(token);
    return ionumber;
}

char *follow_word(struct lexer *lexer)
{
    struct token *token = peek(lexer);
    char *word = NULL;

    if (token->type == TOKEN_WORD)
    {
        word = token->value;
        lexer->index++;
    }

    free(token);

    return word;
}

struct ast_node *create_redirect_node(char *io, char *follow,
                                      enum node_type type)
{
    struct ast_node *node_io = create_node(NODE_IONUMBER);
    add_node_data(node_io, io);

    struct ast_node *node_follow = create_node(NODE_WORD);
    add_node_data(node_follow, follow);

    struct ast_node *node = create_node(type);
    add_child(node, node_io, NULL);
    add_child(node, node_follow, NULL);

    return node;
}
