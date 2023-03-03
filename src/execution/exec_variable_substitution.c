#include "execution.h"

static int valid_hug(char *value)
{
    int i = 0;

    while (value[i] && value[i] != '}')
        i++;

    if (value[i] == '}')
        value[i] = '\0';
    else
        return 0;

    return 1;
}

static int is_hug(char *value)
{
    if (*value != '$')
    {
        return 0;
    }

    if (*(value + 1) == '{')
        return 1;

    return 0;
}

static char *get_hug_value(struct list_variable *list, char *value)
{
    char *val = strdup(value);
    char *res = "";
    if (valid_hug(val + 2))
        res = get_value(list, val + 2);

    free(val);
    return res;
}

char *variable_substitution(char *value, struct list_variable *list)
{
    if (!list)
    {
        return "";
    }

    if (is_hug(value))
        value = get_hug_value(list, value);

    if (*value == '$')
        value = get_value(list, value + 1);

    if (!value)
        return "";

    return strdup(value);
}
