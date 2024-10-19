#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>
#include <signal.h>

int keepRunning = 1;

void* threadFunction(void* arg) {
    while (keepRunning) {
        sleep(1);                           // Simulate doing work
    }
    printf("Thread is exiting...\n");
    return NULL;
}

void handleSignal(int signal) {
    if (signal == SIGINT) {                // Attain by CTRL+C
        keepRunning = 0;                   // Set the flag to 0 to stop the thread
    }
}

int main() {
    pthread_t thread;

    // Create a thread that will run indefinitely
    if (pthread_create(&thread, NULL, threadFunction, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    signal(SIGINT, handleSignal);

    pthread_join(thread, NULL);
    printf("Main thread exiting...\n");
    return 0;
}

