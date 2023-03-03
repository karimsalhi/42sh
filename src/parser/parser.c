#include "parser.h"

struct ast_node *parser(struct option *opt, int argc, char **argv)
{
    struct lexer *lexer = _lexer(opt, argc, argv);

    struct ast_node *ast = input(lexer);

    return ast;
}
