#include "builtin.h"

int builtin_break(size_t is_loop)
{
    if (is_loop)
        return 4242;
    fprintf(stderr, "break is for for / until / while loops\n");
    return 0;
}
