#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"

typedef struct EditorWindow {
    int width;
    int height;
    int cursor_x;
    int cursor_y;
    /* Additional fields for buffer references, etc. */
} EditorWindow;

/* Create a new window */
EditorWindow *create_window(int width, int height);

/* Resize a window */
void resize_window(EditorWindow *win, int new_width, int new_height);

/* Render the window contents */
void render_window(EditorWindow *win);

#endif /* WINDOW_H */
