#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t signal_semaphore;

void* thread_function(void* arg) {
    printf("Thread waiting for signal...\n");
    sem_wait(&signal_semaphore);  // Wait for the signal
    printf("Thread received signal!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    
    // Initialize semaphore with value 0 (not signaled yet)
    sem_init(&signal_semaphore, 0, 0);

    pthread_create(&thread, NULL, thread_function, NULL);

    sleep(2);  // Simulate some work
    printf("Main thread signaling semaphore...\n");
    sem_post(&signal_semaphore);  // Send signal

    pthread_join(thread, NULL);
    sem_destroy(&signal_semaphore);
    return 0;
}

