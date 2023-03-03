#include "parser.h"

size_t add_child(struct ast_node *node, struct ast_node *tmp,
                 struct lexer *lexer)
{
    if (!tmp)
    {
        if (!lexer)
            return 0;
        return lexer->index;
    }
    node->children = xrealloc(node->children,
                              sizeof(node->children) * (node->nb_children + 1));

    *((node->children) + node->nb_children) = tmp;

    node->nb_children++;

    if (lexer)
        return lexer->index;

    return 0;
}
