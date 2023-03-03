#include "parser.h"

static char *get_value(struct token *token)
{
    char *rtn = token->value;
    free(token);
    return rtn;
}

static struct ast_node *in_exp(struct lexer *lexer, struct ast_node *for_node)
{
    size_t id = lexer->index;

    if (peek_check(lexer, TOKEN_COMMA))
    {
        lexer->index++;
        return for_node;
    }

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    if (!peek_check(lexer, TOKEN_IN))
    {
        free_ast(for_node);
        lexer->index = id;
        return NULL;
    }

    lexer->index++;

    while (peek_check(lexer, TOKEN_WORD))
    {
        struct ast_node *node_word = create_node(NODE_WORD);
        add_node_data(node_word, get_value(pop(lexer)));
        add_child(for_node, node_word, NULL);
    }

    if (!peek_check(lexer, TOKEN_COMMA) && !peek_check(lexer, TOKEN_NEWLINE))
    {
        free_ast(for_node);
        for_node = NULL;
        lexer->index = id;
        return NULL;
    }
    lexer->index++;
    return for_node;
}

static struct ast_node *free_for_node(struct ast_node *for_node,
                                      struct lexer *lexer, size_t id)
{
    lexer->index = id;
    free_ast(for_node);
    return NULL;
}

struct ast_node *rule_for(struct lexer *lexer)
{
    size_t id;

    if (!lexer || !peek_check(lexer, TOKEN_FOR))
        return NULL;

    id = lexer->index++;

    struct ast_node *for_node = create_node(NODE_FOR);

    if (!peek_check(lexer, TOKEN_WORD))
        return free_for_node(for_node, lexer, id);

    struct ast_node *node_word = create_node(NODE_WORD);
    add_node_data(node_word, get_value(pop(lexer)));
    add_child(for_node, node_word, NULL);

    for_node = in_exp(lexer, for_node);

    if (!for_node)
    {
        lexer->index = id;
        return NULL;
    }

    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;

    struct ast_node *do_node = do_group(lexer);

    if (do_node)
        add_child(for_node, do_node, NULL);
    else
        return free_for_node(for_node, lexer, id);

    return for_node;
}
