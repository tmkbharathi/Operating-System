#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex;
void* thread_function(void* arg) {
    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += 2;  // Set timeout to 2 seconds

    if (pthread_mutex_timedlock(&mutex, &timeout) == 0) {
        printf("Thread %ld acquired the lock.\n", (long)arg);
        sleep(3);  // Simulate work
        pthread_mutex_unlock(&mutex);
        printf("Thread %ld released the lock.\n", (long)arg);
    } else {
        printf("Thread %ld could not acquire the lock (timeout).\n", (long)arg);
    }
    return NULL;
}

int main() {
    pthread_t threads[2];
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, thread_function, (void*)1);
    sleep(1);  // Delay to increase chance of timeout
    pthread_create(&threads[1], NULL, thread_function, (void*)2);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

