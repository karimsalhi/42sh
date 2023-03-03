#include "parser.h"

static char *get_value(struct token *token)
{
    char *rtn = token->value;
    free(token);
    return rtn;
}

static void loop(struct lexer *lexer, struct ast_node *node)
{
    size_t id = lexer->index;

    while (pop_check(lexer, TOKEN_PIPE))
    {
        if (!peek_check(lexer, TOKEN_WORD))
            break;

        struct ast_node *child = create_node(NODE_WORD);
        add_node_data(child, get_value(pop(lexer)));
        add_child(node, child, NULL);
        id = lexer->index;
    }
    lexer->index = id;
}

struct ast_node *case_item(struct lexer *lexer)
{
    struct ast_node *rtn = create_node(NODE_CASE_ITEM);
    size_t id = lexer->index;

    if (peek_check(lexer, TOKEN_LEFT_PARENTHESIS))
        lexer->index += 1;

    if (!peek_check(lexer, TOKEN_WORD))
    {
        lexer->index = id;
        free_ast(rtn);
        return NULL;
    }

    add_child(rtn, create_node(NODE_WORD), NULL);
    add_node_data(*rtn->children, get_value(pop(lexer)));

    loop(lexer, rtn);

    if (!peek_check(lexer, TOKEN_RIGHT_PARENTHESIS))
    {
        lexer->index = id;
        free_ast(rtn);
        return NULL;
    }
    lexer->index++;

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    struct ast_node *compound_l;

    if ((compound_l = compound_list(lexer)))
        add_child(rtn, compound_l, NULL);

    return rtn;
}
