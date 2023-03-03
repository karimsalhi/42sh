#include "builtin.h"
#include "errno.h"
#include "execution.h"

static int _exec_cmd(char **command)
{
    int pid = fork();

    if (pid == 0)
    {
        execvp(*command, command);
        exit(errno);
    }

    int wstatus;
    waitpid(pid, &wstatus, 0);

    int status = WEXITSTATUS(wstatus);

    int rtn = status == 2 ? 127 : status;

    return rtn;
}

static int _exec_function(char **command, struct list_variable *list)
{
    struct list_function *fun = list->head_f;
    while (fun && strcmp(*command, fun->name) != 0)
        fun = fun->next;
    if (fun)
        return exec_shell_command(fun->command, list);

    return -1;
}

static int _exec_builtins(char **command, struct list_variable *list)
{
    int size = 0;

    while (command[size])
        size++;

    if (strcmp(*command, "cd") == 0)
        return builtin_cd(size, command);

    else if (strcmp(*command, "echo") == 0)
        return builtin_echo(size, command);

    else if (strcmp(*command, "break") == 0)
        return builtin_break(list->is_loop);

    else if (strcmp(*command, "continue") == 0)
        return builtin_continue(list->is_loop);

    else if (strcmp(*command, "exit") == 0)
        builtin_exit();

    return -1;
}

int exec_cmd(char **command, struct list_variable *list)
{
    char **cmd = exec_substitution_cmd(command, list);

    int res = _exec_function(command, list);

    if (res == -1)
        res = _exec_builtins(cmd, list);

    if (res == -1)
        res = _exec_cmd(cmd);

    free_substitution_cmd(cmd);

    return res;
}
