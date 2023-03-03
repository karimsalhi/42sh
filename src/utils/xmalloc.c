#include <err.h>
#include <stddef.h>
#include <stdlib.h>

void *xmalloc(size_t size)
{
    void *rtn;

    if (size && !(rtn = malloc(size)))
        err(1, "xmalloc: failed to malloc");

    return rtn;
}

void *xrealloc(void *ptr, size_t size)
{
    void *rtn;

    if (size && !(rtn = realloc(ptr, size)))
        err(1, "xrealloc: failed to realloc");

    return rtn;
}

void *xcalloc(size_t count, size_t size)
{
    void *rtn;

    if (count && size && !(rtn = calloc(count, size)))
        err(1, "xcalloc: failed to calloc");

    return rtn;
}
