#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t binary_semaphore;

void* thread_function(void* arg) {
    printf("Thread %d waiting for semaphore...\n", *(int*)arg);
    sem_wait(&binary_semaphore);  // Lock
    printf("Thread %d inside critical section.\n", *(int*)arg);
    sleep(2);  // Simulate work
    printf("Thread %d leaving critical section.\n", *(int*)arg);
    sem_post(&binary_semaphore);  // Unlock
    return NULL;
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {1, 2};
    
    // Initialize semaphore with value 1 (binary semaphore)
    sem_init(&binary_semaphore, 0, 1);

    pthread_create(&threads[0], NULL, thread_function, &thread_ids[0]);
    pthread_create(&threads[1], NULL, thread_function, &thread_ids[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sem_destroy(&binary_semaphore);
    return 0;
}

