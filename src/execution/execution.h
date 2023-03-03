#ifndef EXECUTION_H
#define EXECUTION_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"

#ifndef DEFFILEMODE
#    define DEFFILEMODE                                                        \
        (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#endif

struct redirection
{
    int fd;
    int save;
};

struct list_redirection
{
    struct redirection *redirection;
    struct list_redirection *next;
};

struct variable
{
    char *variable;
    char *value;
    struct variable *next;
};

struct list_function
{
    char *name;
    struct ast_node *command;
    struct list_function *next;
};

struct list_variable
{
    struct variable *head;
    struct variable *tail;
    size_t size;

    struct list_function *head_f;
    struct list_function *tail_f;
    size_t size_f;

    size_t is_loop;
};

/**
 * \brief main execution function
 *
 * \param node ast-node
 * \param list list of variable
 */
void execution(struct ast_node *node, struct list_variable *list);

int exec_root(struct ast_node *node, struct list_variable *list);

/**
 * \brief execution of a command
 *
 * \param cmd table of command
 * \param list list of variable
 */
int exec_cmd(char **cmd, struct list_variable *list);

/**
 * \brief free table of command
 *
 * \param cmd table of command
 */

void free_command(char **cmd);

/**
 * \brief execute the rule input
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_input(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the rule list
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_list(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the and_or rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_and_or(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the pipeline rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_pipeline(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the command rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_command(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the simple-command rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_simple_command(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the shell command rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_shell_command(struct ast_node *node, struct list_variable *list);
int exec_funcdec(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the until rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_rule_until(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the while rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_rule_while(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the do-groupe rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_do_group(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the for rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_rule_for(struct ast_node *node, struct list_variable *list);

/**
 * \brief free the list of redirection
 *
 * \param list list of redirection
 */
int free_redirection(struct list_redirection *list);
/**
 * \brief is-digits function
 *
 * \param value string
 */
int is_digits(char *value);

/**
 * \brief check the validy of a fd
 *
 * \param fd file-descriptor
 */
int is_valid_fd(int fd);
/**
 * \brief execution redirection function
 *
 * \param node ast-node
 * \param list list of redirection
 */
struct list_redirection *exec_redirection(struct ast_node *node,
                                          struct list_redirection *list);
struct redirection *exec_redirect(struct ast_node *node);
struct redirection *exec_redirect_input(struct ast_node *node);
struct redirection *exec_redirect_append_output(struct ast_node *node);
struct redirection *exec_redirect_dup_input(struct ast_node *node);
struct redirection *exec_redirect_dup_output(struct ast_node *node);
struct redirection *exec_redirect_rdwr(struct ast_node *node);

/**
 * \brief execute the if rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_rule_if(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the compound-list rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_compound_list(struct ast_node *node, struct list_variable *list);
/**
 * \brief execute the else clause rule
 *
 * \param node ast-node
 * \param list list of variable
 */
int exec_else_clause(struct ast_node *node, struct list_variable *list);
int exec_case(struct ast_node *node, struct list_variable *list);
/**
 * \brief create a list of variable
 */
struct list_variable *create_list_variable(void);
/**
 * \brief add a variable with his value to the list
 *
 * \param list_variable list of variable
 * \param variable variable
 * \param value value
 */
struct list_variable *add_variable(struct list_variable *list_variable,
                                   char *variable, char *value);
/**
 * \brief get the value of a variable in the list
 *
 * \param list list of variable
 * \param variable variable
 */
char *get_value(struct list_variable *list, char *variable);

/**
 * \brief free the list of variable
 *
 * \param list list of variable
 */
void free_list_variable(struct list_variable *list);

/**
 * \brief delete the value in a list of variable
 *
 * \param list list of variable
 * \param value value
 */
void delete_value(struct list_variable *list, char *value);

/**
 * \brief subtitute a value in list of variable
 *
 * \param list list of variable
 * \param value value
 */
char *variable_substitution(char *value, struct list_variable *list);
char *quoting(char *value, struct list_variable *list);
/**
 * \brief execution of an assignment word
 *
 * \param node ast-node
 * \param list list of variable
 */
struct list_variable *exec_assignement_word(struct ast_node *node,
                                            struct list_variable *list);

char **exec_substitution_cmd(char **command, struct list_variable *list);
void free_substitution_cmd(char **command);

#endif
