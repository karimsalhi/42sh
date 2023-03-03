#include "lexer.h"

struct lexer *_lexer(struct option *opt, int argc, char **argv)
{
    FILE *file = input_type(opt, argc, argv);
    if (!file)
        return NULL;

    struct lexer *new_lexer = create_lexer(file);

    fclose(file);

    return new_lexer;
}
