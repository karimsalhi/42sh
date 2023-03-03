#include "parser.h"

static struct ast_node *create_simple_command_node(void)
{
    struct ast_node *node = create_node(NODE_SIMPLE_COMMAND);

    add_child(node, create_node(NODE_LIST_REDIRECTION), NULL);
    add_child(node, create_node(NODE_LIST_ASSIGNEMENT), NULL);
    add_child(node, create_node(NODE_LIST_WORD), NULL);

    return node;
}

static int is_redirection(enum node_type type)
{
    switch (type)
    {
    case NODE_REDIRECT_OUTPUT:
        return 1;
    case NODE_REDIRECT_INPUT:
        return 1;
    case NODE_REDIRECT_APPEND_OUTPUT:
        return 1;
    case NODE_REDIRECT_DUP_INPUT:
        return 1;
    case NODE_REDIRECT_DUP_OUTPUT:
        return 1;
    case NODE_REDIRECT_RDWR:
        return 1;
    default:
        return 0;
    }
    return 0;
}

static size_t add_list_children(struct ast_node *node, struct ast_node *tmp,
                                struct lexer *lexer)
{
    size_t id = lexer->index;

    if (is_redirection(tmp->type))
        id = add_child((node->children)[0], tmp, lexer);
    else if (tmp->type == NODE_ASSIGNEMENT_WORD)
        id = add_child((node->children)[1], tmp, lexer);
    else if (tmp->type == NODE_WORD || tmp->type == NODE_OTHER)
        id = add_child((node->children)[2], tmp, lexer);

    return id;
}

static int check_list_empty(struct ast_node *node)
{
    return node->children[0]->nb_children + node->children[1]->nb_children == 0;
}

struct ast_node *simple_command(struct lexer *lexer)
{
    struct ast_node *node = create_simple_command_node();

    struct ast_node *tmp = NULL;
    size_t id = lexer->index;

    while ((tmp = prefix(lexer)) != NULL)
        id = add_list_children(node, tmp, lexer);

    lexer->index = id;

    if ((check_list_empty(node) && (tmp = element(lexer)) == NULL)
        || (tmp && tmp->type == NODE_OTHER))
    {
        if (tmp != NULL)
            free_ast(tmp);
        lexer->index = id;
        free_ast(node);
        return NULL;
    }
    if (tmp)
    {
        id = add_list_children(node, tmp, lexer);

        while ((tmp = element(lexer)) != NULL)
            id = add_list_children(node, tmp, lexer);

        lexer->index = id;
    }

    return node;
}
