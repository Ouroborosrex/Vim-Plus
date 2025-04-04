#define _POSIX_C_SOURCE 200809L
#include <dlfcn.h>
#include "plugin.h"

bool load_plugin(const char *path) {
    void *handle = dlopen(path, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Failed to load plugin %s: %s\n", path, dlerror());
        return false;
    }

    /* Look for an init_plugin function */
    plugin_init_func init_func = (plugin_init_func)dlsym(handle, "init_plugin");
    if (!init_func) {
        fprintf(stderr, "No init_plugin symbol found in %s\n", path);
        dlclose(handle);
        return false;
    }

    /* Call the plugin’s init function */
    init_func();
    return true;
}
