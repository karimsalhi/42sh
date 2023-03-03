#include "execution.h"

char *insert_variable(char *string, char *value, int i,
                      struct list_variable *list)
{
    char *res;
    if (*string == '\"')
        res = strndup(string + 1, --i);
    else
        res = strndup(string, i);

    int j = 0;
    while (value[j] != ' ' && value[j] != '\0' && value[j] != '\"')
        j++;

    char *var = strndup(value, j);
    char *var_val = variable_substitution(var, list);

    res = realloc(res, (strlen(res) + strlen(var_val) + 1));
    res = strcat(res, var_val);

    res = realloc(res, strlen(res) + strlen(value + j) + 1);
    res = strcat(res, (value + j));

    free(var);
    free(string);

    return res;
}

static char *single_quotes(char *value)
{
    char *save = (value + 1);
    int i = 1;

    while (value[i] != '\'')
        i++;

    value[i] = '\0';

    return strdup(save);
}

static char *double_quote(char *value, struct list_variable *list)
{
    char *save = (value + 1);
    int i = 1;

    while (value[i] != '\"')
    {
        if (value[i] == '$')
        {
            value = insert_variable(value, value + i, i, list);
            save = value;
            --i;
            continue;
        }
        i++;
    }

    value[i] = '\0';

    return save;
}

char *quoting(char *value, struct list_variable *list)
{
    if (*value == '\\')
        return strdup(value + 1);

    if (*value == '\"')
        return double_quote(value, list);

    if (*value == '\'')
        return single_quotes(value);

    return NULL;
}
