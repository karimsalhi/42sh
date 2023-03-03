#include "parser.h"

static void add_symbol(struct ast_node *node, struct token *token)
{
    enum token_type type = token->type;
    free(token);
    if (!node->data)
    {
        node->data = xmalloc(sizeof(char) * 2);
        *(node->data) = '\0';
        *(node->data + 1) = '\0';
    }
    else
        node->data = xrealloc(node->data, sizeof(node->data) + sizeof(char));

    *(node->data + strlen(node->data)) = '\0';

    if (type == TOKEN_AMPERSAND)
        strncat(node->data, "&'\0'", 1);
    else
        strncat(node->data, ";'\0'", 1);
}

static int star_expression(struct lexer *lexer, struct ast_node *node)
{
    size_t id = lexer->index;

    if (!(peek_check(lexer, TOKEN_COMMA) || peek_check(lexer, TOKEN_NEWLINE)
          || peek_check(lexer, TOKEN_AMPERSAND)))
    {
        return 0;
    }

    add_symbol(node, pop(lexer));

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    struct ast_node *and = and_or(lexer);

    if (!and)
    {
        node->data[strlen(node->data) - 1] = '\0';
        lexer->index = id;
        return 0;
    }

    add_child(node, and, NULL);

    return 1;
}

struct ast_node *compound_list(struct lexer *lexer)
{
    size_t id = lexer->index;

    //('/n')*
    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    // and_or
    struct ast_node *and = and_or(lexer);

    if (!and)
    {
        lexer->index = id;
        return NULL;
    }

    struct ast_node *rtn = create_node(NODE_COMPOUND_LIST);

    add_child(rtn, and, NULL);

    //((';'|'&'|'/n') ('/n')* and_or)*
    while (star_expression(lexer, rtn))
        ;

    //[(';'|'&'|'/n') ('/n')*]
    if ((peek_check(lexer, TOKEN_COMMA) || peek_check(lexer, TOKEN_NEWLINE)
         || peek_check(lexer, TOKEN_AMPERSAND)))
    {
        add_symbol(rtn, pop(lexer));
        while (peek_check(lexer, TOKEN_NEWLINE))
            lexer->index++;
    }

    return rtn;
}
