#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "execution.h"

Test(test_value, simple_substituion)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "42sh", "dur");
    list = add_variable(list, "vacances", "bientot");
    list = add_variable(list, "noel", "cadeau");

    cr_assert_not_null(list);

    char *value = command_substitution("$(noel)", list);
    cr_assert_str_eq("cadeau", value);

    value = command_substitution("`vacances`", list);
    cr_assert_str_eq("bientot", value);

    free_list_variable(list);
}

Test(test_value, not_substituion)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "42sh", "dur");
    list = add_variable(list, "vacances", "bientot");
    list = add_variable(list, "noel", "cadeau");

    cr_assert_not_null(list);

    char *value = command_substitution("$(noele)", list);
    cr_assert_str_eq("", value);

    value = command_substitution("`vacaaaances`", list);
    cr_assert_str_eq("", value);

    free_list_variable(list);
}

Test(test_value, error_substituion)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "42sh", "dur");
    list = add_variable(list, "vacances", "bientot");
    list = add_variable(list, "noel", "cadeau");

    cr_assert_not_null(list);

    char *value = command_substitution("$(noel", list);
    cr_assert_null(value);

    value = command_substitution("`vacaaaances", list);
    cr_assert_null(value);

    free_list_variable(list);
}
