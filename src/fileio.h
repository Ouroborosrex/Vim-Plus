#ifndef FILEIO_H
#define FILEIO_H

#include "utils.h"

/* Asynchronously load a file’s contents */
void async_load_file(const char *filename);

/* Asynchronously save current buffer to file */
void async_save_file(const char *filename, const char *contents);

#endif /* FILEIO_H */
