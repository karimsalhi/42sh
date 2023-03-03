#include "lexer.h"

void free_token(struct token *token)
{
    // free(token->value);
    free(token);
}
