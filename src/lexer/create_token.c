#include "lexer.h"
/*
char *duplicate_value(char *input)
{
    size_t size = sizeof(input);
    char *copy = strndup(input, size);
    if (!copy)
        return NULL;

    copy = realloc(copy, size + 1);
    copy[size] = '\0';

    return copy;
}*/

struct token *create_token(char *value)
{
    struct token *token = malloc(sizeof(struct token));
    if (!token)
        return NULL;

    // token->value = duplicate_value(value);
    token->value = value;
    token->type = get_type(value);

    return token;
}
