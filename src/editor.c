#define _POSIX_C_SOURCE 200809L
#include "editor.h"

static char *editor_buffer = NULL;

void init_editor(void) {
    editor_buffer = strdup("");  /* start empty */
}

void shutdown_editor(void) {
    free(editor_buffer);
    editor_buffer = NULL;
}

void set_editor_buffer(const char *content) {
    if (editor_buffer) {
        free(editor_buffer);
    }
    editor_buffer = strdup(content);
}

const char* get_editor_buffer(void) {
    return editor_buffer ? editor_buffer : "";
}
