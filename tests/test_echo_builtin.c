#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "builtin.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(test_echo, exit_code, .init = redirect_all_stdout)
{
    char *argv[1] = { "test" };
    builtin_echo(1, argv);

    cr_assert_stdout_eq_str("test\n");
}
