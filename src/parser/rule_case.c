#include "parser.h"

static char *get_value(struct token *token)
{
    char *rtn = token->value;
    free(token);
    return rtn;
}

static void loop_newline(struct lexer *lexer)
{
    while (peek_check(lexer, TOKEN_NEWLINE))
        lexer->index++;
}

struct ast_node *rule_case(struct lexer *lexer)
{
    size_t id = lexer->index;

    if (!peek_check(lexer, TOKEN_CASE))
        return NULL;

    lexer->index++;
    struct ast_node *rtn = create_node(NODE_RULE_CASE);

    struct ast_node *child_word = create_node(NODE_WORD);
    add_node_data(child_word, get_value(pop(lexer)));
    add_child(rtn, child_word, NULL);

    loop_newline(lexer);

    if (!pop_check(lexer, TOKEN_IN))
    {
        lexer->index = id;
        free_ast(rtn);
        return NULL;
    }

    loop_newline(lexer);

    struct ast_node *child_else = case_clause(lexer);
    if (child_else)
        add_child(rtn, child_else, NULL);

    if (!pop_check(lexer, TOKEN_ESAC))
    {
        lexer->index = id;
        free_ast(rtn);
        return NULL;
    }

    return rtn;
}
