#include "thread.h"

thread_t custom_thread_create(void *(*start_routine)(void *), void *arg) {
    thread_t thread;
    thread_args_t *args = malloc(sizeof(thread_args_t));
    if (!args) {
        printf("Memory Allocation Failed\n");
        return 0;
    }

    args->start_routine = start_routine;
    args->arg = arg;

    int ret = pthread_create(&thread, NULL, start_routine, arg);
    if (ret != 0) {
        free(args);
        printf("Create Thread Failed\n");
        return 0;
    }

    return thread;
}