
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer.h"
#include "parser.h"

Test(test_prefix, whithout_equal)
{
    char *argv[3] = { "test", "-c", "not_equal" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = prefix(lexer);

    cr_assert(node == NULL);

    free_lexer(lexer);
    free_ast(node);
}

Test(test_prefix, whit_equal_in_front)
{
    char *argv[3] = { "test", "-c", "=equal" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = prefix(lexer);

    cr_assert(node->type == NODE_WORD);
    cr_assert_str_eq(argv[2], node->data);

    free_lexer(lexer);
    free_ast(node);
}

Test(test_prefix, whit_equal_in_end)
{
    char *argv[3] = { "test", "-c", "equal=" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = prefix(lexer);

    cr_assert(node->type == NODE_ASSIGNEMENT_WORD);
    cr_assert_str_eq(argv[2], node->data);

    free_lexer(lexer);
    free_ast(node);
}

Test(test_prefix, whit_equal_multiple)
{
    char *argv[3] = { "test", "-c", "a=b=c=d" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = prefix(lexer);

    cr_assert(node == NULL);

    free_lexer(lexer);
    free_ast(node);
}
