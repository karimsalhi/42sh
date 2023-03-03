#include "lexer.h"

static int is_separator(char c)
{
    if (!c || c == ' ' || c == ';' || c == '(' || c == ')' || c == '['
        || c == '\n' || c == '\t')
        return 1;
    return 0;
}

static int is_solo_separator(char c)
{
    if (!c || c == ';' || c == '(' || c == ')')
        return 1;
    return 0;
}

static int is_redirection(char *str)
{
    if (strncmp(str, "<<-", 3) == 0)
        return 3;
    if (strncmp(str, ">>", 2) == 0)
        return 2;
    if (strncmp(str, "<<", 2) == 0)
        return 2;
    if (strncmp(str, ">&", 2) == 0)
        return 2;
    if (strncmp(str, "<&", 2) == 0)
        return 2;
    if (strncmp(str, ">|", 2) == 0)
        return 2;
    if (strncmp(str, "<>", 2) == 0)
        return 2;
    if (strncmp(str, ">", 1) == 0)
        return 1;
    if (strncmp(str, "<", 1) == 0)
        return 1;

    return 0;
}

static size_t loop(char *str, size_t id)
{
    int i;
    while (!is_separator(*(str + id)))
    {
        if ((i = is_redirection(str + id)) != 0)
        {
            id += i;
            break;
        }
        ++id;
    }

    return id;
}

static size_t loop_id(char *str, size_t id)
{
    while (*(str + id) == ' ' || *(str + id) == '\t')
        ++id;
    return id;
}

char **create_tab(char *str)
{
    size_t id_save;
    size_t nb = 0;

    char **rtn = malloc(sizeof(*rtn));
    *rtn = NULL;

    size_t id = loop_id(str, 0);

    while (*(str + id))
    {
        id_save = id;

        if (*(str + id) == '\0' || *(str + id) == '\n' || *(str + id) == '#')
            break;

        if (strncmp(str + id, ";;", 2) == 0)
            id += 2;

        else if (is_solo_separator(*(str + id)))
            id += 1;

        else
        {
            id = loop(str, id);
        }

        rtn = realloc(rtn, sizeof(*rtn) * (++nb + 1));
        *(rtn + nb - 1) = strndup(str + id_save, id - id_save);
        *(rtn + nb) = NULL;

        id = loop_id(str, id);
    }

    return rtn;
}

void free_lexer(struct lexer *lexer)
{
    char **str = lexer->input;

    if (!str)
        return;

    for (size_t i = 0; i < lexer->size; ++i)
        if (*(str + i)[0] && *(str + i)[0] != '\n')
            free(*(str + i));

    free(str);
    free(lexer);
}
