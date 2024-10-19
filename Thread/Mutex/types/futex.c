#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <stdatomic.h>

atomic_int futex_var = 0;

int futex_wait(atomic_int *futex_addr, int val) {
    return syscall(SYS_futex, futex_addr, FUTEX_WAIT, val, NULL, NULL, 0);
}

int futex_wake(atomic_int *futex_addr, int num) {
    return syscall(SYS_futex, futex_addr, FUTEX_WAKE, num, NULL, NULL, 0);
}

void* thread_function(void* arg) {
    int expected = 0;
    if (atomic_compare_exchange_strong(&futex_var, &expected, 1)) {
        printf("Thread %ld acquired the lock.\n", (long)arg);
        sleep(2);  // Simulate work
        atomic_store(&futex_var, 0);  // Release lock
        futex_wake(&futex_var, 1);  // Wake up one waiting thread
        printf("Thread %ld released the lock.\n", (long)arg);
    } else {
        printf("Thread %ld waiting for the lock.\n", (long)arg);
        futex_wait(&futex_var, 1);  // Wait on the futex variable
    }
    return NULL;
}

int main() {
    pthread_t threads[2];
    
    pthread_create(&threads[0], NULL, thread_function, (void*)1);
    sleep(1);  // Give the first thread a chance to lock
    pthread_create(&threads[1], NULL, thread_function, (void*)2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}

