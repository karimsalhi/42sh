#include "lexer.h"

struct token *peek(struct lexer *lexer)
{
    size_t id = lexer->index;
    char *value = (lexer->input)[id];
    struct token *token = create_token(value);
    if (!token)
        return NULL;

    return token;
}

int peek_check(struct lexer *lexer, enum token_type type)
{
    struct token *t = peek(lexer);

    int i = type == t->type ? 1 : 0;
    free(t);

    return i;
}
