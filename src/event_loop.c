#define _POSIX_C_SOURCE 200809L

#include "event_loop.h"

static pthread_t worker_thread;
static pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  queue_cond  = PTHREAD_COND_INITIALIZER;

static Task *task_queue_head = NULL;
static bool event_loop_running = false;

static void *event_loop_worker(void *arg) {
    UNUSED(arg);

    while (event_loop_running) {
        pthread_mutex_lock(&queue_mutex);
        while (task_queue_head == NULL && event_loop_running) {
            /* Wait for new tasks */
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        /* Pop the task from queue */
        Task *task = task_queue_head;
        if (task) {
            task_queue_head = task->next;
        }
        pthread_mutex_unlock(&queue_mutex);

        /* Execute task function */
        if (task) {
            task->function(task->arg);
            free(task);
        }
    }
    return NULL;
}

void init_event_loop(void) {
    event_loop_running = true;
    pthread_create(&worker_thread, NULL, event_loop_worker, NULL);
}

void destroy_event_loop(void) {
    /* Signal the thread to stop */
    pthread_mutex_lock(&queue_mutex);
    event_loop_running = false;
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);

    pthread_join(worker_thread, NULL);
}

void enqueue_task(TaskFunction func, void *arg) {
    Task *new_task = (Task *)malloc(sizeof(Task));
    new_task->function = func;
    new_task->arg = arg;
    new_task->next = NULL;

    pthread_mutex_lock(&queue_mutex);
    /* Insert at head, or you could keep a tail pointer, etc. */
    new_task->next = task_queue_head;
    task_queue_head = new_task;
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}
