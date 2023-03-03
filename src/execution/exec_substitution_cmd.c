#include "execution.h"

static int size(char **cmd)
{
    int i = 0;
    while (cmd[i])
        i++;
    return i;
}

char **exec_substitution_cmd(char **command, struct list_variable *list)
{
    char **tab = xmalloc(sizeof(char *) * (size(command) + 1));

    int i = 0;
    while (command[i])
    {
        if (*command[i] == '\'' || *command[i] == '\"' || *command[i] == '\\')
            tab[i] = quoting(command[i], list);
        else if (*command[i] == '$')
            tab[i] = variable_substitution(command[i], list);
        else
            tab[i] = strdup(command[i]);
        i++;
    }

    tab[i] = NULL;

    return tab;
}

void free_substitution_cmd(char **command)
{
    int i = 0;
    while (command[i])
    {
        if (strcmp("", command[i]) != 0)
            free(command[i]);
        i++;
    }
    free(command);
}
