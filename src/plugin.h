#ifndef PLUGIN_H
#define PLUGIN_H

#include "utils.h"

/* Minimal plugin definition */
typedef void (*plugin_init_func)(void);

/* Load a plugin at runtime (shared object) */
bool load_plugin(const char *path);

#endif /* PLUGIN_H */
