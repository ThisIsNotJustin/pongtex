#ifndef MUTEX_H
#define MUTEX_H

#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>
#include <stdint.h>

typedef struct {
    _Atomic bool lock;
    int64_t val;
} __attribute__((aligned(64))) mutex_t;

void mutex_init(mutex_t *mutex);
static bool atomic_compare_and_swap(_Atomic int64_t *ptr, int64_t old_val, int64_t new_val);
static bool atomic_compare_and_swap_bool(_Atomic bool *ptr, bool old_val, bool new_val);
static void atomic_s(_Atomic int64_t *ptr, int64_t val);
void mutex_lock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);

#endif // MUTEX_H