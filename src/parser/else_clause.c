#include "parser.h"

static void *reset(struct ast_node *ELSE, struct ast_node *ELIF,
                   struct ast_node *THEN)
{
    if (!ELSE)
        free_ast(ELSE);
    if (!ELIF)
        free_ast(ELIF);
    if (!THEN)
        free_ast(THEN);
    return NULL;
}

static struct ast_node *elif_clause(struct lexer *lexer,
                                    struct ast_node *ELSE_node, size_t id)
{
    struct ast_node *ELSE_child = NULL;
    struct ast_node *ELIF_child = NULL;
    struct ast_node *THEN_child = NULL;

    if (!(ELIF_child = compound_list(lexer)))
    {
        lexer->index = id;
        return reset(ELSE_child, ELIF_child, THEN_child);
    }

    if (!pop_check(lexer, TOKEN_THEN))
    {
        lexer->index = id;
        return reset(ELSE_child, ELIF_child, THEN_child);
    }

    if (!(THEN_child = compound_list(lexer)))
    {
        lexer->index = id;
        return reset(ELSE_child, ELIF_child, THEN_child);
    }
    add_child(ELSE_node, ELIF_child, NULL);
    add_child(ELSE_node, THEN_child, NULL);
    return ELSE_node;
}

static struct ast_node *_else_clause(struct lexer *lexer,
                                     struct ast_node *ELSE_node)
{
    size_t id = lexer->index++;
    ELSE_node = elif_clause(lexer, ELSE_node, id);
    if (!ELSE_node)
    {
        free_ast(ELSE_node);
        return NULL;
    }
    struct ast_node *else_clause_child = else_clause(lexer);
    if (else_clause_child)
        add_child(ELSE_node, else_clause_child, NULL);
    else
    {
        free_ast(else_clause_child);
    }

    return ELSE_node;
}

struct ast_node *else_clause(struct lexer *lexer)
{
    size_t id;
    struct ast_node *ELSE_child = NULL;
    struct ast_node *ELIF_child = NULL;
    struct ast_node *THEN_child = NULL;

    if (!lexer)
        return NULL;

    struct ast_node *ELSE_node = create_node(NODE_ELSE_CLAUSE);

    if (peek_check(lexer, TOKEN_ELSE))
    {
        id = lexer->index++;
        if (!(ELSE_child = compound_list(lexer)))
        {
            lexer->index = id;
            return reset(ELSE_child, ELIF_child, THEN_child);
        }
        add_child(ELSE_node, ELSE_child, NULL);
    }
    else if (peek_check(lexer, TOKEN_ELIF))
        ELSE_node = _else_clause(lexer, ELSE_node);
    else
    {
        free_ast(ELSE_node);
        return NULL;
    }

    return ELSE_node;
}
