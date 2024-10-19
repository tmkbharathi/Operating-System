#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_spinlock_t spinlock;

void* thread_function(void* arg) {
    pthread_spin_lock(&spinlock);  // Acquire spinlock
    printf("Thread %ld acquired the spinlock.\n", (long)arg);
    sleep(1);  // Simulate work
    pthread_spin_unlock(&spinlock);  // Release spinlock
    printf("Thread %ld released the spinlock.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[2];
    pthread_spin_init(&spinlock, 0);  // Initialize spinlock

    for (long i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_spin_destroy(&spinlock);  // Destroy spinlock
    return 0;
}

