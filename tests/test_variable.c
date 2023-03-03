#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "execution.h"

Test(test_value, create_list_variable)
{
    struct list_variable *list = create_list_variable();

    cr_assert_not_null(list);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);

    free_list_variable(list);
}

Test(test_value, add_one_variable)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "karim", "doigt de pied gonfle");

    cr_assert_not_null(list);
    cr_assert(list->head == list->tail);
    cr_assert_str_eq(list->head->variable, "karim");
    cr_assert_str_eq(list->head->value, "doigt de pied gonfle");

    free_list_variable(list);
}

Test(test_value, add_three_variable)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "karim", "doigt de pied gonfle");
    list = add_variable(list, "arthur", "nageur");
    list = add_variable(list, "hao", "LOL");

    cr_assert_not_null(list);

    cr_assert_str_eq(list->head->variable, "karim");
    cr_assert_str_eq(list->head->value, "doigt de pied gonfle");

    cr_assert_str_eq(list->head->next->next->variable, "hao");
    cr_assert_str_eq(list->head->next->next->value, "LOL");

    cr_assert_str_eq(list->head->next->variable, "arthur");
    cr_assert_str_eq(list->head->next->value, "nageur");

    free_list_variable(list);
}

Test(test_value, get_value)
{
    struct list_variable *list = create_list_variable();
    list = add_variable(list, "karim", "doigt de pied gonfle");
    list = add_variable(list, "arthur", "nageur");
    list = add_variable(list, "hao", "LOL");
    list = add_variable(list, "messi", "best");
    list = add_variable(list, "adm", "de la merde");
    list = add_variable(list, "messi", "vive le barca");

    char *variable = "arthur";
    cr_assert_str_eq(get_value(list, variable), "nageur");

    variable = "messi";
    cr_assert_str_eq(get_value(list, variable), "vive le barca");

    free_list_variable(list);
}
