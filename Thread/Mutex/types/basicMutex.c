#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* thread_function(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread %ld has entered the critical section.\n", (long)arg);
    // Critical section
    printf("Thread %ld is leaving the critical section.\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[2];
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}

