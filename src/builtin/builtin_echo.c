#include "builtin.h"

static struct echo_opt *init(void)
{
    struct echo_opt *opt = xmalloc(sizeof(struct echo_opt));
    opt->E_opt = 0;
    opt->e_opt = 0;
    opt->n_opt = 0;
    opt->id = 0;
    return opt;
}

static int print_escap_char(char c)
{
    if (c == 'c')
        return -1;
    if (c == '\\')
        fprintf(stdout, "\\");
    if (c == 'a')
        fprintf(stdout, "\a");
    if (c == 'b')
        fprintf(stdout, "\b");
    if (c == 'e')
        fprintf(stdout, "\033");
    if (c == 'f')
        fprintf(stdout, "\f");
    if (c == 'n')
        fprintf(stdout, "\n");
    if (c == 'r')
        fprintf(stdout, "\r");
    if (c == 't')
        fprintf(stdout, "\t");
    if (c == 'v')
        fprintf(stdout, "\v");
    return 0;
}

static int is_escap(char c)
{
    if (c == '\\' || c == 'a' || c == 'b' || c == 'c' || c == 'e' || c == 'f'
        || c == 'n' || c == 'r' || c == 't' || c == 'v')
        return 1;
    else
        return 0;
}

static int print_escap(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '\\')
        {
            if (str[i + 1])
            {
                if (is_escap(str[i + 1]) == 1)
                {
                    if (print_escap_char(str[i + 1]) == -1)
                    {
                        fflush(stdout);
                        return 1;
                    }
                }
                else
                    fprintf(stdout, "%c", str[i + 1]);
                i++;
            }
        }
        else
            fprintf(stdout, "%c", str[i]);
    }
    fflush(stdout);
    return 0;
}

static int get_opt(int argc, char **argv, struct echo_opt *opt)
{
    int j;
    int i;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            int n = opt->n_opt;
            int e = opt->e_opt;
            int E = opt->E_opt;
            for (j = 1;
                 argv[i][j] == 'n' || argv[i][j] == 'e' || argv[i][j] == 'E';
                 j++)
            {
                if (argv[i][j] == 'n')
                    opt->n_opt = 1;
                if (argv[i][j] == 'E')
                    opt->E_opt = 1;
                if (argv[i][j] == 'e')
                    opt->e_opt = 1;
            }
            if ((argv[i][j]) != '\0' || j == 1)
            {
                opt->n_opt = n;
                opt->e_opt = e;
                opt->E_opt = E;
            }
        }
        else
            break;
    }
    opt->id = i;
    return 0;
}

static int my_echo(int argc, char **argv, struct echo_opt *opt)
{
    int i;
    if (opt->e_opt == 0)
    {
        for (i = opt->id; i < argc - 1; i++)
            fprintf(stdout, "%s ", argv[i]);
        if (argv[i])
            fprintf(stdout, "%s", argv[argc - 1]);
    }
    else
    {
        for (i = opt->id; i < argc - 1; i++)
        {
            if (print_escap(argv[i]) == 1)
                return 1;
            fprintf(stdout, " ");
        }
        if (argv[i])
            if (print_escap(argv[argc - 1]) == 1)
                return 1;
    }
    return 0;
}

int builtin_echo(int argc, char **argv)
{
    struct echo_opt *opt = init();

    get_opt(argc, argv, opt);

    if (my_echo(argc, argv, opt) == 1)
        return 0;

    if (opt->n_opt == 0)
        fprintf(stdout, "\n");

    fflush(stdout);
    free(opt);

    return 0;
}
