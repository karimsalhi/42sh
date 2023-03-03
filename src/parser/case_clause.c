#include "parser.h"

static void loop(struct lexer *lexer, struct ast_node *node)
{
    size_t id = lexer->index;

    while (pop_check(lexer, TOKEN_DOUBLE_AMPERSAND))
    {
        while (peek_check(lexer, TOKEN_NEWLINE))
            lexer->index++;

        struct ast_node *child = case_item(lexer);

        if (!child)
            break;

        add_child(node, child, NULL);
        id = lexer->index;
    }
    lexer->index = id;
}

struct ast_node *case_clause(struct lexer *lexer)
{
    struct ast_node *rtn = create_node(NODE_CASE_CLAUSE);
    struct ast_node *tmp = case_item(lexer);

    if (!tmp)
    {
        free_ast(rtn);
        return NULL;
    }
    add_child(rtn, tmp, NULL);

    loop(lexer, rtn);

    if (peek_check(lexer, TOKEN_DOUBLE_AMPERSAND))
        lexer->index++;

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    return rtn;
}
