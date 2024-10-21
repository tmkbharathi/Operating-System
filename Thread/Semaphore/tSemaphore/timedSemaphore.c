#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

sem_t timed_semaphore;

void* thread_function(void* arg) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 3;  // Wait for 3 seconds

    printf("Thread %d waiting for semaphore with timeout...\n", *(int*)arg);
    if (sem_timedwait(&timed_semaphore, &ts) == -1) {
        printf("Thread %d timed out.\n", *(int*)arg);
    } else {
        printf("Thread %d acquired semaphore.\n", *(int*)arg);
        sem_post(&timed_semaphore);  // Release semaphore
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int thread_id = 1;
    
    // Initialize semaphore with value 0
    sem_init(&timed_semaphore, 0, 0);

    pthread_create(&thread, NULL, thread_function, &thread_id);
    sleep(5);  // Simulate delay

    pthread_join(thread, NULL);
    sem_destroy(&timed_semaphore);
    return 0;
}

