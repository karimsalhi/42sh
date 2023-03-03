#include "parser.h"

struct ast_node *list(struct lexer *lexer)
{
    struct ast_node *tmp = NULL;

    if ((tmp = and_or(lexer)) == NULL)
        return NULL;

    struct ast_node *node = create_node(NODE_LIST);
    add_child(node, tmp, lexer);

    size_t id = lexer->index;

    while (peek_check(lexer, TOKEN_COMMA) || peek_check(lexer, TOKEN_AMPERSAND))
    {
        lexer->index++;
        if ((tmp = and_or(lexer)) == NULL)
        {
            break;
        }

        id = add_child(node, tmp, lexer);
    }

    lexer->index = id;

    if (peek_check(lexer, TOKEN_COMMA) || peek_check(lexer, TOKEN_AMPERSAND))
        lexer->index++;

    return node;
}
