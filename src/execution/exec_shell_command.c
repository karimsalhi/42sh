#include "execution.h"

int exec_shell_command(struct ast_node *node, struct list_variable *list)
{
    if (!node)
        return 0;

    if ((*node->children)->type == NODE_COMPOUND_LIST)
    {
        if (*node->data == '(')
        {
            int pid = fork();
            int wstatus;
            if (pid == 0)
                exit(exec_compound_list(*node->children, list));

            waitpid(pid, &wstatus, 0);
            return WEXITSTATUS(wstatus);
        }
        else
            return exec_compound_list(*node->children, list);
    }
    if ((*node->children)->type == NODE_RULE_IF)
    {
        return exec_rule_if(*node->children, list);
    }

    if ((*node->children)->type == NODE_WHILE)
    {
        return exec_rule_while(*node->children, list);
    }

    if ((*node->children)->type == NODE_UNTIL)
    {
        return exec_rule_until(*node->children, list);
    }

    if ((*node->children)->type == NODE_FOR)
    {
        return exec_rule_for(*node->children, list);
    }

    if ((*node->children)->type == NODE_RULE_CASE)
    {
        return exec_case(*node->children, list);
    }

    return 0;
}
