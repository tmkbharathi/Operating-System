#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* thread_function(void* arg) {
    if (pthread_mutex_trylock(&mutex) == 0) {
        printf("Thread %ld acquired the lock.\n", (long)arg);
        sleep(2);  // Simulate work
        pthread_mutex_unlock(&mutex);
        printf("Thread %ld released the lock.\n", (long)arg);
    } else {
        printf("Thread %ld could not acquire the lock (already locked).\n", (long)arg);
    }
    return NULL;
}

int main() {
    pthread_t threads[2];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, thread_function, (void*)1);
    sleep(1);  // Delay to increase chance of lock contention
    pthread_create(&threads[1], NULL, thread_function, (void*)2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

