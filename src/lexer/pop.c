#include "lexer.h"

struct token *pop(struct lexer *lexer)
{
    if (!lexer)
        return NULL;
    size_t id = lexer->index;
    char *value = (lexer->input)[id];

    struct token *token = create_token(value);
    if (!token)
        return NULL;

    if (*lexer->input[id] != '\0')
        lexer->index += 1;

    return token;
}

struct token *pop_command(struct lexer *lexer)
{
    struct token *rtn = pop(lexer);
    rtn->type = TOKEN_WORD;

    return rtn;
}

int pop_check(struct lexer *lexer, enum token_type type)
{
    struct token *t = pop(lexer);

    int i = type == t->type ? 1 : 0;
    free(t);

    return i;
}
