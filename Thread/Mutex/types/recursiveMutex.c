#include <stdio.h>
#include <pthread.h>

pthread_mutex_t recursive_mutex;

void* recursive_function(void* arg) {
    pthread_mutex_lock(&recursive_mutex);
    printf("Thread %ld acquired the lock.\n", (long)arg);
    pthread_mutex_lock(&recursive_mutex);  // Lock again (recursive)
    printf("Thread %ld acquired the lock recursively.\n", (long)arg);

    // Critical section
    pthread_mutex_unlock(&recursive_mutex);  // First unlock
    pthread_mutex_unlock(&recursive_mutex);  // Second unlock
    printf("Thread %ld released the lock.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);  // Set mutex as recursive
    pthread_mutex_init(&recursive_mutex, &attr);

    pthread_create(&thread, NULL, recursive_function, (void*)1);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&recursive_mutex);
    pthread_mutexattr_destroy(&attr);
    return 0;
}

