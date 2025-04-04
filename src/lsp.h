#ifndef LSP_H
#define LSP_H

#include "utils.h"

/* Initialize the LSP client with a language server command */
bool init_lsp_client(const char *server_cmd);

/* Send a dummy request (e.g. completion) */
bool lsp_request_completion(const char *file_path, int line, int col);

/* Shutdown the LSP client */
void shutdown_lsp_client(void);

#endif /* LSP_H */
