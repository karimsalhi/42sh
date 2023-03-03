#ifndef BUILTIN_H
#define BUILTIN_H
#define _GNU_SOURCE

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/xmalloc.h"

struct echo_opt
{
    int E_opt;
    int n_opt;
    int e_opt;
    int id;
};

/**
 * \brief Function who has the same behavior than exit
 *
 */
int builtin_exit(void);
/**
 * \brief Function who has the same behavior than cd
 *
 * \param argc argc
 * \param argv argv
 */
int builtin_cd(int argc, char **argv);
/**
 * \brief Function who has the same behavior than echo
 *
 * \param argc argc
 * \param argv argv
 */
int builtin_echo(int argc, char **argv);

int builtin_break(size_t is_loop);
int builtin_continue(size_t is_loop);

#endif /* !BUILTIN_H */
