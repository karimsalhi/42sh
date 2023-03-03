#include "lexer.h"

static enum token_type get_separator(char *value)
{
    if (strcmp(value, ";") == 0)
        return TOKEN_COMMA;
    else if (strcmp(value, "\n") == 0)
        return TOKEN_NEWLINE;
    else if (strcmp(value, "&") == 0)
        return TOKEN_AMPERSAND;
    else if (strcmp(value, "{") == 0)
        return TOKEN_LEFT_HUG;
    else if (strcmp(value, "}") == 0)
        return TOKEN_RIGHT_HUG;
    else if (strcmp(value, "[") == 0)
        return TOKEN_LEFT_HOOK;
    else if (strcmp(value, "]") == 0)
        return TOKEN_RIGHT_HOOK;
    else if (strcmp(value, "(") == 0)
        return TOKEN_LEFT_PARENTHESIS;
    else if (strcmp(value, ")") == 0)
        return TOKEN_RIGHT_PARENTHESIS;
    else
        return TOKEN_ERROR;
}

static enum token_type get_token(char *value)
{
    if (strcmp(value, "if") == 0)
        return TOKEN_IF;
    else if (strcmp(value, "elif") == 0)
        return TOKEN_ELIF;
    else if (strcmp(value, "then") == 0)
        return TOKEN_THEN;
    else if (strcmp(value, "else") == 0)
        return TOKEN_ELSE;
    else if (strcmp(value, "fi") == 0)
        return TOKEN_FI;
    else if (strcmp(value, "do") == 0)
        return TOKEN_DO;
    else if (strcmp(value, "done") == 0)
        return TOKEN_DONE;
    else if (strcmp(value, "while") == 0)
        return TOKEN_WHILE;
    else if (strcmp(value, "until") == 0)
        return TOKEN_UNTIL;
    else if (strcmp(value, "for") == 0)
        return TOKEN_FOR;
    else
        return TOKEN_ERROR;
}
static enum token_type get_case(char *value)
{
    if (strcmp(value, "esac") == 0)
        return TOKEN_ESAC;
    else if (strcmp(value, "case") == 0)
        return TOKEN_CASE;
    else if (strcmp(value, "function") == 0)
        return TOKEN_FUNCDEC;
    else if (strcmp(value, "in") == 0)
        return TOKEN_IN;
    return TOKEN_ERROR;
}

static enum token_type get_and_or(char *value)
{
    if (strcmp(value, "&&") == 0)
        return TOKEN_AND;
    else if (strcmp(value, "||") == 0)
        return TOKEN_OR;
    else if (strcmp(value, ";;") == 0)
        return TOKEN_DOUBLE_AMPERSAND;
    else
        return TOKEN_ERROR;
}

static enum token_type get_pipeline(char *value)
{
    if (strcmp(value, "|") == 0)
        return TOKEN_PIPE;
    else if (strcmp(value, "!") == 0)
        return TOKEN_NOT;
    else
        return TOKEN_ERROR;
}

enum token_type get_redirection(char *value)
{
    if (strcmp(value, ">") == 0)
        return TOKEN_REDIRECTION_OUTPUT;
    else if (strcmp(value, ">|") == 0)
        return TOKEN_REDIRECTION_OUTPUT;
    else if (strcmp(value, "<") == 0)
        return TOKEN_REDIRECTION_INPUT;
    else if (strcmp(value, ">>") == 0)
        return TOKEN_REDIRECTION_APPEND_OUTPUT;
    else if (strcmp(value, "<&") == 0)
        return TOKEN_REDIRECTION_DUP_INPUT;
    else if (strcmp(value, ">&") == 0)
        return TOKEN_REDIRECTION_DUP_OUTPUT;
    else if (strcmp(value, "<>") == 0)
        return TOKEN_REDIRECTION_RDWR;
    return TOKEN_ERROR;
}

enum token_type get_type(char *value)
{
    enum token_type type = TOKEN_WORD;

    if (!*value)
        return TOKEN_EOF;
    else if ((type = get_separator(value)) != TOKEN_ERROR)
        return type;
    else if ((type = get_token(value)) != TOKEN_ERROR)
        return type;
    else if ((type = get_and_or(value)) != TOKEN_ERROR)
        return type;
    else if ((type = get_redirection(value)) != TOKEN_ERROR)
        return type;
    else if ((type = get_pipeline(value)) != TOKEN_ERROR)
        return type;
    else if ((type = get_case(value)) != TOKEN_ERROR)
        return type;
    else
        return TOKEN_WORD;
}
