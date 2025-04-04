#define _POSIX_C_SOURCE 200809L

#include "syntax.h"

/*
 * highlight_line:
 * A naive demonstration function that classifies words.
 * For example, let's consider:
 *   - "if" or "for" as TOKEN_KEYWORD
 *   - anything in quotes as TOKEN_STRING
 *   - lines starting with '#' as TOKEN_COMMENT
 *   - everything else as TOKEN_IDENTIFIER
 *
 * This example is purely illustrative.
 */
void highlight_line(const char *line, TokenType *token_types, int max_tokens) {
    if (!line || !token_types) return;

    /* If line starts with '#' treat as comment */
    if (line[0] == '#') {
        token_types[0] = TOKEN_COMMENT;
        return;
    }

    int token_count = 0;
    char buffer[256];
    size_t i = 0, j = 0;

    while (line[i] != '\0' && token_count < max_tokens) {
        /* Skip spaces */
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }

        j = 0;
        while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0') {
            buffer[j++] = line[i++];
        }
        buffer[j] = '\0';

        if (j > 0) {
            /* Simple rules */
            if (strcmp(buffer, "if") == 0 || strcmp(buffer, "for") == 0) {
                token_types[token_count++] = TOKEN_KEYWORD;
            } else if (buffer[0] == '"' && buffer[j-1] == '"') {
                token_types[token_count++] = TOKEN_STRING;
            } else {
                token_types[token_count++] = TOKEN_IDENTIFIER;
            }
        }
    }
}
