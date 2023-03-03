#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum token_type
{
    TOKEN_WORD = 0,

    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_WHILE,
    TOKEN_UNTIL,

    TOKEN_COMMA,
    TOKEN_NEWLINE,
    TOKEN_AMPERSAND, // = ;
    TOKEN_LEFT_HUG, // = {
    TOKEN_RIGHT_HUG, // = }
    TOKEN_LEFT_HOOK, // = [
    TOKEN_RIGHT_HOOK, // = ]
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,

    TOKEN_AND,
    TOKEN_OR,

    TOKEN_NOT,
    TOKEN_PIPE,
    TOKEN_DOUBLE_AMPERSAND,

    TOKEN_CASE,
    TOKEN_ESAC,
    TOKEN_IN,

    TOKEN_FOR,

    TOKEN_REDIRECTION_OUTPUT,
    TOKEN_REDIRECTION_INPUT,
    TOKEN_REDIRECTION_APPEND_OUTPUT,
    TOKEN_REDIRECTION_DUP_INPUT,
    TOKEN_REDIRECTION_DUP_OUTPUT,
    TOKEN_REDIRECTION_RDWR,

    TOKEN_FUNCDEC,

    TOKEN_EOF,

    TOKEN_ERROR = -1
};

#endif // TOKEN_TYPE_H
