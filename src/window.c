#include "window.h"
#include "editor.h"

EditorWindow *create_window(int width, int height) {
    EditorWindow *win = (EditorWindow *)malloc(sizeof(EditorWindow));
    win->width = width;
    win->height = height;
    win->cursor_x = 0;
    win->cursor_y = 0;
    return win;
}

void resize_window(EditorWindow *win, int new_width, int new_height) {
    if (!win) return;
    win->width = new_width;
    win->height = new_height;
}

void render_window(EditorWindow *win) {
    if (!win) return;

    /* Clear the screen, then render the current buffer. For simplicity, 
       we'll just show a placeholder text. 
       A real implementation would draw text lines from the editor buffer. */
    clear();
    mvprintw(0, 0, "myVim Editor - (demo render)");
    mvprintw(1, 0, "Window size: %dx%d", win->width, win->height);
    mvprintw(2, 0, "Cursor at: (%d, %d)", win->cursor_x, win->cursor_y);
    mvprintw(4, 0, "Press 'q' to quit.");

    refresh();
}
