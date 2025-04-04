#ifndef EDITOR_H
#define EDITOR_H

#include "utils.h"

void init_editor(void);
void shutdown_editor(void);
void set_editor_buffer(const char *content);
const char* get_editor_buffer(void);

#endif /* EDITOR_H */
