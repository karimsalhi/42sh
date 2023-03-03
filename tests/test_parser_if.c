#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer.h"
#include "parser.h"

/*Test(test_if, pop_simple)
{
    char *argv[3] = { "test", "-c", "echo" };
    struct lexer *lexer = _lexer(3, argv);
    struct token *token = pop(lexer);

    cr_assert_str_eq("echo", token->value);

    free_token(token);
    free_lexer(lexer);
}

Test(test_if, test_element)
{
    char *argv[3] = { "test", "-c", "echo" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = element(lexer);

    cr_assert_str_eq("echo", node->data);
    cr_assert(node->type == NODE_ELEMENT);

    free_tab(lexer->input);
    free(lexer);
    free_ast(node);
}*/
