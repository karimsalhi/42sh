#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "execution.h"

Test(test_quote, simple_quote)
{
    char *value = strdup("\'single quote\'");
    char *res = quoting(value);

    cr_assert_str_eq("single quote", res);
    free(value);
}
