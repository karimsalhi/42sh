#include "parser.h"

static struct ast_node *hug_compound_list(struct lexer *lexer)
{
    struct ast_node *tmp = NULL;

    if (peek_check(lexer, TOKEN_LEFT_HUG))
    {
        lexer->index++;
        if (!(tmp = compound_list(lexer)))
            return NULL;

        if (!peek_check(lexer, TOKEN_RIGHT_HUG))
        {
            free_ast(tmp);
            return NULL;
        }

        lexer->index++;
        return tmp;
    }

    return NULL;
}

static struct ast_node *parenthesis_compound_list(struct lexer *lexer)
{
    struct ast_node *tmp = NULL;

    if (peek_check(lexer, TOKEN_LEFT_PARENTHESIS))
    {
        lexer->index++;
        if (!(tmp = compound_list(lexer)))
            return NULL;

        if (!peek_check(lexer, TOKEN_RIGHT_PARENTHESIS))
        {
            free_ast(tmp);
            return NULL;
        }

        lexer->index++;

        return tmp;
    }

    return NULL;
}

static struct ast_node *return_child(struct ast_node *rtn,
                                     struct ast_node *node)
{
    add_child(rtn, node, NULL);
    return rtn;
}

struct ast_node *shell_command(struct lexer *lexer)
{
    struct ast_node *node = NULL;
    struct ast_node *rtn = create_node(NODE_SHELL_COMMAND);

    if ((node = hug_compound_list(lexer)) != NULL)
    {
        rtn->data = "{";
        return return_child(rtn, node);
    }

    if ((node = parenthesis_compound_list(lexer)) != NULL)
    {
        add_child(rtn, node, NULL);
        rtn->data = "(";
        return rtn;
    }
    if ((node = rule_if(lexer)) != NULL)
        return return_child(rtn, node);

    if ((node = rule_for(lexer)) != NULL)
        return return_child(rtn, node);

    if ((node = while_rule(lexer)) != NULL)
        return return_child(rtn, node);

    if ((node = until_rule(lexer)) != NULL)
        return return_child(rtn, node);

    if ((node = rule_case(lexer)) != NULL)
        return return_child(rtn, node);

    free_ast(rtn);

    return NULL;
}
