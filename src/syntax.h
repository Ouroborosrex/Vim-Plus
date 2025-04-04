#ifndef SYNTAX_H
#define SYNTAX_H

#include "utils.h"

/* Example “token types” for demonstration */
typedef enum {
    TOKEN_UNKNOWN,
    TOKEN_KEYWORD,
    TOKEN_STRING,
    TOKEN_COMMENT,
    TOKEN_IDENTIFIER,
} TokenType;

/* Prototype for syntax highlighting a line of text */
void highlight_line(const char *line, TokenType *token_types, int max_tokens);

#endif /* SYNTAX_H */
