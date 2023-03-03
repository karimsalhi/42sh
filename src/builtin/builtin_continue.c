#include "builtin.h"

int builtin_continue(size_t is_loop)
{
    if (is_loop)
        return 4243;
    fprintf(stderr, "continue is for for / until / while loops\n");
    return 0;
}
