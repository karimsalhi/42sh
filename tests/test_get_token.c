#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer.h"

Test(test_simple_token_lexer, simple_if)
{
    struct token *token = create_token("if");
    cr_assert(token->type == TOKEN_IF);
    free(token);
}

Test(test_simple_token_lexer, simple_then)
{
    struct token *token = create_token("then");
    cr_assert(token->type == TOKEN_THEN);
    free(token);
}

Test(test_simple_token_lexer, simple_elif)
{
    struct token *token = create_token("elif");
    cr_assert(token->type == TOKEN_ELIF);
    free(token);
}

Test(test_simple_token_lexer, simple_else)
{
    struct token *token = create_token("else");
    cr_assert(token->type == TOKEN_ELSE);
    free(token);
}

Test(test_simple_token_lexer, simple_fi)
{
    struct token *token = create_token("fi");
    cr_assert(token->type == TOKEN_FI);
    free(token);
}

Test(test_simple_token_lexer, simple_do)
{
    struct token *token = create_token("do");
    cr_assert(token->type == TOKEN_DO);
    free(token);
}

Test(test_simple_token_lexer, simple_done)
{
    struct token *token = create_token("done");
    cr_assert(token->type == TOKEN_DONE);
    free(token);
}

Test(test_simple_token_lexer, simple_comma)
{
    struct token *token = create_token(";");
    cr_assert(token->type == TOKEN_COMMA);
    free(token);
}

Test(test_simple_token_lexer, simple_word)
{
    struct token *token = create_token("word");
    cr_assert(token->type == TOKEN_WORD);
    free(token);
}

Test(test_simple_token_lexer, simple_and)
{
    struct token *token = create_token("&&");
    free(token);
}

Test(test_simple_token_lexer, simple_or)
{
    struct token *token = create_token("||");
    cr_assert(token->type == TOKEN_OR);
    free(token);
}

Test(test_simple_token_lexer, simple_new_line)
{
    struct token *token = create_token("\n");
    cr_assert(token->type == TOKEN_NEWLINE);
    free(token);
}

Test(test_simple_token_lexer, simple_eof)
{
    struct token *token = create_token("\0");
    cr_assert(token->type == TOKEN_EOF);
    free(token);
}
