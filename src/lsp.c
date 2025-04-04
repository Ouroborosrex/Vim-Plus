#define _POSIX_C_SOURCE 200809L
#include "lsp.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>   /* Defines SIGTERM and kill */
#include <stdio.h>
#include <stdlib.h>

static pid_t lsp_process = 0;

bool init_lsp_client(const char *server_cmd) {
    if (!server_cmd) return false;

    /* Fork and exec the language server (very naive example) */
    lsp_process = fork();
    if (lsp_process == 0) {
        /* Child: start language server */
        execlp(server_cmd, server_cmd, NULL);
        /* If we reach here, exec failed */
        perror("execlp failed");
        exit(1);
    } else if (lsp_process < 0) {
        perror("fork failed");
        return false;
    }

    /* Parent: store the PID, set up pipes or sockets for IPC in real scenario */
    return true;
}

bool lsp_request_completion(const char *file_path, int line, int col) {
    if (lsp_process <= 0) return false;

    /* Normally you'd send a JSON-RPC request via a pipe or socket. */
    printf("[LSP] Requesting completion at %s:%d:%d\n", file_path, line, col);
    /* This is just a stub. A real implementation requires I/O. */
    return true;
}

void shutdown_lsp_client(void) {
    if (lsp_process > 0) {
        /* Signal the language server to shutdown gracefully. */
        kill(lsp_process, SIGTERM);
        waitpid(lsp_process, NULL, 0);
    }
}
