#define _POSIX_C_SOURCE 200809L
#include "fileio.h"
#include "event_loop.h"
#include "editor.h"

static void load_file_task(void *arg) {
    const char *filename = (const char *)arg;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open %s\n", filename);
        free(arg);
        return;
    }

    /* Read file into an in-memory buffer (naive approach) */
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(size + 1);
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    fclose(fp);

    /* Update the editor buffer (from main thread normally) */
    set_editor_buffer(buffer);

    free(buffer);
    free(arg);
}

void async_load_file(const char *filename) {
    /* Copy filename for the background thread */
    char *arg = strdup(filename);
    enqueue_task(load_file_task, arg);
}

static void save_file_task(void *arg) {
    const char *filename = ((char **)arg)[0];
    const char *contents = ((char **)arg)[1];

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Failed to open %s for writing\n", filename);
        free((void *)filename);
        free((void *)contents);
        free(arg);
        return;
    }
    fputs(contents, fp);
    fclose(fp);

    free((void *)filename);
    free((void *)contents);
    free(arg);
}

void async_save_file(const char *filename, const char *contents) {
    /* We need to allocate a small array of two pointers. */
    char **args = (char **)malloc(sizeof(char *) * 2);
    args[0] = strdup(filename);
    args[1] = strdup(contents);
    enqueue_task(save_file_task, args);
}
