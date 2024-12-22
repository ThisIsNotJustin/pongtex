#include "mutex.h"

void mutex_init(mutex_t *mutex) {
    mutex->lock = false;
    mutex->val = 0;
}

static bool atomic_compare_and_swap(_Atomic int64_t *ptr, int64_t old_val, int64_t new_val) {
    return atomic_compare_exchange_strong(ptr, &old_val, new_val);
}

static bool atomic_compare_and_swap_bool(_Atomic bool *ptr, bool old_val, bool new_val) {
    return atomic_compare_exchange_strong(ptr, &old_val, new_val);
}


static void atomic_s(_Atomic int64_t *ptr, int64_t val) {

    while (!atomic_compare_and_swap(ptr, *ptr, val)) {
#ifdef __x86_64__
        __asm__ volatile("pause");
#elif defined(__aarch64__)
        __asm__ volatile("yield");
#else
        printf("Unsupported architecture\n");
#endif
    }
}

void mutex_lock(mutex_t *mutex) {
    while (1) {
        if (!mutex->lock) {
            if (atomic_compare_and_swap_bool((_Atomic bool *) &mutex->lock, false, true)) {
                return;
            }
        }

#ifdef __x86_64__
        __asm__ volatile("pause");
#elif defined(__aarch64__)
        __asm__ volatile("yield");
#else
        printf("Unsupported architecture\n");
#endif
    }
}

void mutex_unlock(mutex_t *mutex) {
    atomic_s((_Atomic int64_t *) &mutex->lock, 0);
}