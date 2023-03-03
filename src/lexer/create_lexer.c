#include "lexer.h"

static void add(struct lexer *lexer, char *val)
{
    lexer->index += 1;
    lexer->input = realloc(lexer->input, sizeof(char *) * (lexer->index + 1));
    *(lexer->input + lexer->index - 1) = val;
    *(lexer->input + lexer->index) = NULL;
}

struct lexer *create_lexer(FILE *file)
{
    struct lexer *lexer = xmalloc(sizeof(struct lexer));
    char *line = NULL;
    size_t len = 0;
    size_t i;

    lexer->index = 0;
    lexer->input = xmalloc(sizeof(char *));
    *lexer->input = NULL;

    while (getline(&line, &len, file) != -1)
    {
        char **tab = create_tab(line);

        if (lexer->index != 0)
            add(lexer, "\n");

        for (i = 0; *(tab + i); i++)
            add(lexer, *(tab + i));

        free(tab);
    }

    free(line);

    add(lexer, "\0");
    lexer->size = lexer->index;
    lexer->index = 0;
    return lexer;
}
