#include "builtin.h"
int builtin_cd(int argc, char **argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "%s: too many arguments\n", argv[0]);
        return 1;
    }
    char str[1024];
    char *dst = NULL;
    char *home = NULL;

    if ((home = getenv("HOME")) == NULL)
        home = "/";

    if ((dst = argv[1]) == NULL)
        dst = home;

    getcwd(str, 1024);
    setenv("OLDPWD", str, 1);

    if (chdir(dst) == 0)
    {
        getcwd(str, 1024);
        setenv("PWD", str, 1);
    }
    else
    {
        fprintf(stderr, "%s: No such file or directory\n", argv[1]);
        return 1;
    }
    return 0;
}

/*int main(int argc, char **argv)
{
    char str[1024];
    if (builtin_cd(argc, argv) == 0)
        printf("%s\n", getcwd(str, 1024));
    return 0;
}*/
