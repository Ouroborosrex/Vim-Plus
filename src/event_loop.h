#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "utils.h"

/* Event loop interface */

typedef void (*TaskFunction)(void *arg);

typedef struct Task {
    TaskFunction function;
    void *arg;
    struct Task *next;
} Task;

void init_event_loop(void);
void destroy_event_loop(void);
void enqueue_task(TaskFunction func, void *arg);

#endif /* EVENT_LOOP_H */
