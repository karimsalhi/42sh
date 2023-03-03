#include "execution.h"
#include "lexer.h"
#include "print_ast.h"

/*static void print(char **rtn)
{
    for (size_t id = 0; *(rtn + id); id++)
    {
        printf("%s$\n", *(rtn + id));
    }
}*/

struct option *assign_c_option(struct option *opt, int *i, int n, char **str)
{
    opt->c_option = 1;
    if (*i + 1 == n)
        opt->c_arg = "";
    else
        opt->c_arg = str[*i + 1];
    *i += 1;
    return opt;
}

struct option *parser_long_option(struct option *opt, int *i, char **str)
{
    if (strcmp(str[*i], "--verbose") == 0)
    {
        opt->verbose_option = 1;
        return opt;
    }
    if (strcmp(str[*i], "--ast-print") == 0)
    {
        opt->ast_option = 1;
        return opt;
    }
    return opt;
}

struct option *parser_option(struct option *opt, int n, char **str)
{
    for (int i = 0; i < n; i++)
    {
        if (str[i][0] == '-')
        {
            if (str[i][1] == '-')
            {
                parser_long_option(opt, &i, str);
                continue;
            }
            if (strcmp(str[i], "-c") == 0)
            {
                assign_c_option(opt, &i, n, str);
                continue;
            }
        }
    }
    return opt;
}
/*static void print_option(struct option *opt)
{
    printf("c_option: %d\n", opt->c_option);
    printf("verbose_option: %d\n", opt->verbose_option);
    printf("ast_option: %d\n", opt->ast_option);
    printf("c_arg: %s\n", opt->c_arg);
}*/

/*int test_exec_var(int argc, char **argv)
{
    struct option *opt = xcalloc(sizeof(struct option), 1);
    if (argc > 1)
        opt = parser_option(opt, argc, argv);

    struct lexer *lexer = _lexer(opt, argc, argv);

    struct ast_node *ast = prefix(lexer);

    struct list_variable *list = create_list_variable();
    list = exec_assignement_word(ast, list);

    printf("%s\n", get_value(list, "a"));

    free_list_variable(list);
    free_ast(ast);
    free_lexer(lexer);

    return 1;
}*/

int main(int argc, char *argv[])
{
    // printf("nb argc: %d\n", argc);

    struct option *opt = xcalloc(sizeof(struct option), 1);
    if (argc > 1)
    {
        opt = parser_option(opt, argc, argv);
        // if (opt)
        // print_option(opt);
    }

    struct lexer *lexer = _lexer(opt, argc, argv);
    if (!lexer)
    {
        free(opt);
        return 1;
    }
    // print(lexer->input);

    struct ast_node *ast = root(lexer);
    if (!ast)
    {
        free(opt);
        free_lexer(lexer);
        fprintf(stderr, "invalid grammar\n");
        return 2;
    }

    if (opt->ast_option == 1)
    {
        print_ast(ast);
    }

    struct list_variable *list = create_list_variable();

    int rtn = exec_root(ast, list);
    if (lexer)
        free_lexer(lexer);

    free_ast(ast);
    free_list_variable(list);
    free(opt);

    // printf("rtn = %d\n", rtn);

    return rtn;
}
