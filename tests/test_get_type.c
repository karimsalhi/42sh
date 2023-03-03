#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer.h"

Test(test_simple_lexer, simple_if)
{
    enum token_type type = get_type("if");
    cr_assert(type == TOKEN_IF);
}

Test(test_simple_lexer, simple_then)
{
    enum token_type type = get_type("then");
    cr_assert(type == TOKEN_THEN);
}

Test(test_simple_lexer, simple_elif)
{
    enum token_type type = get_type("elif");
    cr_assert(type == TOKEN_ELIF);
}

Test(test_simple_lexer, simple_else)
{
    enum token_type type = get_type("else");
    cr_assert(type == TOKEN_ELSE);
}

Test(test_simple_lexer, simple_fi)
{
    enum token_type type = get_type("fi");
    cr_assert(type == TOKEN_FI);
}

Test(test_simple_lexer, simple_do)
{
    enum token_type type = get_type("do");
    cr_assert(type == TOKEN_DO);
}

Test(test_simple_lexer, simple_done)
{
    enum token_type type = get_type("done");
    cr_assert(type == TOKEN_DONE);
}

Test(test_simple_lexer, simple_comma)
{
    enum token_type type = get_type(";");
    cr_assert(type == TOKEN_COMMA);
}

Test(test_simple_lexer, simple_word)
{
    enum token_type type = get_type("word");
    cr_assert(type == TOKEN_WORD);
}

Test(test_simple_lexer, simple_eof)
{
    enum token_type type = get_type("\0");
    cr_assert(type == TOKEN_EOF);
}

Test(test_simple_lexer, simple_and)
{
    enum token_type type = get_type("&&");
    cr_assert(type == TOKEN_AND);
}

Test(test_simple_lexer, simple_or)
{
    enum token_type type = get_type("||");
    cr_assert(type == TOKEN_OR);
}

Test(test_simple_lexer, simple_new_line)
{
    enum token_type type = get_type("\n");
    cr_assert(type == TOKEN_NEWLINE);
}
