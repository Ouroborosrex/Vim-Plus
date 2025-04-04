#define _POSIX_C_SOURCE 200809L
#include "utils.h"
#include "event_loop.h"
#include "editor.h"
#include "syntax.h"
#include "plugin.h"
#include "lsp.h"
#include "fileio.h"
#include "window.h"

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    /* Initialize curses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Initialize the event loop */
    init_event_loop();

    /* Initialize editor */
    init_editor();

    /* Optionally init LSP client (requires a valid language server installed) */
    // init_lsp_client("clangd"); // Example: clangd

    /* Create an EditorWindow */
    EditorWindow *win = create_window(COLS, LINES);

    /* Load a sample plugin */
    load_plugin("./sample_plugin.so");

    bool running = true;
    while (running) {
        render_window(win);

        int ch = getch();
        switch (ch) {
            case 'q':
                running = false;
                break;
            case 'o':
                /* Example: load a file asynchronously */
                async_load_file("test.txt");
                break;
            case 's':
                /* Example: save the current buffer */
                async_save_file("output.txt", get_editor_buffer());
                break;
            default:
                break;
        }
    }

    /* Cleanup */
    shutdown_editor();
    destroy_event_loop();
    // shutdown_lsp_client();

    endwin();

    return 0;
}
