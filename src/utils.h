#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <ncurses.h>

/* Utility macros */
#define UNUSED(x) (void)(x)

/* Forward declarations, if needed */
void log_debug(const char *fmt, ...);

#endif /* UTILS_H */
