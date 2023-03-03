#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer.h"
#include "redirection.h"

Test(test_simple_redirection, get_first_output_redirection_type)
{
    enum token_type type = get_type(">");
    cr_assert(type == TOKEN_REDIRECTION_OUTPUT);
}

Test(test_simple_redirection, get_second_output_redirection_type)
{
    enum token_type type = get_type(">|");
    cr_assert(type == TOKEN_REDIRECTION_OUTPUT);
}

Test(test_simple_redirection, get_first_input_redirection_type)
{
    enum token_type type = get_type("<");
    cr_assert(type == TOKEN_REDIRECTION_INPUT);
}

Test(test_simple_redirection, get_append_output_redirection_type)
{
    enum token_type type = get_type(">>");
    cr_assert(type == TOKEN_REDIRECTION_APPEND_OUTPUT);
}

Test(test_simple_redirection, get_dup_input_redirection_type)
{
    enum token_type type = get_type("<&");
    cr_assert(type == TOKEN_REDIRECTION_DUP_INPUT);
}

Test(test_simple_redirection, get_dup_output_redirection_type)
{
    enum token_type type = get_type(">&");
    cr_assert(type == TOKEN_REDIRECTION_DUP_OUTPUT);
}

Test(test_simple_redirection, get_read_write_redirection_type)
{
    enum token_type type = get_type("<>");
    cr_assert(type == TOKEN_REDIRECTION_RDWR);
}

Test(test_simple_redirection, get_ionumber_not_valid)
{
    char *argv[3] = { "test", "-c", "not redirection" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_OUTPUT);

    cr_assert_null(ionumber);

    free_lexer(lexer);
}

Test(test_simple_redirection, get_ionumber_valid)
{
    char *argv[3] = { "test", "-c", ">" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_OUTPUT);

    cr_assert_str_eq(ionumber, "1");

    free_lexer(lexer);
}

Test(test_simple_redirection, get_ionumber_valid_number)
{
    char *argv[3] = { "test", "-c", "12345>" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_OUTPUT);

    cr_assert_str_eq(ionumber, "12345");

    free_lexer(lexer);
}

Test(test_simple_redirection, get_ionumber_not_valid_type)
{
    char *argv[3] = { "test", "-c", "12345>" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_INPUT);

    cr_assert_null(ionumber);

    free_lexer(lexer);
}

Test(test_simple_redirection, get_ionumber__valid_type_append)
{
    char *argv[3] = { "test", "-c", "12345>>" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_APPEND_OUTPUT);

    cr_assert_str_eq(ionumber, "12345");

    free_lexer(lexer);
}

Test(test_simple_redirection, not_valid_follow)
{
    char *argv[3] = { "test", "-c", "if redirection" };
    struct lexer *lexer = _lexer(3, argv);
    char *word = follow_word(lexer);

    cr_assert_null(word);

    free_lexer(lexer);
}

Test(test_simple_redirection, valid_follow)
{
    char *argv[3] = { "test", "-c", "redirection" };
    struct lexer *lexer = _lexer(3, argv);
    char *word = follow_word(lexer);

    cr_assert_str_eq(word, "redirection");

    free_lexer(lexer);
}

Test(test_simple_redirection, valid_ionumber_follow)
{
    char *argv[3] = { "test", "-c", "21>&redirection" };
    struct lexer *lexer = _lexer(3, argv);
    char *ionumber = get_io_redirection(lexer, TOKEN_REDIRECTION_DUP_OUTPUT);

    cr_assert(lexer->index == 1);
    cr_assert_str_eq((lexer->input)[lexer->index], "redirection");

    char *word = follow_word(lexer);

    cr_assert_str_eq(ionumber, "21");
    cr_assert_str_eq(word, "redirection");

    free_lexer(lexer);
}

Test(test_simple_redirection, not_valid_redirection_grammar)
{
    char *argv[3] = { "test", "-c", "not redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirect_output(lexer);

    cr_assert_null(node);

    free_lexer(lexer);
}

Test(test_simple_redirection, valid_redirection_grammar)
{
    char *argv[3] = { "test", "-c", "> redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirect_output(lexer);

    cr_assert(node->type == NODE_REDIRECT_OUTPUT);

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_output)
{
    char *argv[3] = { "test", "-c", ">| redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_OUTPUT);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "1");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_input)
{
    char *argv[3] = { "test", "-c", "< redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_INPUT);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "0");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_append)
{
    char *argv[3] = { "test", "-c", ">> redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_APPEND_OUTPUT);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "1");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_dup_output)
{
    char *argv[3] = { "test", "-c", ">& redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_DUP_OUTPUT);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "1");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_dup_input)
{
    char *argv[3] = { "test", "-c", "<& redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_DUP_INPUT);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "0");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}

Test(test_simple_redirection, valid_redirection_rdwr)
{
    char *argv[3] = { "test", "-c", "<> redirection" };
    struct lexer *lexer = _lexer(3, argv);
    struct ast_node *node = redirection(lexer);

    cr_assert(node->type == NODE_REDIRECT_RDWR);

    struct ast_node *io = (node->children)[0];
    struct ast_node *data = (node->children)[1];

    cr_assert(io->type == NODE_IONUMBER);
    cr_assert_str_eq(io->data, "0");

    cr_assert(data->type == NODE_WORD);
    cr_assert_str_eq(data->data, "redirection");

    free_lexer(lexer);
    free_ast(node);
}
