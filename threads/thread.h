#ifndef THREAD_H
#define THREAD_H


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef pthread_t thread_t;

typedef struct {
    void *(*start_routine)(void *);
    void *arg;
} thread_args_t;

thread_t custom_thread_create(void *(*start_routine)(void *), void *arg);

#endif // THREAD_H