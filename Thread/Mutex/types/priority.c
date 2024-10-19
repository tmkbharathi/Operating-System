#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* threadFunction(void* arg) {
    printf("Thread %ld attempting to lock the mutex.\n", (long)arg);
    pthread_mutex_lock(&mutex);
    printf("Thread %ld has locked the mutex.\n", (long)arg);
    sleep(2);  // Simulate some work in critical section
    pthread_mutex_unlock(&mutex);
    printf("Thread %ld has unlocked the mutex.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[2];
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);  // Set priority inheritance
    pthread_mutex_init(&mutex, &attr);

    pthread_create(&threads[0], NULL, threadFunction, (void*)1);
    sleep(1);  // Give the first thread  chance to lock the mutex
    pthread_create(&threads[1], NULL, threadFunction, (void*)2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}

