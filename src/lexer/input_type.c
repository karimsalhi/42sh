#include "lexer.h"

#define BUF_SIZE 4096

FILE *input_type(struct option *opt, int argc, char **argv)
{
    char *buf = argv[argc - 1];
    FILE *buf_descr;
    size_t len = strlen(buf);

    if (argc == 1)
        return stdin;

    if (opt->c_option == 1)
    {
        buf = opt->c_arg;
        len = strlen(buf);
        buf_descr = fmemopen(buf, len, "r");
    }

    else
        buf_descr = fopen(buf, "r");

    if (!buf_descr)
        return NULL;
    // char rd_buf[BUF_SIZE] = { '\0' };
    // fread(rd_buf, len, sizeof(char), buf_descr);

    return buf_descr;
}
