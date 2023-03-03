#include "parser.h"

static struct ast_node *create_rule_if(struct ast_node *IF_child,
                                       struct ast_node *THEN_child,
                                       struct ast_node *ELSE_child)
{
    struct ast_node *rtn = create_node(NODE_RULE_IF);

    add_child(rtn, IF_child, NULL);
    add_child(rtn, THEN_child, NULL);
    if (ELSE_child)
        add_child(rtn, ELSE_child, NULL);

    return rtn;
}

static void _reset(struct ast_node *IF_child, struct ast_node *THEN_child)
{
    if (IF_child)
        free_ast(IF_child);
    if (THEN_child)
        free_ast(THEN_child);
}

static void *reset(struct ast_node *ELSE_child, struct lexer *lexer, size_t id)
{
    if (ELSE_child)
        free_ast(ELSE_child);
    lexer->index = id;

    return NULL;
}

struct ast_node *rule_if(struct lexer *lexer)
{
    size_t id;
    size_t id2;
    struct ast_node *IF_child = NULL;
    struct ast_node *THEN_child = NULL;
    struct ast_node *ELSE_child = NULL;

    if (!lexer || !peek_check(lexer, TOKEN_IF))
        return NULL;

    id = lexer->index++;

    if (!(IF_child = compound_list(lexer)))
    {
        _reset(IF_child, THEN_child);
        return reset(ELSE_child, lexer, id);
    }

    if (!pop_check(lexer, TOKEN_THEN))
    {
        _reset(IF_child, THEN_child);
        return reset(ELSE_child, lexer, id);
    }

    if (!(THEN_child = compound_list(lexer)))
    {
        _reset(IF_child, THEN_child);
        return reset(ELSE_child, lexer, id);
    }

    id2 = lexer->index;

    if (!(ELSE_child = else_clause(lexer)))
        lexer->index = id2;

    if (!pop_check(lexer, TOKEN_FI))
    {
        _reset(IF_child, THEN_child);
        return reset(ELSE_child, lexer, id);
    }

    return create_rule_if(IF_child, THEN_child, ELSE_child);
}
