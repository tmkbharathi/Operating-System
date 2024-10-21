#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t counting_semaphore;

void* thread_function(void* arg) {
    printf("Thread %d waiting for semaphore...\n", *(int*)arg);
    sem_wait(&counting_semaphore);  // Decrement (lock)
    printf("Thread %d inside critical section.\n", *(int*)arg);
    sleep(2);  // Simulate work
    printf("Thread %d leaving critical section.\n", *(int*)arg);
    sem_post(&counting_semaphore);  // Increment (unlock)
    return NULL;
}

int main() {
    pthread_t threads[4];
    int thread_ids[4] = {1, 2, 3, 4};
    
    // Initialize counting semaphore with value 2 (2 threads can enter critical section)
    sem_init(&counting_semaphore, 0, 2);

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&counting_semaphore);
    return 0;
}


