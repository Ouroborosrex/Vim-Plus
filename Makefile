CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -fPIC -I./src
LDFLAGS = -lpthread -lncurses

SOURCES = \
    src/main.c \
    src/editor.c \
    src/event_loop.c \
    src/syntax.c \
    src/plugin.c \
    src/lsp.c \
    src/fileio.c \
    src/window.c

OBJECTS = $(SOURCES:.c=.o)

# Build the main executable
all: myVim sample_plugin.so

myVim: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build the sample plugin as a shared library
sample_plugin.so: plugins/sample_plugin.c
	$(CC) $(CFLAGS) -shared -o $@ $<

# Basic cleanup
clean:
	rm -f $(OBJECTS) myVim sample_plugin.so
